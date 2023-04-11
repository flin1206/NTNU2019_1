#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE	*pFile = NULL;
    
    if( ( pFile = fopen( "maldives.bmp", "rb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    // Identifier
    
    char	bm[2];
    
    fread( bm, 2, 1, pFile );
    printf( "ID: %c%c\n", bm[0], bm[1] );
    
    // Size
    
    uint32_t size;
    
    fread( &size, 4, 1, pFile );
    printf( "Size: %u\n", size );
    
    // Reserved
    
    uint32_t reserve;
    
    fread( &reserve, 4, 1, pFile );
    printf( "Reserve: %u\n", reserve );
    
    // Offset
    
    uint32_t offset;
    
    fread( &offset, 4, 1, pFile );
    printf( "Offset: %u\n", offset );
    
    // Header Size
    
    uint32_t header_size;
    
    fread( &header_size, 4, 1, pFile );
    printf( "Header Size: %u\n", header_size );
    
    // Width
    
    uint32_t width;
    
    fread( &width, 4, 1, pFile );
    printf( "Width: %u\n", width );
    
    // Height
    
    uint32_t height;
    
    fread( &height, 4, 1, pFile );
    printf( "Height: %u\n", height );
    
    // Planes
    
    uint16_t planes;
    
    fread( &planes, 2, 1, pFile );
    printf( "Planes: %u\n", planes );
    
    // Bits Per Pixel
    
    uint16_t bpp;
    
    fread( &bpp, 2, 1, pFile );
    printf( "Bits Per Pixel: %u\n", bpp );
    
    // Compression
    
    uint32_t compression;
    
    fread( &compression, 4, 1, pFile );
    printf( "Compression: %u\n", compression );
    
    // Bitmap Data Size 
    
    uint32_t bitmap_size;
    
    fread( &bitmap_size, 4, 1, pFile );
    printf( "Bitmap Data Size: %u\n", bitmap_size );
    
    // H-Resolution
    
    uint32_t hres;
    
    fread( &hres, 4, 1, pFile );
    printf( "H-Resolution: %u\n", hres );
    
    // V-Resolution
    
    uint32_t vres;
    
    fread( &vres, 4, 1, pFile );
    printf( "V-Resolution: %u\n", vres );
    
    // Used colors
    
    uint32_t used;
    
    fread( &used, 4, 1, pFile );
    printf( "Used Colors: %u\n", used );
    
    // Important colors
    
    uint32_t important;
    
    fread( &important, 4, 1, pFile );
    printf( "Important Colors: %u\n", important );
    
            
    fclose( pFile );
    
    
    return 0;
}