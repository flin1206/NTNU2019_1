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

int chechHeader(sBmpHeader header)
{
    if ((header.bm[0] != 'B') || (header.bm[1] != 'M'))
        return 0;
    if (header.width * header.height * header.bpp / 8 + header.offset != header.size)
        return 0;
    if ((header.header_size != 40) || (header.planes != 1))
        return 0;
    if (header.bpp != 24)
        return 0;
    if (header.bitmap_size != header.width * header.height * header.bpp / 8)
        return 0;
    return 1;
}
sBmpHeader trans_16bmp_header(sBmpHeader pHeader)
{
    sBmpHeader tmp;
    tmp.bm[0] = 'B', tmp.bm[1] = 'M';
    tmp.reserve = pHeader.reserve;
    tmp.offset = pHeader.offset;
    tmp.header_size = pHeader.header_size;
    tmp.width = pHeader.width;
    tmp.height = pHeader.height;
    tmp.planes = pHeader.planes;
    tmp.compression = pHeader.compression;
    tmp.hres = pHeader.hres;
    tmp.vres = pHeader.vres;
    tmp.used = pHeader.used;
    tmp.important = pHeader.important;
    tmp.bpp = 16;
    tmp.size = tmp.width * tmp.height * tmp.bpp / 8 + tmp.offset;
    tmp.bitmap_size = tmp.width * tmp.height * tmp.bpp / 8;
    return tmp;
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

    sBmpHeader header, header16;
    fread(&header, sizeof(header), 1, pFile);
    if (chechHeader(header) == 0)
    {
        printf("error\n");
        return 0;
    }
    header16 = trans_16bmp_header(header);
    fwrite(&header16, sizeof(header), 1, pFile2);

    while (!feof(pFile))
    {
        uint8_t original[3] = {0};
        uint16_t modified = 0;
        fread(original, 1, 3, pFile);

        for (size_t i = 0; i < 3; i++)
        {
            original[i] = original[i] / 8;
        }

        modified = original[0] + original[1] * 32 + original[2] * 1024;
        fwrite(&modified, 2, 1, pFile2);
    }

    fclose(pFile);
    fclose(pFile2);

    return 0;
}
