#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include "mystring.h"

// hw0103
long int mystrtol(const char *nptr, char **endptr , int base)
{
    long int returnValue = 0;
    long int len;
    long int count = 0;
    int positive = 1;
    int number[12];
    long int answer = 0;

    // get string len
    for( int i = 0; ; i++)
    {
        if(nptr[i] == 0)
        {
            len = i;
            break;
        }
    }

    // check base
    if( (( base < 2 )||( base > 36 )) && (base != 0) )
    {
        *endptr = NULL;
        return 0;
    }

    //define positive or not
    for( int i = 0; i < len; i++)
    {
        if(!isspace(nptr[i]))
        {
            // not space - means negative, + and else means positive, count record current number
            if( nptr[i] == '+' )
            {
                count = i + 1;
                positive = 1;
                break;
            }
            else if( nptr[i] == '-' )
            {
                count = i + 1;
                positive = -1;
                break;
            }
            else
            {   
                count = i;
                positive = 1;
                break;
            }
        }
    
    }

    // define base 0
    if( base == 0 )
    {
        for( int i = count; i < len; i++)
        {
            // check the first chapter 
            // 0x 0X to 16, 0 to 8, else 10
            if(isalnum( nptr[i]))
            {
                if( nptr[i] == '0' )
                {
                    if(( nptr[i+1] == 'x' )||( nptr[i+1] == 'X' ))
                    {
                        base = 16;
                        count = i + 2;
                        break;
                    }
                    else
                    {
                        base = 8;
                        count = i + 1;
                        break;
                    }
                }
                else
                {
                    count = i;
                    base = 10;
                    break;
                }
            }       
        }
    }

    int tmp = count;

    // store the valid input in the array
    for( int i = count; i < len; i++)
    {
        if( isalnum(nptr[i]) )
        {
            // below decimal 
            if( base < 11 )
            {
                if(( 47 < nptr[i] )&&( nptr[i] < base + 48 ))
                {
                    number[i-count] = nptr[i] - 48;
                }
                else
                {
                    count = i;
                    break;
                }
            }
            // 11 to 36
            else if ( base < 37 )
            {
                // 0 - 9
                if(( 47 < nptr[i] )&&( nptr[i] < 58 ))
                {
                    number[i-count] = nptr[i] - 48 ;
                }
                // a - z
                else if(( 64 < nptr[i] )&&( nptr[i] < base + 55 ))
                {
                    number[i-count] = nptr[i] - 55 ;
                }
                // A - Z
                else if(( 96 < nptr[i] )&&( nptr[i] < base + 87 ))
                {
                    number[i-count] = nptr[i] - 87 ;
                }
                else
                {
                    count = i;
                    break;
                }
            }
        }
        else
        {
            count = i;
            break;
        }   
    };

    // return endptr
    *endptr = (char *)nptr + count;

    // trans char to number
    for(int i = 0, j = count - tmp ; i < count - tmp; i++)
    {
        answer +=  number[i] * pow( base, j-1 );
        j--;
    }
    // return answer
    return answer * positive ;
    
}

// hw0104
char *mystrchr(const char *s, int c)
{
    //search from head
    for( int i = 0;;i++ )
    {
        if( c == s[i] )
        {
            return (char *)s + i;
        }
        else if( s[i] == 0 )
        {
            return NULL;
        }
    }
}

char *mystrrchr(const char *s, int c)
{
    
    if (c == '\0')
    {
        return mystrchr (s, '\0');
    }
    // find the end digit
    long int end = 0;
    for( int i = 0; i < 100;i++ )
    {
        if( s[i] == 0 )
        {
            end = i-1;
            break;
        }
    }
    // search from buttom
    for( int i = end; i >= 0 ; i--)
    {
        if( c == s[i] )
        {
            return (char *)s + i;
        }
        else if( s[i] == 0 )
        {
            return NULL;
        }
    }

}

size_t mystrspn(const char *s, const char *accept)
{
    // check if the current char has correspond char in accept
    // break when there its NULL
    for (int i = 0 ;; i++ )
    {
        if( mystrchr( accept, s[i] ) == NULL )
        {
            return i;
        }
    }
}

size_t mystrcspn(const char *s, const char *reject)
{
    // check if the current char has correspond char in reject
    // break when there its NOT NULL
    for (int i = 0 ;; i++ )
    {
        if( mystrchr( reject, s[i] ) != NULL )
        {
            return i;
        }
    }
}

char *mystrpbrk(const char *s, const char *accept)
{
    // use mystrchr to check if there is corresponding char 
    for (int i = 0 ;; i++ )
    {
        if( mystrchr( accept, s[i] ) != NULL )
        {
            for( int j = 0; ; j++ )
            {
                if( accept[j] == s[i] )
                {
                    return (char *)s + i;
                }
            }
        }
        if( s[i] == 0 )
        {
            return NULL;
        }
    }
}

char *mystrstr(const char *haystack , const char *needle)
{
    // check the corresponding needle and return the position
    for(int i = 0 ;; i++)
    {   
        for(int j = 0 ;; j++)
        {
            if(needle[j] == 0)
            {
                return (char *)haystack + i;
            }
            else if( haystack[i+j] != needle[j])
            {
                break;
            }
        }

        if( haystack[i] == 0 )
        {
            return NULL;
        }
    }
}

char *mystrtok(char *str, const char *delim)
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
            if(mystrspn(str,delim)==0)
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
            if(mystrcspn(mystrtokEnd,delim)==0) 
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
        return str;
    }
    else
    {
        // store the start point
        // if the first char = 0, return NULL
        char *mystrtoksta = mystrtokEnd;
        if(mystrtokEnd[0] == 0)
        {
            return NULL;
        }

        // find the delim and trans it to 0
        // put the static pointer to the next position of delim
        // after find,return start point
        int tmp = 0;
        while(mystrtokEnd[0]!=0)
        {
            if(mystrcspn(mystrtokEnd,delim)==0) 
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
        return mystrtoksta;
    }
}

