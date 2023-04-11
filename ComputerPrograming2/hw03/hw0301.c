#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

// Please enter the search target: in the beginning
// Found 1 time(s)
// Gen 1:1 In the beginning God created the heavens and the earth.

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

// {"chapter":1,"verse":1,"text":"In the beginning God created the heavens and the earth.","translation_id":"ASV","book_id":"Gen","book_name":"Genesis"}

int countTheTarget(FILE *pFILE, char *target)
{
    char str[1000];
    int32_t count = 0;
    while (fgets(str, 1000, pFILE) != NULL)
    {
        for (int i = 0; i < strlen(str); i++)
        {
            str[i] = tolower(str[i]);
        }
        if (strstr(str, target) != NULL)
        {
            count++;
        }
    }
    return count;
}

int printTheLine(FILE *pFILE, char *target)
{
    char oriStr[1000] = {0};
    char str[1000] = {0};
    char book_id[10] = {0};
    char text[1000] = {0};
    char *pstr, *pend;
    int chapter = 0;
    int verse = 0;
    int32_t count = 0;
    while (fgets(str, 1000, pFILE) != NULL)
    {
        strcpy(oriStr, str);
        for (int i = 0; i < strlen(str); i++)
        {
            str[i] = tolower(str[i]);
        }

        if (strstr(str, target) != NULL)
        {
            memset(book_id, 0, 10);
            memset(text, 0, 1000);
            pstr = strstr(oriStr, "\"chapter\":") + 10;
            chapter = strtol(pstr, &pend, 10);
            pstr = strstr(oriStr, "\"verse\":") + 8;
            verse = strtol(pstr, &pend, 10);
            pstr = strstr(oriStr, "\"text\":\"") + 8;

            for (int i = 0; pstr[0] != '\"'; i++)
            {
                text[i] = pstr[0];
                pstr++;
            }
            pstr = strstr(oriStr, "\"book_id\":\"") + 11;
            for (int i = 0; pstr[0] != '\"'; i++)
            {
                book_id[i] = pstr[0];
                pstr++;
            }

            count++;
            printf("%d. %s %d:%d %s\n", count, book_id, chapter, verse, text);
        }
    }
    return count;
}

int main()
{
    // get the search target
    char target[50] = {0};
    FILE *pFile = NULL;
    printf("Please enter the search target:");
    if (fgets(target, 50, stdin) == NULL)
    {
        perror("Error\n");
        return 0;
    }
    removeEnterOrCleanBuffer(target);

    // open the bible
    if ((pFile = fopen("bible.txt", "r")) == NULL)
    {
        printf("File could not be opened!\n");
        return 0;
    }

    printf("count %d time(s)\n", countTheTarget(pFile, target));
    rewind(pFile);
    printTheLine(pFile, target);
    fclose(pFile);
    return 0;
}