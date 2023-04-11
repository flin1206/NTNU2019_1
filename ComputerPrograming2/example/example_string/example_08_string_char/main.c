#include <stdio.h>
#include <stdint.h>

int main()
{
    char    c = 'a';

    printf( "Print by character %c\n", c );
    printf( "Print by integer %d\n", c );
    printf( "Print by HEX %02X\n", c );
    printf( "Print by hex %02x\n", c );

    return 0;
}
