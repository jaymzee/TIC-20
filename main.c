#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"
#include "lua.h"
#include "colors.h"

struct Screen *screen = NULL;

int main(int argc, char *argv[])
{
    const char *filename = "main.lua";

    // process program arguments
    if (argc > 1) {
        filename = argv[1];
    }

    // Initialize SDL
    fprintf(stderr, "Initializing SDL\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF Init: %s\n", TTF_GetError());
        return 1;
    }
    fprintf(stderr, "Create Screen (windowed mode)\n");
    screen = CreateScreen(LIGHT_GRAY, SDL_RENDERER_ACCELERATED);
    if (!screen) {
        fprintf(stderr, "Create Screen failed.");
        return 1;
    }

    // execute lua file
    fprintf(stderr, "Executing %s\n", filename);
    int exitcode = LuaMain(filename);
    if (exitcode) {
        fprintf(stderr, "%s\n", GetLuaError());
    } else {
        fprintf(stderr, "Shutting down\n");
    }

    // cleanup and exit
    DestroyScreen(screen);
    SDL_Quit();

    // return the exit code that lua returned
    return exitcode;
}
