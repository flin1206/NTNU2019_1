CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm
all: example.c
    gcc example.c -o example $(CFLAGS)
clean:
    rm example
