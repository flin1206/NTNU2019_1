#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t neg = -2;
    uint32_t zero = 0;

    if( neg < zero )
    {
        printf( "-2 is less than zero.\n" );
    }
    else
    {
        printf( "-2 is not less than zero.\n" );
    }
    
    return 0;
}
