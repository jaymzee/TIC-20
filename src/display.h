#ifndef TIC_DISPLAY_H_INCLUDED
#define TIC_DISPLAY_H_INCLUDED

#include <stdint.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)

#define MAX_FONTS 256

typedef struct Display Display;

Display *CreateDisplay(const char *window_title,
                       uint32_t pencolor,
                       uint32_t renderer_flags);
void DestroyDisplay(Display *);

void ClearScreen(const Display *, uint32_t backcolor);
void Delay(uint32_t msec);
void DrawLine(const Display *, int x1, int y1, int x2, int y2);

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
int DrawText(const Display *,
             int x, int y, const char *str,
             uint32_t color, uint8_t font_slot);
void FlipDisplay(const Display *);
void PenColor(Display *, uint32_t color);
const char *LoadFont(Display *display, uint8_t slot, const char *fontpath, int size);

#endif
