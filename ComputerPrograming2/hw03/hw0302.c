#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

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
    char filename[50];
    printf("Please enter the search target:");
    if (fgets(filename, 50, stdin) == NULL)
    {
        perror("Error\n");
        return 0;
    }
    removeEnterOrCleanBuffer(filename);
    printf("Speed (0.5-2):");
    double speed = 1;
    scanf("%lf", &speed);
    if ((speed > 2) || (speed < 0.5))
    {
        printf("Error\n");
        return 0;
    }
    // open the player
    if ((pFile = fopen(filename, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }
    
    // a clock = 1000ms
    clock_t start = clock() / 1000;
    clock_t hour[2], minute[2], second[2], minsecond[2];
    clock_t from, to;
    char count[10];
    char timeline[50];
    char text[1000];
    char blank[10];
    char *ptr;

    while (!feof(pFile))
    {
        // get the required content first
        if (fgets(count, 10, pFile) == NULL)
        {
            break;
        }
        removeEnterOrCleanBuffer(count);
        if (fgets(timeline, 100, pFile) == NULL)
        {
            break;
        }
        removeEnterOrCleanBuffer(timeline);
        if (fgets(text, 1000, pFile) == NULL)
        {
            break;
        }
        removeEnterOrCleanBuffer(text);

        // store the showtime in from and to, make it divide speed
        from = ((timeline[0] - '0') * 10 + (timeline[1] - '0')) * 3600000 + ((timeline[3] - '0') * 10 + (timeline[4] - '0')) * 60000 +
               ((timeline[6] - '0') * 10 + (timeline[7] - '0')) * 1000 + (timeline[9] - '0') * 100 + (timeline[10] - '0') * 10 + (timeline[11] - '0');
        to = ((timeline[17] - '0') * 10 + (timeline[18] - '0')) * 3600000 + ((timeline[20] - '0') * 10 + (timeline[21]) - '0') * 60000 +
             ((timeline[23] - '0') * 10 + (timeline[24] - '0')) * 1000 + (timeline[26] - '0') * 100 + (timeline[27] - '0') * 10 + (timeline[28] - '0');
        from = from / speed;
        to = to / speed;

        // show the text on requireed time
        system("clear");
        while (clock() / 1000 - start < from)
        {
        }
        // printf("%s\n", timeline);
        printf("%s\n", text);
        while (clock() / 1000 - start < to)
        {
        }
        system("clear");

        if (fgets(blank, 5, pFile) == NULL)
        {
            break;
        }
    }
    pclose(pFile);
    return 0;
}