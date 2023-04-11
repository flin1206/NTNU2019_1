#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;

int main() 
{ 

	// retutns zero on success else non-zero 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
		printf("error initializing SDL: %s\n", SDL_GetError()); 
	} 
	SDL_Window* win = SDL_CreateWindow("Hello World", // creates a window 
									SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, 
									1920, 1080, 0); 

	// triggers the program that controls 
	// your graphics hardware and sets flags 
	Uint32 render_flags = SDL_RENDERER_ACCELERATED; 

	// creates a renderer to render our images 
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags); 

	// creates a surface to load an image into the main memory 
	SDL_Surface* surface; 

	// please provide a path for your image 
	//surface = IMG_Load("maldives.bmp"); 
	
	FILE	*pFile = NULL;
    
    if( ( pFile = fopen( "maldives.bmp", "rb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    sBmpHeader	header;
    fread( &header, sizeof( header ), 1, pFile );
    
    uint8_t *pPixels = NULL;
    pPixels = malloc( header.bitmap_size );
    fread( pPixels, 1, header.bitmap_size, pFile );
    
    /*
    for (int32_t i = 0 ; i < header.bitmap_size; i += 3 )
    {
        uint8_t tmp = pPixels[i];
        pPixels[i] = pPixels[i+2];
        pPixels[i+2] = tmp;
    }
    */
    
    fclose( pFile );
    
    surface = SDL_CreateRGBSurfaceFrom( ( void * ) pPixels, header.width, header.height, 24, 3 * header.width,
                                        0x000000ff, 0x0000ff00, 0x00ff0000, 0);

	// loads image to our graphics hardware memory. 
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface); 

	// clears main-memory 
	SDL_FreeSurface(surface); 

	int end = 0;

	// annimation loop 
	while (!end) { 
		SDL_Event event; 

		// Events mangement 
		while (SDL_PollEvent(&event)) { 
			switch (event.type) { 

			case SDL_QUIT: 
				// handling of close button 
				end = 1; 
				break; 
			} 
		} 

		// clears the screen 
		SDL_RenderClear(rend); 
		SDL_RenderCopy(rend, tex, NULL, NULL); 

		// triggers the double buffers 
		// for multiple rendering 
		SDL_RenderPresent(rend); 

		// calculates to 60 fps 
		SDL_Delay(1000 / 60); 
	} 

	// destroy texture 
	SDL_DestroyTexture(tex); 

	// destroy renderer 
	SDL_DestroyRenderer(rend); 

	// destroy window 
	SDL_DestroyWindow(win); 
	return 0; 
} 
