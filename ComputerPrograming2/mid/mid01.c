#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <ctype.h>
#include "mystring.h"

int main()
{
    char str3[] = "This.is.www.gitbook.net.website";
    char *rest;
    char *token = mystrtok_r(str3, ".", &rest);
    int32_t i = 0;
    // printf("%s\n",token);

    while (token != NULL)
    {
        printf("%d:%s rest : %s\n", i, token, rest);
        token = mystrtok_r(NULL, ".", &rest);
        i++;
    }

    return 0;

}