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

    // get the puzzle and steps FILENAME
    char puzzleFilename[1000], stepsFilename[1000];
    printf("Please enter the image: ");
    if (fgets(puzzleFilename, sizeof(puzzleFilename), stdin) == NULL)
    {
        printf("Error!\n");
        return 0;
    }
    removeEnterOrCleanBuffer(puzzleFilename);
    printf("Please enter the puzzle: ");
    if (fgets(stepsFilename, sizeof(stepsFilename), stdin) == NULL)
    {
        printf("Error!\n");
        return 0;
    }
    removeEnterOrCleanBuffer(stepsFilename);

    // readthem
    if ((pFile = fopen(puzzleFilename, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    if ((pFile2 = fopen(stepsFilename, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    // get the information of the puzzle
    int width, height, stepNum;
    fscanf(pFile2, "%d%d%d", &width, &height, &stepNum);
    int puzzle[stepNum][width][height];
    for (int i = 0; i < stepNum; i++)
        for (int j = 0; j < height; j++)
            for (int k = 0; k < width; k++)
                fscanf(pFile2, "%d", &puzzle[i][j][k]);

    pclose(pFile2);

    int countStep = 0;

    while (countStep != stepNum)
    {
        FILE *pOut = NULL;
        sBmpHeader header;
        char outFilename[20];
        sprintf(outFilename, "%d", countStep + 1);
        strcat(outFilename, ".bmp");
        if ((pOut = fopen(outFilename, "wb")) == NULL)
        {
            printf("File could not be opened!\n");
            return 0;
        }
        fread(&header, sizeof(header), 1, pFile);
        fwrite(&header, sizeof(header), 1, pOut);

        int opperand = 0;
        for (int j = 0; j < height; j++)
        {
            for (int l = 0; l < header.height / height; l++)
            {
                for (int k = 0; k < width; k++)
                {

                    if ((height % 2 == 1) && (j != 0))
                    {
                        opperand = width + 1;
                    }
                    else if (j != 0)
                    {
                        opperand = 2;
                    }
                    else
                    {
                        opperand = 0;
                    }

                    if ((height % 2 == 1) && (opperand > 0))
                    {
                        opperand += j-1;
                    }

                    long int offset = ((puzzle[countStep][j][k] - 1) / width) * header.width * header.height / height + l * header.width;

                    offset += (puzzle[countStep][j][k] - 1 + opperand) % width * header.width / width;

                    // long int offset = ((puzzle[countStep][j][k] - 1) / width) * header.width * header.height / height + l * header.width + (puzzle[countStep][j][k] - 1) % width * header.width / width;

                    fseek(pFile, sizeof(header) + offset * 3, SEEK_SET);
                    int bufferSize = header.width * 3 / width;
                    uint8_t buffer[bufferSize];
                    if (puzzle[countStep][j][k] == 0)
                    {
                        for (int i = 0; i < bufferSize; i++)
                        {
                            buffer[i] = 255;
                        }
                    }
                    else
                    {
                        fread(&buffer, sizeof(buffer), 1, pFile);
                    }
                    fwrite(&buffer, sizeof(buffer), 1, pOut);
                }
            }
        }
        fseek(pFile, 0, SEEK_SET);
        fclose(pOut);
        for (int i = 0; i < 20; i++)
        {
            outFilename[i] = 0;
        }
        countStep++;
    }

    return 0;
}
