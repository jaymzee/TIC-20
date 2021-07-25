#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"

struct Screen {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font[MAX_FONTS];
    uint32_t pencolor;
};

struct Screen *CreateScreen(uint32_t pencolor, uint32_t renderer_flags)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *sans18;

    // create a winodw, renderer, and font
    window = SDL_CreateWindow(
        "lua",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "Create Window:%s\n", SDL_GetError());
        return NULL;
    }

    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (!renderer) {
        fprintf(stderr, "Create Renderer:%s\n", SDL_GetError());
        return NULL;
    }
    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    sans18 = TTF_OpenFont("DejaVuSans.ttf", 18);
    if (!sans18) {
        fprintf(stderr, "Open Font: %s\n", TTF_GetError());
        return NULL;
    }

    struct Screen *screen = calloc(1, sizeof(struct Screen));
    screen->window = window;
    screen->renderer = renderer;
    screen->font[0] = sans18;
    screen->pencolor = pencolor;

    return screen;
}

void DestroyScreen(struct Screen *screen)
{
    SDL_DestroyRenderer(screen->renderer);
    SDL_DestroyWindow(screen->window);
    screen->renderer = NULL;
    screen->window = NULL;
}

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(const struct Screen *screen,
              int x, int y, const char *str,
              int font_number, uint32_t color)
{
    SDL_Renderer *renderer = screen->renderer;
    TTF_Font *font = screen->font[font_number];
    SDL_Color color_ = { color >> 24, color >> 16, color >> 8, color };

    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Blended(font, str, color_);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void ClearScreen(const struct Screen *screen, uint32_t color)
{
    SDL_Renderer *renderer = screen->renderer;
    uint8_t r = color >> 24, g = color >> 16, b = color >> 8, a = color;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);

    color = screen->pencolor;
    r = color >> 24, g = color >> 16, b = color >> 8, a = color;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SetPenColor(struct Screen *screen, uint32_t color)
{
    uint8_t r = color >> 24, g = color >> 16, b = color >> 8, a = color;

    screen->pencolor = color;
    SDL_SetRenderDrawColor(screen->renderer, r, g, b, a);
}

void DrawLine(const struct Screen *screen, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(screen->renderer, x1, y1, x2, y2);
}

void Flip(const struct Screen *screen)
{
    SDL_RenderPresent(screen->renderer);
}

void Delay(uint32_t msec)
{
    SDL_Delay(msec);
}

