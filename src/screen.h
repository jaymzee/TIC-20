#include <stdint.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)

#define MAX_FONTS 1

struct Screen *CreateScreen(uint32_t pencolor, uint32_t flags);
void DestroyScreen(struct Screen *);

void ClearScreen(const struct Screen *, uint32_t color);
void Delay(uint32_t msec);
void DrawLine(const struct Screen *, int x1, int y1, int x2, int y2);

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(const struct Screen *,
              int x, int y, const char *str,
              int font, uint32_t color);
void Flip(const struct Screen *);
void SetPenColor(struct Screen *, uint32_t color);
