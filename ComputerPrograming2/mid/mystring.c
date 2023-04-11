#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "mystring.h"


char *mystrtok_r(char *str, const char *delim, char **saveptr)
{
    static char *mystrtokEnd = NULL;

    if(str != NULL)
    {
        // when delim = NULL, return str
        if (delim[0] == 0)
        {
            return str;
        }

        // ignore delim on the top
        for(int i = 0;;i++)
        {
            if(strspn(str,delim)==0)
            {
                break;
            }
            else
            {
                str++;
            }
        }

        //store the pointer of the string in mystrtokEnd    
        mystrtokEnd = str;

        // find the delim and trans it to 0
        // put the static pointer to the next position of delim
        // if didnt find correspondind delim return str
        int tmp = 0;
        while(mystrtokEnd[0]!=0)
        {
            if(strcspn(mystrtokEnd,delim)==0) 
            {
                mystrtokEnd[0] = 0;
                mystrtokEnd++;
                tmp = 1;
            }
            else
            {
                if(tmp > 0)
                {
                    break;
                }
                mystrtokEnd++;
            }
        }
        *saveptr = mystrtokEnd;
        return str;
    }
    else
    {
        // store the start point
        // if the first char = 0, return NULL
        char *mystrtoksta = mystrtokEnd;
        if(mystrtokEnd[0] == 0)
        {
            *saveptr = NULL;
            return NULL;
        }

        // find the delim and trans it to 0
        // put the static pointer to the next position of delim
        // after find,return start point
        int tmp = 0;
        while(mystrtokEnd[0]!=0)
        {
            if(strcspn(mystrtokEnd,delim)==0) 
            {
                mystrtokEnd[0] = 0;
                mystrtokEnd++;
                tmp = 1;
            }
            else
            {
                if(tmp > 0)
                {
                    break;
                }
                mystrtokEnd++;
            }
        }
        *saveptr = mystrtokEnd;
        return mystrtoksta;
    }
}
