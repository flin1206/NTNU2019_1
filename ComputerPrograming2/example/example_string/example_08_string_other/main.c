#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

int main()
{
    const char str[] = "Hello World";

    printf( "str: \"%s\"\n", str );
    printf( "sizeof( str ) = %ld\n", sizeof( str ) );
    printf( "strlen( str ) = %ld\n\n", strlen( str ) );

    if( ( fopen( "abc.txt", "r" ) ) == NULL )
    {
        printf( "errno = %d\n", errno );
        printf( "error: %s\n", strerror( errno ) );
    }

    return 0;
}
