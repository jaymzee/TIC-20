#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "display.h"
#include "font8x8_basic.h"

#define FBDEV "/dev/fb0"
#define ABS(x) ((x) >= 0 ? (x) : (-x))

void query_framebuffer(const char *device, struct fb_var_screeninfo *fbinfo) {
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror(device);
        exit(1);
    }
    ioctl(fd, FBIOGET_VSCREENINFO, fbinfo);
    close(fd);
}

typedef struct Display {
    struct fb_var_screeninfo fbinf;
    uint32_t *fb;
    size_t   fblen;
    uint32_t pencolor;
} Display;

Display *CreateDisplay(uint32_t pencolor)
{
    Display *disp = calloc(1, sizeof(Display));
    if (!disp) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    query_framebuffer(FBDEV, &disp->fbinf);

    // validate fbinfo
    if (!disp->fbinf.xres || !disp->fbinf.yres) {
        fprintf(stderr, "invalid framebuffer resolution\n");
        exit(1);
    }
    if (disp->fbinf.bits_per_pixel != 32) {
        fprintf(stderr, "32 bpp expected\n");
        exit(1);
    }

    disp->fblen = 4 * disp->fbinf.xres_virtual * disp->fbinf.yres;

    // open framebuffer
    int fd = open(FBDEV, O_RDWR);
    if (fd < 0) {
        perror(FBDEV);
        exit(1);
    }
    // get writable screen memory; 32bit color
    uint32_t *fb = mmap(NULL,
                        disp->fblen,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED,
                        fd,
                        0);
    if (fb == NULL) {
        fprintf(stderr, "mmap fb failed\n");
        exit(1);
    }
    disp->fb = fb;

    // disable cursor
    printf("\033[?1c");
    fflush(stdout);

    PenColor(disp, pencolor);

    return disp;
}

void DestroyDisplay(Display *display)
{
    // restore cursor
    printf("\033[?0c");
    // clear screen
    printf("\033[2J\033[H");

    munmap(display->fb, display->fblen);
    free(display);
}

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
// return 1 on success, 0 on failure
// the usual failure is an invalid font number
int DrawText(const Display *display,
             int x, int y, const char *str,
             uint32_t color)
{
    uint32_t *fb = display->fb;
    int stride = display->fbinf.xres_virtual;
    color = color >> 8;

    for (int n = 0; str[n]; n++) {
        uint8_t c = str[n] & 0x7f; // strip off 8th bit
        for (int i = 0; i < 8; i++) {
            uint8_t d = font8x8_basic[c][i];
            for (int j = 0; j < 8; j++) {
                int offset = x + j*2 + (y+i*4)*stride;
                if (d & 1) {
                    fb[offset] = color;
                    fb[offset + 1] = color;
                    fb[offset + stride] = color;
                    fb[offset + stride + 1] = color;
                    fb[offset + 2*stride] = color;
                    fb[offset + 2*stride + 1] = color;
                    fb[offset + 3*stride] = color;
                    fb[offset + 3*stride + 1] = color;
                } else {
                    fb[offset] = 0;
                    fb[offset + 1] = 0;
                    fb[offset + stride] = 0;
                    fb[offset + stride + 1] = 0;
                    fb[offset + 2*stride] = 0;
                    fb[offset + 2*stride + 1] = 0;
                    fb[offset + 3*stride] = 0;
                    fb[offset + 3*stride + 1] = 0;
                }
                d = d >> 1;
            }
        }
        x += 16;
    }

    return 1;
}

void ClearScreen(const Display *disp, uint32_t color)
{
    uint32_t *fb = disp->fb;
    int stride = disp->fbinf.xres_virtual;
    color = color >> 8;

    printf("\033[2J\033[H");
    fflush(stdout);

    for (int i = 0; i < disp->fbinf.yres; i++) {
        for (int j = 0; j < disp->fbinf.xres; j++) {
            fb[i*stride + j] = color;
        }
    }
}

void PenColor(Display *display, uint32_t color)
{
    uint8_t r = color >> 24, g = color >> 16, b = color >> 8, a = color;

    display->pencolor = color;
}

// Midpoint algorithm for 2D line
void DrawLine(const Display *disp, int x0, int y0, int x1, int y1)
{
    uint32_t *fb = disp->fb;
    int stride = disp->fbinf.xres_virtual;
    uint32_t color = disp->pencolor >> 8;

    const int dx = x1 - x0;
    const int dy = y1 - y0;
    const int incx = x1 > x0 ? 1 : -1;
    const int incy = y1 > y0 ? 1 : -1;

    int x = x0;
    int y = y0;

    fb[y*stride + x] = color;
    if (ABS(dx) > ABS(dy)) {
        const int incrE = 2 * ABS(dy);
        const int incrSE = 2 * (ABS(dy) - ABS(dx));
        int d = 2 * ABS(dy) - ABS(dx);
        while (x != x1) {
            if (d <= 0) {
                d += incrE; // or W
                x += incx;
            } else {
                d += incrSE; // or NE, NW, SW
                x += incx;
                y += incy;
            }
            fb[y*stride + x] = color;
        }
    } else {
        const int incrS = 2 * ABS(dx);
        const int incrSE = 2 * (ABS(dx) - ABS(dy));
        int d = 2 * ABS(dx) - ABS(dy);
        while (y != y1) {
            if (d <= 0) {
                d += incrS; // or N
                y += incy;
            } else {
                d += incrSE; // or SW, NW, NE
                x += incx;
                y += incy;
            }
            fb[y*stride + x] = color;
        }
    }
}

void DrawPoint(const Display *disp, int x, int y)
{
    uint32_t *fb = disp->fb;
    int stride = disp->fbinf.xres_virtual;
    uint32_t color = disp->pencolor >> 8;

    fb[y*stride + x] = color;
}

void Delay(uint32_t msec)
{
    struct timespec req, rem;
    uint32_t sec = msec / 1000;
    msec -= sec * 1000;

    req.tv_sec = sec;
    req.tv_nsec = msec * 1000000;

    nanosleep(&req, &rem);
}
