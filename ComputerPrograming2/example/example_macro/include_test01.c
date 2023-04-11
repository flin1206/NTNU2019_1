#include <stdio.h>
#include <stdint.h>

int32_t max( int32_t, int32_t );

int main()
{
    int32_t a = 0;
    int32_t b = 1;
    
    printf( "max: %d\n", max( a, b ) );
    
    return 0;
}
