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

int mystrsplit(char ***pppList, int *pCounter, const char *pStr, const char *pSeparator)
{
    int tmp = 0;
    int counter = 0;
    int sts = 0;
    char oriStr[99999];
    char *poriStr;
    char *tmpStr;
    char *list[999][999];
    char *sep;
    int str_l = 0;

    // put the String in buffer
    for (int i = 0; pStr[i] != 0; i++)
    {
        oriStr[i] = pStr[i];
        str_l++;
    }
    poriStr = oriStr;

    // check if the pseperator is space or not
    if (*pSeparator == 0)
    {
        sts = 1;
    }

    // when *pSeparator is 0
    if (sts == 1)
    {

        // ignore space on the bot
        // put a spcce on the bot
        for (int i = str_l; i > 0; i--)
        {
            str_l = i;
            if (isspace(poriStr[i]))
            {
                poriStr[i] = 0;
            }
            else
            {
                break;
            }
        }
        poriStr[str_l] = ' ';

        // ignore space on the top
        for (int i = 0;; i++)
        {
            if (isspace(poriStr[0]))
            {
                poriStr++;
            }
            else
            {
                break;
            }
        }

        // use a ptr to store start point of each string
        // when meet seperator, trans it to zeor and store the startptr to the array and put it to the next point
        // if meet space continuously, dont store
        // break whan meet zero
        tmpStr = poriStr;
        int tmp = 0;
        while (poriStr[0] != 0)
        {
            if (isspace(poriStr[0]))
            {
                poriStr[0] = 0;
                if (tmp == 0)
                {
                    (*list)[counter] = tmpStr;
                    counter++;
                }
                poriStr++;
                tmpStr = poriStr;
                tmp = 1;
            }
            else
            {
                tmp = 0;
                poriStr++;
            }
        }
    }

    else
    {
        // use a ptr to store start point of each string
        // when meet seperator, trans it to zeor and store the startptr to the array and put it to the next point
        // break whan meet zero
        tmpStr = poriStr;
        while (poriStr[0] != 0)
        {
            if (strspn(poriStr, pSeparator) != 0)
            {
                poriStr[0] = 0;
                (*list)[counter] = tmpStr;
                counter++;
                poriStr++;
                tmpStr = poriStr;
                if ((poriStr[1] == 0) && (poriStr[0] != 0))
                {
                    (*list)[counter] = tmpStr;
                    counter++;
                }
            }
            else
            {
                if (poriStr[1] == 0)
                {
                    (*list)[counter] = tmpStr;
                    counter++;
                }
                poriStr++;
            }
        }
    }

    // prepare space for *ppplist and (*pppList)[i]
    // copy the content to the array
    *pppList = malloc(counter * sizeof(char **));
    for (int i = 0; i < counter; i++)
    {
        (*pppList)[i] = malloc(strlen((*list)[i]) * sizeof(char));
        strncpy((*pppList)[i], (*list)[i], strlen((*list)[i]));
    }
    *pCounter = counter;

    return 0;
}

int main()
{
    char **splitList;
    int counter;
    char inputStr[1000] = {0}, changeTonStr[1000] = {0}, outputStr[1000] = {0};
    printf("input: ");
    fgets(inputStr, 1000, stdin);
    removeEnterOrCleanBuffer(inputStr);
    strcpy(changeTonStr, inputStr);
    for (int i = 0; i < strlen(changeTonStr); i++)
    {
        if (changeTonStr[i] == '-' || changeTonStr[i] == ' ')
        {
            switch (changeTonStr[i - 1])
            {
            case '1':
                changeTonStr[i - 1] = '7';
                break;
            case '2':
                changeTonStr[i - 1] = '1';
                break;
            case '3':
                changeTonStr[i - 1] = '2';
                break;
            case '4':
                if (changeTonStr[i - 2] == 'p' || changeTonStr[i - 2] == 't' || changeTonStr[i - 2] == 'k')
                    changeTonStr[i - 1] = '8';
                else if (changeTonStr[i - 2] == 'h')
                {
                    changeTonStr[i - 2] = '*';
                    changeTonStr[i - 1] = '2';
                }
                break;
            case '5':
                changeTonStr[i - 1] = '7';
                break;
            case '7':
                changeTonStr[i - 1] = '3';
                break;
            case '8':
                if (changeTonStr[i - 2] == 'p' || changeTonStr[i - 2] == 't' || changeTonStr[i - 2] == 'k')
                    changeTonStr[i - 1] = '4';
                else if (changeTonStr[i - 2] == 'h')
                {
                    changeTonStr[i - 2] = '*';
                    changeTonStr[i - 1] = '3';
                }
                break;
            }
        }
    }

    mystrsplit(&splitList, &counter, changeTonStr, " -");

    for (int i = 0; i < counter; i++)
    {
        int len = strlen(splitList[i]);
        if (splitList[i][len - 2] == '*')
        {
            splitList[i][len - 2] = splitList[i][len - 1];
            splitList[i][len - 1] = 0;
        }
        strcat(outputStr, splitList[i]);
        if (splitList[i][strlen(splitList[i]) - 1] != '.')
            strcat(outputStr, ".");
        strcat(outputStr, " ");
    }
    strcat(outputStr, inputStr);
    printf("output: %s\n", outputStr);
    for (int i = 0; i < strlen(outputStr); i++)
    {
        if (outputStr[i] == ' ')
            outputStr[i] = '+';
    }

    char command[1000] = "wget -q -O out.wav https://hapsing.ithuan.tw/bangtsam?taibun=";

    strcat(command, outputStr);
    // printf("%s\n",command);
    system(command);
    printf("out.wav has been generated.\n");
    return 0;
}