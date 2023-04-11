#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mymatch.h"

int mymatch(char ***pppList, const char *pStr, const char *pPattern)
{
    int PatternType = 0;
    char **splitlist;
    char *empt = "";
    int splitcount = 0;
    int patlen = 0;
    // use split to trans string to word list
    mystrsplit(&splitlist, &splitcount, pStr, empt);

    // check type of pattern & count the length of pattern
    for (int i = 0;; i++)
    {
        if (pPattern[i] == '?')
        {
            PatternType = 1;
        }
        else if (pPattern[i] == '*')
        {
            PatternType = 2;
        }
        if (pPattern[i] == 0)
        {
            patlen = i;
            break;
        }
    }
    // check validity
    if (PatternType == 0)
    {
        return -1;
    }

    int count = 0;
    // a?e
    // count the number of the corresponding word in first loop
    if (PatternType == 1)
    {
        for (int i = 0; i < splitcount; i++)
        {
            int k = 0;
            for (int j = 0; j < patlen; j++)
            {
                if ((splitlist[i][j] == 0) || (strlen(pPattern) != strlen(splitlist[i])))
                {
                    break;
                }
                else if ((splitlist[i][j] == pPattern[j]) || (pPattern[j] == '?'))
                {
                    k++;
                }
            }
            if (k == patlen)
            {
                count++;
            }
        }
    }
    // a*e
    else
    {
        for (int i = 0; i < splitcount; i++)
        {
            for (int j = 0; j < patlen; j++)
            {
                if (pPattern[j] == '*')
                {
                    for (int k = patlen - 1; pPattern[k] != '*'; k--)
                    {
                        if (splitlist[i][strlen(splitlist[i]) - 1] != pPattern[k])
                        {
                            break;
                        }
                        else if (pPattern[k - 1] == '*')
                        {
                            // printf("%s\n",splitlist[i]);
                            count++;
                            break;
                        }
                    }
                }
                else if (splitlist[i][j] != pPattern[j])
                {
                    break;
                }
            }
        }
    }

    // prepare enough size
    *pppList = malloc(count * sizeof(char *));
    count = 0;

    // a?e
    // use similar way and store the word to the list
    if (PatternType == 1)
    {
        for (int i = 0; i < splitcount; i++)
        {
            int k = 0;
            for (int j = 0; j < patlen; j++)
            {
                if ((splitlist[i][j] == 0) || (strlen(pPattern) != strlen(splitlist[i])))
                {
                    break;
                }
                else if ((splitlist[i][j] == pPattern[j]) || (pPattern[j] == '?'))
                {
                    k++;
                }
            }
            if (k == patlen)
            {

                (*pppList)[count] = (char *)malloc(k * sizeof(char));
                strncpy((*pppList)[count], splitlist[i], k);
                // printf("%s\n",(*pppList)[count]);
                count++;
            }
        }
    }
    else
    {
        for (int i = 0; i < splitcount; i++)
        {
            for (int j = 0; j < patlen; j++)
            {
                if (pPattern[j] == '*')
                {
                    for (int k = patlen - 1; pPattern[k] != '*'; k--)
                    {
                        if (splitlist[i][strlen(splitlist[i]) - 1] != pPattern[k])
                        {
                            break;
                        }
                        else if (pPattern[k - 1] == '*')
                        {
                            (*pppList)[count] = (char *)malloc(strlen(splitlist[i]) * sizeof(char));
                            strncpy((*pppList)[count], splitlist[i], strlen(splitlist[i]));
                            count++;
                            break;
                        }
                    }
                }
                else if (splitlist[i][j] != pPattern[j])
                {
                    break;
                }
            }
        }
    }

    return count;
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