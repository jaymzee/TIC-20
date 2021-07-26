CC = gcc
CFLAGS = -g -Wall -I/mingw64/include/lua5.1
LFLAGS = -llua5.1 -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

vpath %.c src
vpath %.h src

tic20 : main.c display.c tic.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
