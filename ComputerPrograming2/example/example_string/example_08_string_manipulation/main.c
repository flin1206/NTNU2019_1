#include <stdio.h>
#include <string.h>

int main()
{
    char    str01[20] = "Happy ";
    char    str02[20] = "New Year ";
    char    str03[128] = {0};

    printf( "str01: \"%s\"\n", str01 );
    printf( "str02: \"%s\"\n", str02 );
    printf( "str03: \"%s\"\n", str03 );

    strncpy( str03, str01, 128 );
    printf( "str03: \"%s\"\n", str03 );

    strncat( str03, str02, 128 - 20 );
    printf( "str03: \"%s\"\n", str03 );

    return 0;
}
