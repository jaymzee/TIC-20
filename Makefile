CC = gcc
CFLAGS = -g -I/usr/include/lua5.2
LFLAGS = -llua5.2

vpath %.c src
vpath %.h src

.PHONY: clean

tic20 : main.c display.c tic.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f tic20
