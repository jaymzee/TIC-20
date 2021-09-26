#ifndef TIC_DISPLAY_H_INCLUDED
#define TIC_DISPLAY_H_INCLUDED

#include <stdint.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)

typedef struct Display Display;

Display *CreateDisplay(uint32_t pencolor);
void DestroyDisplay(Display *);

void ClearScreen(const Display *, uint32_t color);
void Delay(uint32_t msec);
void DrawLine(const Display *, int x1, int y1, int x2, int y2);
void DrawPoint(const Display *, int x, int y);

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
// returns 1 on success and 0 on failure
int DrawText(const Display *,
             int x, int y, const char *str,
             uint32_t color);
void FlipDisplay(const Display *);
void PenColor(Display *, uint32_t color);

#endif
