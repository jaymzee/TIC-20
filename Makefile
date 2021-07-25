CC = gcc
CFLAGS = -g -Wall -I/usr/include/lua5.2
LFLAGS = -llua5.2 -lSDL2 -lSDL2_ttf

tic20 : main.c screen.c lua.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
