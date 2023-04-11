#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

void    char_check( int32_t );

int main()
{
    for( int32_t i = 0 ; i < 128 ; i++ )
    {
        char_check( i );
    }

    return 0;
}

void    char_check( int32_t c )
{
    printf( "Character %d:\n", c );

    if( isblank( c ) )
    {
        printf( "\t is blank.\n" );
    }

    if( isdigit( c ) )
    {
        printf( "\t is a digit.\n" );
    }

    if( isalpha( c ) )
    {
        printf( "\t is a letter.\n" );
    }

    if( isalnum( c ) )
    {
        printf( "\t is a digit or a letter.\n" );
    }

    if( isxdigit( c ) )
    {
        printf( "\t is in 0-9a-f.\n" );
    }

    if( islower( c ) )
    {
        printf( "\t is a lowercase letter.\n" );
    }

    if( isupper( c ) )
    {
        printf( "\t is an uppercase letter.\n" );
    }

    if( isspace( c ) )
    {
        printf( "\t is a space.\n" );
    }

    if( iscntrl( c ) )
    {
        printf( "\t is a control character.\n" );
    }

    if( ispunct( c ) )
    {
        printf( "\t is a punctuation symbol.\n" );
    }

    if( isprint( c ) )
    {
        printf( "\t is printable : --%c--.\n", c );
    }


    return;
}
