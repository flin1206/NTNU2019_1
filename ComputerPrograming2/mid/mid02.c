#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct country
{
    char CountryName[100];
    char CountryCode[100];
    char IndicatorName[100];
    char IndicatorCode[100];
    long int command1Num;
    double command2Num;
} __attribute__((__packed__));
typedef struct country scountry;

int mystrsplit(char ***pppList, int *pCounter, const char *pStr, const char *pSeparator)
{
    int tmp = 0;
    int counter = 0;
    int sts = 0;
    char oriStr[99999];
    char *poriStr;
    char *tmpStr;
    char *list[100][50];
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
int32_t menu(void)
{
    int32_t choice = 0;
    printf("--- Menu ---\n");
    printf("1) Which country has the largest population growth?\n");
    printf("2) Which country has the largest population growth rate?\n");
    printf("3) Which country has the smallest population growth , including negative growth?\n");
    printf("4) Which country has the smallest population growth rate, including negative growth?\n");
    printf("5) Which country has the largest population standard deviation?\n");
    printf("6) Which country has the smallest population standard deviation?\n");
    printf("7) Given a country name (case-insensitive), please use linear least squares method to predict the country's population in 2021.\n");
    printf("8) Exit\n");
    printf("Your choice:");
    if (scanf("%d", &choice) != 1)
        return -1;

    if (choice < 0 || choice > 8)
        return -1;

    return choice;
}

void command1(FILE *pFile)
{

    scountry country[1000];
    char c = 0;
    char *str, *endptr;
    int countryNum = 0;
    int largestCommand1Num = 0;
    char output[100] = {0};

    while (!feof(pFile))
    {
        char wholeStr[1000] = {0};
        char **list;
        int counter;
        char *sep = "\"";
        fgets(wholeStr, 1000, pFile);
        if(feof(pFile))
        {
            break;
        }
        removeEnterOrCleanBuffer(wholeStr);
        // printf("%s\n",wholeStr);
        mystrsplit(&list, &counter, wholeStr, sep);
        str = wholeStr;

        strncpy(country[countryNum].CountryName, list[1], 100);
        strncpy(country[countryNum].CountryCode, list[3], 100);
        strncpy(country[countryNum].IndicatorName, list[5], 100);
        strncpy(country[countryNum].IndicatorCode, list[7], 100);
        //printf("%s %s %s %s \n",list[1],list[3],list[5],list[7]);
        //printf("%ld %ld \n", strtol(list[counter - 2], &endptr, 10), strtol(list[9], &endptr, 10));
        country[countryNum].command1Num = strtol(list[counter - 2], &endptr, 10) - strtol(list[9], &endptr, 10);
        if (country[countryNum].command1Num > largestCommand1Num)
        {
            largestCommand1Num = country[countryNum].command1Num;
            for (int i = 0; i < 100; i++)
            {
                output[i] = country[countryNum].CountryName[i];
            }
        }

        if(feof(pFile))
        {
            break;
        }
        countryNum++;
    }

    printf("%s\n", output);
    return;
}

void command2(FILE *pFile)
{

    scountry country[1000];
    char c = 0;
    char *str, *endptr;
    int countryNum = 0;
    double largestCommand2Num = 0;
    char output[100] = {0};

    while (!feof(pFile))
    {
        char wholeStr[1000] = {0};
        char **list;
        int counter;
        char *sep = "\"";
        fgets(wholeStr, 1000, pFile);
        if(feof(pFile))
        {
            break;
        }
        removeEnterOrCleanBuffer(wholeStr);
        // printf("%s\n",wholeStr);
        mystrsplit(&list, &counter, wholeStr, sep);
        str = wholeStr;

        strncpy(country[countryNum].CountryName, list[1], 100);
        strncpy(country[countryNum].CountryCode, list[3], 100);
        strncpy(country[countryNum].IndicatorName, list[5], 100);
        strncpy(country[countryNum].IndicatorCode, list[7], 100);
        // printf("%s %s %s %s \n",list[1],list[3],list[5],list[7]);
        //printf("%ld %ld \n", strtol(list[counter - 2], &endptr, 10), strtol(list[9], &endptr, 10));
        country[countryNum].command2Num = (atoi(list[counter - 2]) - atoi(list[9])) / atoi(list[9]);
        if (country[countryNum].command1Num > largestCommand2Num)
        {
            largestCommand2Num = country[countryNum].command1Num;
            for (int i = 0; i < 100; i++)
            {
                output[i] = country[countryNum].CountryName[i];
            }
        }

        if(feof(pFile))
        {
            break;
        }
        countryNum++;
    }

    printf("%s\n", output);
    return;
}

void command3(FILE *pFile)
{

    return;
}

void command4(FILE *pFile)
{
    return;
}

void command5(FILE *pFile)
{
    return;
}

int main()
{
    FILE *pFile = NULL;

    char filename[1000];
    printf("Please enter the data name: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        printf("Error!\n");
        return 0;
    }
    removeEnterOrCleanBuffer(filename);

    // open the player
    if ((pFile = fopen(filename, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    int sTime, eTime;
    printf("Please enter the analysis start time: ");
    scanf("%d", &sTime);
    printf("Please enter the analysis end time: ");
    scanf("%d", &eTime);

    while (1)
    {

        char c = 0;
        int countC = 0;
        while (countC < 4)
        {
            c = fgetc(pFile);
            if (c == '\n')
            {
                countC++;
            }
        }

        char firstLine[1000] = {0};
        char *ptr, *endptr;
        while (1)
        {
            c = fgetc(pFile);
            if (c == '\n')
                break;
            firstLine[strlen(firstLine)] = c;
        }

        ptr = firstLine + 65;
        // printf("%ld", strtol(ptr, &endptr, 10));
        if (sTime != strtol(ptr, &endptr, 10))
        {
            printf("error time");
            return 0;
        }
        ptr = endptr + 3 + 7 * (eTime - sTime - 1);
        if (eTime != strtol(ptr, &endptr, 10))
        {
            printf("error time");
            return 0;
        }
        int32_t choice = menu();
        if (choice == -1)
        {
            continue;
        }
        else if (choice == 8)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            command1(pFile);
            break;
        case 2:
            command2(pFile);
            break;
        case 3:
            command3(pFile);
            break;
        case 4:
            command4(pFile);
            break;
        case 5:
            command5(pFile);
            break;
        default:
            break;
        }

        rewind(pFile);
    }

    fclose(pFile);

    return 0;
}