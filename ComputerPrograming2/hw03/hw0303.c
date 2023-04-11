#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct _sBmpHeader
{
    char bm[2];
    uint32_t size;
    uint32_t reserve;
    uint32_t offset;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t bitmap_size;
    uint32_t hres;
    uint32_t vres;
    uint32_t used;
    uint32_t important;
} __attribute__((__packed__));
typedef struct _sBmpHeader sBmpHeader;

typedef struct
{
    int32_t x;
    int32_t y;
} pixel_t;

void print_bmp_header(sBmpHeader *pHeader)
{
    printf("ID: %c%c\n", pHeader->bm[0], pHeader->bm[1]);
    printf("Size: %u\n", pHeader->size);
    printf("Reserve: %u\n", pHeader->reserve);
    printf("Offset: %u\n", pHeader->offset);
    printf("Header Size: %u\n", pHeader->header_size);
    printf("Width: %u\n", pHeader->width);
    printf("Height: %u\n", pHeader->height);
    printf("Planes: %u\n", pHeader->planes);
    printf("Bits Per Pixel: %u\n", pHeader->bpp);
    printf("Compression: %u\n", pHeader->compression);
    printf("Bitmap Data Size: %u\n", pHeader->bitmap_size);
    printf("H-Resolution: %u\n", pHeader->hres);
    printf("V-Resolution: %u\n", pHeader->vres);
    printf("Used Colors: %u\n", pHeader->used);
    printf("Important Colors: %u\n", pHeader->important);

    return;
}

double countDistance(pixel_t point1, pixel_t point2)
{
    return sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
}

void removeEnterOrCleanBuffer(char *str)
{
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = 0;
    else
    { 
        int32_t c = 0;
        while ((c = fgetc(stdin)) != '\n' && c != EOF)
        {
        }
    }
}


int main()
{
    FILE *pFile = NULL;
    FILE *pFile2 = NULL;

    // store the input and output FILENAME
    char inFilename[1000], outFilename[1000];
    printf("Please enter the input image name: ");
    if( fgets( inFilename, sizeof( inFilename ), stdin ) == NULL )
    {
        printf( "Error!\n" );
        return 0;
    }
    removeEnterOrCleanBuffer(inFilename);
    printf("Please enter the output image name: ");
    if( fgets( outFilename, sizeof( outFilename ), stdin ) == NULL )
    {
        printf( "Error!\n" );
        return 0;
    }
    removeEnterOrCleanBuffer(outFilename);

    // read and write them
    if ((pFile = fopen(inFilename, "rb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    if ((pFile2 = fopen(outFilename, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    // store the value of circleCenter and radius
    pixel_t circleCenter;
    double radius;
    printf("Please enter the center: ");
    if (scanf("(%d,%d)", &circleCenter.x, &circleCenter.y) != 2)
    {
        printf("ERROR\n");
        return 0;
    }
    printf("Please enter the radius: ");
    if (scanf("%lf", &radius) != 1)
    {
        printf("ERROR\n");
        return 0;
    }

    // 
    sBmpHeader header;
    fread(&header, sizeof(header), 1, pFile);
    fwrite(&header, sizeof(header), 1, pFile2);
    circleCenter.y = header.height - circleCenter.y;
    long int pixelNum = header.width * header.height;
    int32_t countWidth = 0, countHeight = 0;
    while (!feof(pFile))
    {
        countHeight += countWidth / header.width;
        countWidth = countWidth % header.width;
        uint8_t original[3] = {0};
        uint8_t modified[3] = {0};
        size_t count = fread(original, 1, 3, pFile);
        for (size_t i = 0; i < count; i++)
        {
            pixel_t tmp;
            tmp.x = countWidth, tmp.y = countHeight;
            if(countDistance(tmp,circleCenter) < radius )
                modified[i] = original[i];
            else
                modified[i] = 255;
        }
        fwrite(modified, count, 1, pFile2);
        countWidth++;
    }

    fclose(pFile);
    fclose(pFile2);

    return 0;
}