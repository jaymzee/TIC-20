#include <stdio.h>
#include <signal.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "display.h"
#include "tic.h"
#include "colors.h"

extern volatile uint8_t ram[];

void intHandler(int dummy) {
    ram[0x55aa] = 0;
}

int main(int argc, char *argv[])
{
    struct Display *display = NULL;
    const char *filename = "main.lua";

    // process program arguments
    if (argc > 1) {
        filename = argv[1];
    }

    ram[0x55aa] = 1;
    signal(SIGINT, intHandler);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF Init: %s\n", TTF_GetError());
        return 1;
    }
    display = CreateDisplay("TIC-20", GREEN, SDL_RENDERER_ACCELERATED);
    if (display == NULL) {
        return 1;
    }

    // execute lua file
    int status = TicExec(filename, display);
    if (status) {
        fprintf(stderr, "%s\n", TicError());
    }

    // cleanup and exit
    DestroyDisplay(display);
    SDL_Quit();

    // return the exit code that lua returned
    return status;
}
