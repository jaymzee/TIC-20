# makefile for windows executable
#
# development environment is MSYS2 mingw64 with the packages:
#   mingw-w64-x86_64-gcc 10.3.0-2
#   mingw-w64-x86_64-clang 12.0.0-7
#   mingw-w64-x86_64-lua 5.4.2-2
#   mingw-w64-x86_64-SDL2 2.0.14-2
#   mingw-w64-x86_64-SDL2_ttf 2.0.15-1

CC = gcc
CFLAGS = -g -Wall
LFLAGS = -llua -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

vpath %.c src
vpath %.h src

.PHONY: clean

tic20: main.c display.c tic.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f tic20
