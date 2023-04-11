#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mymatch.h"

int main()
{
    char **list;
    char *string = "ae age apt aqe aot auht";
    char *pattern = "a*t";

    int Counter;

    for (int i = 0; i < mymatch(&list, string, pattern); i++)
    {
        printf("%s\n", list[i]);
    }

    return 0;
}