#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    char    *str01 = "99.99K Gold.";
    char    *strPtr01;
    char    *str02 = "12345abc";
    char    *strPtr02;

    double  d = strtod( str01, &strPtr01 );

    printf( "strtod example:\n%s\n", str01 );
    printf( "\tDouble value %.2f\n", d );
    printf( "\tThe remaining string is \"%s\"\n", strPtr01 );

    int64_t l = strtol( str02, &strPtr02, 10 );

    printf( "strtol example (Base:10):\n%s\n", str02 );
    printf( "Long value %ld\n", l );
    printf( "\tThe remaining string is \"%s\"\n", strPtr02 );

    l = strtol( str02, &strPtr02, 16 ); // <-- Memory Leak

    printf( "strtol example (Base:16):\n%s\n", str02 );
    printf( "Long value %ld\n", l );
    printf( "\tThe remaining string is \"%s\"\n", strPtr02 );

    return 0;
}
