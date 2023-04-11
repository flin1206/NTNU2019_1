#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

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

struct option long_options[] =
    {
        {"linenum", 1, NULL, 'w'},
        {"help", no_argument, NULL, 1},
        {"color", 1, NULL, 'h'},
        {"language", 1, NULL, 'o'},
        {0, 0, 0, 0},
};

typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} element;

void printHelp()
{
    printf("usage:\n");
    printf("  ./fin01 [options]\n");
    printf("    -w: the width of the output figure. (Default: 1024)\n");
    printf("    -h: the height of the output figure. (Default: 768)\n");
    printf("    -o: the output file name. (Default: output.bmp)\n");
    printf("    --help:   Modifies an Album tag\n");
}

double countDis(int AX, int AY, int BX, int BY)
{
    return sqrt(pow(AX - BX, 2) + pow(AY - BY, 2));
}

int main(int argc, char *argv[])
{

    /*     printf( "argc: %d\n", argc );

        for( int32_t i = 0 ; i < argc ; i++ )
        {
            printf( "argv[%d]: %s\n", i, argv[i] );
        }

        puts( "---" );
         */
    // getopt_long

    int32_t c = 0;
    int32_t index = 0, optW = 0, optH = 0, optO = 0;
    long width = 1024, height = 768;
    char outputName[1000] = {0};

    while ((c = getopt_long(argc, argv, "w:h:o:", long_options, &index)) != -1)
    {
        // printf("index: %d\n", index);
        switch (c)
        {
        case 'w':
            // printf("option: -w, %s\n", optarg);
            optW = 1;
            width = atol(optarg);
            break;
        case 'h':
            // printf("option: -h, %s\n", optarg);
            optH = 1;
            height = atol(optarg);
            break;
        case 'o':
            // printf("option: -o, %s\n", optarg);
            optO = 1;
            strcpy(outputName, optarg);
            break;
        case 1:
            printHelp();
            return 0;
        default:
            printf("error\n");
            break;
        }
    }
    if (optO == 0)
        strcpy(outputName, "output.bmp");

    FILE *pFile = NULL;

    if ((pFile = fopen(outputName, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    sBmpHeader header;
    header.bm[0] = 'B';
    header.bm[1] = 'M';
    header.size = width * height * 3 + 54;
    header.reserve = 0;
    header.offset = 54;
    header.header_size = 40;
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bpp = 24;
    header.compression = 0;
    header.bitmap_size = width * height;
    header.hres = 9449;
    header.vres = 9449;
    header.used = 0;
    header.important = 0;
    // print_bmp_header(&header);
    fwrite(&header, sizeof(header), 1, pFile);

    element tl, tr, bl, br;
    printf("Please enter (R,G,B) in the top left pixel:");
    scanf("%hhd,%hhd,%hhd", &tl.r, &tl.g, &tl.b);
    printf("Please enter (R,G,B) in the top right pixel:");
    scanf("%hhd,%hhd,%hhd", &tr.r, &tr.g, &tr.b);
    printf("Please enter (R,G,B) in the bottom left pixel:");
    scanf("%hhd,%hhd,%hhd", &bl.r, &bl.g, &bl.b);
    printf("Please enter (R,G,B) in the bottom right pixel:");
    scanf("%hhd,%hhd,%hhd", &br.r, &br.g, &br.b);

    element elementMap[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double toprdis = countDis(i, j, width, height);
            double topldis = countDis(i, j, width, 0);
            double butrdis = countDis(i, j, 0, height);
            double butldis = countDis(i, j, 0, 0);
            double dissum = toprdis + topldis + butrdis + butldis;
            elementMap[i][j].r = tl.r * (toprdis + butrdis + butldis) / dissum +
                                 tr.r * (topldis + butrdis + butldis) / dissum +
                                 bl.r * (toprdis + topldis + butrdis) / dissum +
                                 br.r * (toprdis + topldis + butldis) / dissum;
            elementMap[i][j].g = tl.g * (toprdis + butrdis + butldis) / dissum +
                                 tr.g * (topldis + butrdis + butldis) / dissum +
                                 bl.g * (toprdis + topldis + butrdis) / dissum +
                                 br.g * (toprdis + topldis + butldis) / dissum;
            elementMap[i][j].b = tl.b * (toprdis + butrdis + butldis) / dissum +
                                 tr.b * (topldis + butrdis + butldis) / dissum +
                                 bl.b * (toprdis + topldis + butrdis) / dissum +
                                 br.b * (toprdis + topldis + butldis) / dissum;
            fwrite(&elementMap[i][j], 1, sizeof(elementMap[i][j]), pFile);
        }
    }
    printf("Done\n");
    fclose(pFile);
}