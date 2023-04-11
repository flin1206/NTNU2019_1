#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "upper_lower_api.h"

char toUpper( char c )
{
    if( c >= 'a' && c <= 'z' )
    {
        return c ^ ' ';
    }
    else
    {
        return c;
    }
}

char toLower( char c )
{
    if( c >= 'A' && c <= 'Z' )
    {
        return c ^ ' ';
    }
    else
    {
        return c;
    }
}

uint64_t util_getFdSize( int fd )
{
    struct stat statbuf;
    
    if( fstat( fd, &statbuf ) < 0 )
    {
        close( fd );
        return -1;
    }
    
    return statbuf.st_size;
}
