#include <stdio.h>
#include <stdint.h>

#define MAX(a,b) ( a > b ? a:b )

static inline int32_t max( int32_t a, int32_t b ) 
{
    return a > b ? a : b;
}

int main()
{
    int32_t a = 100;
    int32_t b = 90;
    int32_t c = 0;
    
    c = MAX( a, b );
    
    printf( "max = %d\n", c );
    
    c = max( a, b );
    
    printf( "max = %d\n", c );
    
    return 0;
}
