#include <stdio.h>

void reverse( const char * );

int main()
{
    char    str[64] = {0};

    printf( "Please enter a string:\n" );
    fgets( str, 64, stdin );

    printf( "Reverse the string:\n" );
    reverse( str );

    return 0;
}

void reverse( const char *ptr )
{
    if( '\0' == *ptr )
    {
        return;
    }
    else
    {
        reverse( ptr + 1 );
        putchar( *ptr );
        return;
    }
}
