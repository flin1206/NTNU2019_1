#include <stdio.h>
#include <stdint.h>

int main()
{
    char    str[32] = {0};

    /*
    printf( "Please enter a string:\n" );
    scanf( "%s", str );
    printf( "scanf: %s\n", str );
    */

    printf( "Please enter a string:\n" );
    fgets( str, 32, stdin );
    printf( "fgets: %s", str );

    putchar( 67 );
    printf( "\n" );

    puts( str );

    int32_t a = 2 , b = 3;
    snprintf( str, 32, "%d + %d = %d\n", a, b, a + b );
    puts( str );

    int32_t c = 0, d = 0, e = 0;

    sscanf( str, "%d + %d = %d", &c, &d, &e );
    printf( "c = %d, d = %d, e = %d\n", c, d, e );

    return 0;
}
