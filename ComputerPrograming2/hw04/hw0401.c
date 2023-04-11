/** \file
  This program is used to apply Visual Cryptography on bmp file.
  Which will turn it to gray scale only and make it 2*2 bigger.
  By using 4 pixel to represent one pixel.
  */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

/** \mainpage
   This program is used to apply Visual Cryptography on bmp file.
  Which will turn it to gray scale only and make it 2*2 bigger.
  By using 4 pixel to represent one pixel.
*/

/**
 * This structure is used to store the header information of an bmp file
 */
struct _sBmpHeader
{
    char bm[2]; ///< store BM
    uint32_t size; ///< BMP size
    uint32_t reserve; ///< BMP reserve
    uint32_t offset;///< BMP reserve
    uint32_t header_size;///< BMP header_size
    uint32_t width;///< BMP width
    uint32_t height;///< BMP height
    uint16_t planes;///< BMP planes
    uint16_t bpp;///< BMP bpp
    uint32_t compression;///< BMP compression
    uint32_t bitmap_size;///< BMP bitmap_size
    uint32_t hres;///< BMP hres
    uint32_t vres;///< BMP vres
    uint32_t used;///< BMP used
    uint32_t important;///< BMP important
} __attribute__((__packed__));
typedef struct _sBmpHeader sBmpHeader;

/**
 * This function will return the header of 2*2 times of the original bmp header.
 */
sBmpHeader transheader(sBmpHeader pHeader)
{
    sBmpHeader tmp;
    tmp.bm[0] = 'B', tmp.bm[1] = 'M';
    tmp.size = (pHeader.size - 54) * 4 + 54;
    tmp.reserve = pHeader.reserve;
    tmp.offset = pHeader.offset;
    tmp.header_size = pHeader.header_size;
    tmp.width = pHeader.width * 2;
    tmp.height = pHeader.height * 2;
    tmp.planes = pHeader.planes;
    tmp.bpp = pHeader.bpp;
    tmp.compression = pHeader.compression;
    tmp.bitmap_size = pHeader.bitmap_size * 4;
    tmp.hres = pHeader.hres;
    tmp.vres = pHeader.vres;
    tmp.used = pHeader.used;
    tmp.important = pHeader.important;
    return tmp;
}
/**
* The main work start from here.
*/


int main(int argc, char *argv[])
{
    /**
     * We use four FILE stream to read or write the FILE.
     */
    FILE *pFile = NULL;
    FILE *pFileL1 = NULL;
    FILE *pFileL2 = NULL;
    FILE *pFileO = NULL;    


    /**
     * Check calidity of the input bmp FILE first.
     */
    if (argc == 1)
    {
        printf("PLEASE PROVIDE FILE\n");
        return 0;
    }

    if (argv[1][strlen(argv[0]) - 1] == '\n')
    {
        argv[1][strlen(argv[0]) - 1] = 0;
    }

    char Filename[1000] = {0};
    char FilenameL1[1000] = {0};
    char FilenameL2[1000] = {0};
    char FilenameO[1000] = {0};
    strcpy(Filename, argv[1]);

    if ((pFile = fopen(Filename, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    char *ptr = Filename;
    int c = 0;
    while (strncmp(ptr, ".bmp", 4))
    {
        FilenameL1[c] = ptr[0];
        FilenameL2[c] = ptr[0];
        FilenameO[c] = ptr[0];
        c++;
        ptr++;
    }
    /**
     * rename three FILE :
     * filename_layer1.bmp
     * filename_layer2.bmp
     * filename_overlap.bmp
     */
    strcat(FilenameL1, "_layer1.bmp");
    strcat(FilenameL2, "_layer2.bmp");
    strcat(FilenameO, "_overlap.bmp");/// combine layer1 and layer 2

    if ((pFileL1 = fopen(FilenameL1, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    if ((pFileL2 = fopen(FilenameL2, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    if ((pFileO = fopen(FilenameO, "wb")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    sBmpHeader header;
    fread(&header, sizeof(header), 1, pFile);
    sBmpHeader header2 = transheader(header);
    fwrite(&header2, sizeof(header), 1, pFileL1);
    fwrite(&header2, sizeof(header), 1, pFileL2);
    fwrite(&header2, sizeof(header), 1, pFileO);
    srand(time(NULL));
    while (!feof(pFile))
    {
        uint8_t original[999999] = {0};
        uint8_t modifiedl1[999999] = {0};
        uint8_t modifiedl2[999999] = {0};
        uint8_t modifiedO[999999] = {0};
        uint32_t count = header.width * 3;
        fread(original, 1, header.width * 3, pFile);
        for (size_t i = 0; i < count; i = i + 3)
        {
            /// trans them to gray mode
            uint32_t gray = 0.299 * original[i + 2] + 0.587 * original[i + 1] + 0.114 * original[i];
            int x = rand() % 2;
            if (gray > 128)
            {
                /// determined the color of the pixel and apply Visual Cryptography
                if (x == 0)
                {
                    for (size_t j = 0; j < 3; j++)
                    {
                        modifiedl1[6 * i + j] = 0;
                        modifiedl1[6 * i + 3 + j] = 255;
                        modifiedl1[header2.width * 3 + 2 * i + j] = 255;
                        modifiedl1[header2.width * 3 + 2 * i + 3 + j] = 0;
                        modifiedl2[6 * i + j] = 0;
                        modifiedl2[6 * i + 3 + j] = 255;
                        modifiedl2[header2.width * 3 + 2 * i + j] = 255;
                        modifiedl2[header2.width * 3 + 2 * i + 3 + j] = 0;
                        modifiedO[2 * i + j] = 0;
                        modifiedO[2 * i + 3 + j] = 255;
                        modifiedO[header2.width * 3 + 2 * i + j] = 255;
                        modifiedO[header2.width * 3 + 2 * i + 3 + j] = 0;
                    }
                }
                else
                {
                    for (size_t j = 0; j < 3; j++)
                    {
                        modifiedl1[6 * i + j] = 255;
                        modifiedl1[6 * i + 3 + j] = 0;
                        modifiedl1[header2.width * 3 + 2 * i + j] = 0;
                        modifiedl1[header2.width * 3 + 2 * i + 3 + j] = 255;
                        modifiedl2[6 * i + j] = 255;
                        modifiedl2[6 * i + 3 + j] = 0;
                        modifiedl2[header2.width * 3 + 2 * i + j] = 0;
                        modifiedl2[header2.width * 3 + 2 * i + 3 + j] = 255;
                        modifiedO[6 * i + j] = 255;
                        modifiedO[6 * i + 3 + j] = 0;
                        modifiedO[header2.width * 3 + 2 * i + j] = 0;
                        modifiedO[header2.width * 3 + 2 * i + 3 + j] = 255;
                    }
                }
            }
            else
            {
                if (x == 0)
                {
                    for (size_t j = 0; j < 3; j++)
                    {
                        modifiedl1[6 * i + j] = 255;
                        modifiedl1[6 * i + 3 + j] = 0;
                        modifiedl1[header2.width * 3 + 2 * i + j] = 0;
                        modifiedl1[header2.width * 3 + 2 * i + 3 + j] = 255;
                        modifiedl2[6 * i + j] = 0;
                        modifiedl2[6 * i + 3 + j] = 255;
                        modifiedl2[header2.width * 3 + 2 * i + j] = 255;
                        modifiedl2[header2.width * 3 + 2 * i + 3 + j] = 0;
                        modifiedO[2 * i + j] = 0;
                        modifiedO[2 * i + 3 + j] = 0;
                        modifiedO[header2.width * 3 + 2 * i + j] = 0;
                        modifiedO[header2.width * 3 + 2 * i + 3 + j] = 0;
                    }
                }
                else
                {
                    for (size_t j = 0; j < 3; j++)
                    {
                        modifiedl1[6 * i + j] = 0;
                        modifiedl1[6 * i + 3 + j] = 255;
                        modifiedl1[header2.width * 3 + 2 * i + j] = 255;
                        modifiedl1[header2.width * 3 + 2 * i + 3 + j] = 0;
                        modifiedl2[6 * i + j] = 255;
                        modifiedl2[6 * i + 3 + j] = 0;
                        modifiedl2[header2.width * 3 + 2 * i + j] = 0;
                        modifiedl2[header2.width * 3 + 2 * i + 3 + j] = 255;
                        modifiedO[6 * i + j] = 0;
                        modifiedO[6 * i + 3 + j] = 0;
                        modifiedO[header2.width * 3 + 2 * i + j] = 0;
                        modifiedO[header2.width * 3 + 2 * i + 3 + j] = 0;
                    }
                }
            }
        }
        /// write the pixel on the file
        fwrite(modifiedO, 1, header2.width * 3 * 2, pFileO);
        fwrite(modifiedl1, 1, header2.width * 3 * 2, pFileL1);
        fwrite(modifiedl2, 1, header2.width * 3 * 2, pFileL2);
    }
    fclose(pFile);
    fclose(pFileO);
    fclose(pFileL1);
    fclose(pFileL2);
    return 0;
}