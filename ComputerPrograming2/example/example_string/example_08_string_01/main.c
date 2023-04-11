#include <stdio.h>

int main()
{
    char    char_array[] = "Hello";

    printf( "Character array -->\n" );
    printf( "%s\n", char_array );
    printf( "sizeof: %lu\n", sizeof( char_array ) );

    char    *char_ptr = "Hello World :)";

    printf( "Character pointer -->\n" );
    printf( "%s\n", char_ptr );
    printf( "sizeof: %lu\n", sizeof( char_ptr ) );

    return 0;
}
