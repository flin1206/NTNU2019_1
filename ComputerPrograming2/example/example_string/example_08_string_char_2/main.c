#include <stdio.h>
#include <stdint.h>

int main()
{
    char    c = 'A';

    for( size_t i = 0 ; i < 26 ; i++ )
    {
        printf( "%c\n", c + i );
    }

    return 0;
}
