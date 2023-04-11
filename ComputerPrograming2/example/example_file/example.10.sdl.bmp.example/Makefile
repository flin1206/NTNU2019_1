CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

all: bmp_display.c
	gcc bmp_display.c -o bmp_display $(CFLAGS)
clean:
	rm example
