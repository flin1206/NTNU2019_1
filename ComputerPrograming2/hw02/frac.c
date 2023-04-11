#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "frac.h"


void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
    // math procedure
    sMixedNumber num;
    num.x = (r1.x*r2.y) + (r1.y*r2.x) + (r1.intpart + r2.intpart)*r1.y*r2.y;
    num.y = r1.y * r2.y;
    
    // reduction of a fraction
    if(abs(num.x) > abs(num.y))
    {
        for(int i = 2; i < (abs(num.x)+1); i++)
        {
            if((num.x%i==0)&(num.y%i==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        }
    }
    else
    {
       for(int i = 2; i < (abs(num.y)+1); i++)
        {
            if( ( num.x %i == 0)&(num.y % i ==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        } 
    }
    
    // makes if fits format
    if((num.x<0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if((num.x>0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if(num.x == 0)
    {
        num.y = 1;
    }
    if(num.y==0)
    {
        return ;
    }
    num.intpart = num.x / num.y;
    num.x = num.x % num.y;
    if((num.x < 0)&&(num.intpart != 0))
    {
        num.x = num.x*-1;
    }

    // return the value
    (*pNumber).intpart = num.intpart;
    (*pNumber).x = num.x;
    (*pNumber).y = num.y;


    return;
}
void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
    //num 1 / num 2 = x / y = r1.x/r1.y - r2.x/r2.y
    sMixedNumber num;
    num.x = (r1.x*r2.y) - (r1.y*r2.x) + (r1.intpart - r2.intpart)*r1.y*r2.y;
    num.y = r1.y * r2.y;
    if(abs(num.x) > abs(num.y))
    {
        for(int i = 2; i < (abs(num.x)+1); i++)
        {
            if((num.x%i==0)&(num.y%i==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        }
    }
    else
    {
       for(int i = 2; i < (abs(num.y)+1); i++)
        {
            if( ( num.x %i == 0)&(num.y % i ==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        } 
    }

    // reduction of a fraction
    if((num.x<0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if((num.x>0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if(num.x == 0)
    {
        num.y = 1;
    }

    // makes if fits format
    num.intpart = num.x / num.y;
    num.x = num.x % num.y;
    if((num.x < 0)&&(num.intpart != 0))
    {
        num.x = num.x*-1;
    }

    // return the value
    (*pNumber).intpart = num.intpart;
    (*pNumber).x = num.x;
    (*pNumber).y = num.y;
    return;
}
void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
    //num 1 / num 2 = x / y = r1.x/r1.y * r2.x/r2.y
    sMixedNumber num;
    num.x = (r1.x + r1.y * r1.intpart) * (r2.x + r2.y * r2.intpart) ;
    num.y = r1.y * r2.y;

    // reduction of a fraction
    if(abs(num.x) > abs(num.y))
    {
        for(int i = 2; i < (abs(num.x)+1); i++)
        {
            if((num.x%i==0)&(num.y%i==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        }
    }
    else
    {
       for(int i = 2; i < (abs(num.y)+1); i++)
        {
            if( ( num.x %i == 0)&(num.y % i ==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        } 
    }
    
    // makes if fits format
    if((num.x<0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if((num.x>0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if(num.x == 0)
    {
        num.y = 1;
    }

    if(num.y==0)
    {
        return ;
    }
    num.intpart = num.x / num.y;
    num.x = num.x % num.y;
    if((num.x < 0)&&(num.intpart != 0))
    {
        num.x = num.x*-1;
    }

    // return the value
    (*pNumber).intpart = num.intpart;
    (*pNumber).x = num.x;
    (*pNumber).y = num.y;
    return ;
}
void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2)
{
    //num 1 / num 2 = x / y = r1.x/r1.y * r2.y/r2.x
    sMixedNumber num;
    num.x = (r1.x + r1.y * r1.intpart) * r2.y;
    num.y = r1.y * (r2.x + r2.y * r2.intpart);

    // reduction of a fraction
    if(abs(num.x) > abs(num.y))
    {
        for(int i = 2; i < (abs(num.x)+1); i++)
        {
            if((num.x%i==0)&(num.y%i==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        }
    }
    else
    {
       for(int i = 2; i < (abs(num.y)+1); i++)
        {
            if( ( num.x %i == 0)&(num.y % i ==0))
            {
                num.x = num.x/i;
                num.y = num.y/i;
                i--;
            }
        } 
    }

    // makes if fits format
    if((num.x<0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if((num.x>0)&&(num.y<0))
    {
        num.x = -num.x;
        num.y = -num.y;
    }else if(num.x == 0)
    {
        num.y = 1;
    }
    if(num.y==0)
    {
        return ;
    }
    num.intpart = num.x / num.y;
    num.x = num.x % num.y;
    if((num.x < 0)&&(num.intpart != 0))
    {
        num.x = num.x*-1;
    }

    // return the value
    (*pNumber).intpart = num.intpart;
    (*pNumber).x = num.x;
    (*pNumber).y = num.y;
    return ;
}
void mixed_shift( sMixedNumber pNumber[],int32_t from , int32_t *size)
{
    for(int i = from; i < (*size-1); i++ )
    {
        pNumber[i] = pNumber[i+1];
    }
    *size = *size - 1;
}
void array_shift( char *array,int32_t from , int32_t *size )
{
    if((*size - from) > 1)
    {
        for(int i = from; i < (*size-1); i++ )
        {
            array[i] = array[i+1];
        }
    }
    *size = *size - 1;
}
int mystrsplit(char ***pppList , int *pCounter , const char *pStr, const char *pSeparator)
{
    int tmp = 0;
    int counter = 0;
    int sts = 0;
    char oriStr[4096];
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
 


