#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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

    display = CreateDisplay(GREEN);
    if (display == NULL) {
        return 1;
    }

    // execute lua file
    int status = TicExec(filename, display);
    if (status) {
        fprintf(stderr, "%s\n", TicError());
        // TODO: restore display but don't clear it
        exit(1);
    }

    // cleanup and exit
    DestroyDisplay(display);

    // return the exit code that lua returned
    return status;
}
