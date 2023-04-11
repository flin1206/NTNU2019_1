#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "frac.h"

int main()
{

    char **elementList, *calculateElementList;
    int countElement = 0, countCalculateElement = 0;
    char *seperator1 = "+-/*";
    sMixedNumber *mixnum;
    char input[2048];
    printf("Q:");
    scanf("%s", input);

    // use calculate element to seperarte the input
    // store eachof them to array
    mystrsplit(&elementList, &countElement, input, seperator1);
    for (int i = 0; i < strlen(input); i++)
    {
        if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/'))
        {
            countCalculateElement++;
        }
    }
    calculateElementList = malloc(countCalculateElement * sizeof(char));
    mixnum = malloc(countElement * sizeof(sMixedNumber));
    for (int i = 0, j = 0; i < strlen(input); i++)
    {
        if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/'))
        {
            calculateElementList[j] = input[i];
            j++;
        }
    }

    // when the first char is input, make it become -1 * ...
    int firstNegative = 0;
    if (input[0] == '-')
    {
        firstNegative = 1;
        calculateElementList[0] = '*';
        mixnum[0].intpart = -1;
        mixnum[0].x = 0;
        mixnum[0].y = 1;
    }

    // trans string to number
    // store the number to the struture array
    for (int i = firstNegative; i < countElement; i++)
    {
        char *pHead = elementList[i];
        char *pEnd;
        if (elementList[i][0] == '\\')
        {
            mixnum[i].intpart = 0;
            int tmp = 1;
            for (int j = 0; elementList[i][j] != '{'; j++)
            {
                tmp++;
            }
            pHead += tmp;
            mixnum[i].x = (int)strtol(pHead, &pEnd, 0);
            pHead += 3;
            mixnum[i].y = (int)strtol(pHead, &pEnd, 0);
        }
        else
        {
            mixnum[i].intpart = (int)strtol(pHead, &pEnd, 0);
            int tmp = 1;
            for (int j = 0; elementList[i][j] != '{'; j++)
            {
                tmp++;
            }
            pHead += tmp;
            mixnum[i].x = (int)strtol(pHead, &pEnd, 0);
            pHead += 3;
            mixnum[i].y = (int)strtol(pHead, &pEnd, 0);
        }
    }

    // calculate * /
    for (int i = 0; i < countCalculateElement; i++)
    {
        if (calculateElementList[i] == '*')
        {
            mixed_mul(&mixnum[i + 1], mixnum[i], mixnum[i + 1]);
            mixed_shift(mixnum, i, &countElement);
            array_shift(calculateElementList, i, &countCalculateElement);
            // printf("*%d\\frac{%d}{%d}\n",mixnum[i].intpart,mixnum[i].x,mixnum[i].y);
            i--;
        }
        else if (calculateElementList[i] == '/')
        {
            mixed_div(&mixnum[i + 1], mixnum[i], mixnum[i + 1]);
            mixed_shift(mixnum, i, &countElement);
            array_shift(calculateElementList, i, &countCalculateElement);
            // printf("/%d\\frac{%d}{%d}\n",mixnum[i].intpart,mixnum[i].x,mixnum[i].y);
            i--;
        }
    }

    // calculate + -
    for (int i = 0; i < countCalculateElement; i++)
    {
        if (calculateElementList[i] == '+')
        {
            mixed_add(&mixnum[i + 1], mixnum[i], mixnum[i + 1]);
            mixed_shift(mixnum, i, &countElement);
            array_shift(calculateElementList, i, &countCalculateElement);
            // printf("+%d\\frac{%d}{%d}\n",mixnum[i].intpart,mixnum[i].x,mixnum[i].y);
            i--;
        }
        else if (calculateElementList[i] == '-')
        {
            mixed_sub(&mixnum[i + 1], mixnum[i], mixnum[i + 1]);
            mixed_shift(mixnum, i, &countElement);
            array_shift(calculateElementList, i, &countCalculateElement);
            // printf("-%d\\frac{%d}{%d}\n",mixnum[i].intpart,mixnum[i].x,mixnum[i].y);
            i--;
        }
    }

    printf("A: %d\\frac{%d}{%d}\n", mixnum[0].intpart, mixnum[0].x, mixnum[0].y);

    return 0;
}