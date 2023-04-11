#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "mysplit.h"

int mystrsplit(char ***pppList , int *pCounter , const char *pStr, const char *pSeparator)
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
    for(int i = 0; pStr[i] != 0; i++)
    {
        oriStr[i] = pStr[i];
        str_l++;
    }
    poriStr = oriStr;

    // check if the pseperator is space or not 
    if(*pSeparator == 0)
    {
        sts = 1;
    }

    // when *pSeparator is 0
    if( sts == 1 )
    {

        // ignore space on the bot
        // put a spcce on the bot
        for(int i = str_l; i > 0 ; i-- )
        {
            str_l = i;
            if(isspace(poriStr[i]))
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
        for(int i = 0;;i++)
        {
            if(isspace(poriStr[0]))
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
        while(poriStr[0] != 0)
        {
            if(isspace(poriStr[0])) 
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
        while(poriStr[0]!=0)
        {
            if(strspn(poriStr,pSeparator)!=0)
            {
                poriStr[0] = 0;
                (*list)[counter] = tmpStr;
                counter ++;
                poriStr++;
                tmpStr = poriStr;
                if((poriStr[1]==0)&&(poriStr[0]!=0))
                {
                    (*list)[counter] = tmpStr;
                    counter++;
                }               
            }
            else
            { 
                if(poriStr[1]==0)
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
    *pppList = malloc(counter*sizeof(char**));
    for (int i = 0; i < counter; i++) 
    {
        (*pppList)[i] = malloc(strlen((*list)[i])*sizeof(char));     
        strncpy((*pppList)[i] ,(*list)[i],strlen((*list)[i]));
    } 
    *pCounter = counter;

    return 0;
}


       