#ifndef TIC_DISPLAY_H_INCLUDED
#define TIC_DISPLAY_H_INCLUDED

#include <stdint.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)

#define MAX_FONTS 1

typedef struct Display Display;

Display *CreateDisplay(uint32_t color, uint32_t flags);
void DestroyDisplay(Display *);

void ClearScreen(const Display *, uint32_t color);
void Delay(uint32_t msec);
void DrawLine(const Display *, int x1, int y1, int x2, int y2);

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(const Display *,
              int x, int y, const char *str,
              int font, uint32_t color);
void FlipDisplay(const Display *);
void PenColor(Display *, uint32_t color);

#endif
