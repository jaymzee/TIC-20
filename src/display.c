#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "display.h"

typedef struct Display {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font[MAX_FONTS];
    uint32_t pencolor;
} Display;

Display *CreateDisplay(const char *window_title,
                       uint32_t pencolor,
                       uint32_t renderer_flags)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;

    // create a winodw, renderer, and font

    window = SDL_CreateWindow(
        window_title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "Create Window:%s\n", SDL_GetError());
        return NULL;
    }

    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (renderer == NULL) {
        fprintf(stderr, "Create Renderer:%s\n", SDL_GetError());
        return NULL;
    }
    if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
        fprintf(stderr, "Blend Mode:%s\n", SDL_GetError());
    }

    font = TTF_OpenFont("fonts/DejaVuSans.ttf", 18);
    if (font == NULL) {
        fprintf(stderr, "Open Font: %s\n", TTF_GetError());
        return NULL;
    }

    Display *display = calloc(1, sizeof(Display));
    display->window = window;
    display->renderer = renderer;
    display->font[0] = font;
    PenColor(display, pencolor);

    return display;
}

void DestroyDisplay(Display *display)
{
    for (int i = 0; i < MAX_FONTS; i++) {
        TTF_Font *font = display->font[i];
        if (font) {
            TTF_CloseFont(font);
        }
    }
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    free(display);
}

// return error string on failure, null on success
const char *LoadFont(Display *display, uint8_t slot, const char *fontpath, int size)
{
    TTF_Font *font = TTF_OpenFont(fontpath, size);

    if (!font) {
        return TTF_GetError();
    }

    display->font[slot] = font;

    return NULL;
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
             uint32_t color, uint8_t font_slot)
{
    SDL_Renderer *renderer = display->renderer;
    TTF_Font *font = display->font[font_slot];
    SDL_Color color_ = { color >> 24, color >> 16, color >> 8, color };

    if (font == NULL) {
        return 0;
    }

    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Blended(font, str, color_);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return 1;
}

void ClearScreen(const Display *display, uint32_t color)
{
    SDL_Renderer *renderer = display->renderer;
    uint8_t r = color >> 24, g = color >> 16, b = color >> 8, a = color;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);

    color = display->pencolor;
    r = color >> 24, g = color >> 16, b = color >> 8, a = color;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void PenColor(Display *display, uint32_t color)
{
    uint8_t r = color >> 24, g = color >> 16, b = color >> 8, a = color;

    display->pencolor = color;
    SDL_SetRenderDrawColor(display->renderer, r, g, b, a);
}

void DrawLine(const Display *display, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(display->renderer, x1, y1, x2, y2);
}

void DrawPoint(const Display *display, int x, int y)
{
    SDL_RenderDrawPoint(display->renderer, x, y);
}

void FlipDisplay(const Display *display)
{
    SDL_RenderPresent(display->renderer);
}

void Delay(uint32_t msec)
{
    SDL_Delay(msec);
}

