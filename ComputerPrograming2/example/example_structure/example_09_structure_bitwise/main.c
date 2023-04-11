#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t a = 128;
    int32_t b = 127;

    printf( "a = %d (%08X)\nb = %d (%08X)\n", a, a, b, b );
    printf( "a & b = %d (%08X)\n", a & b, a & b );
    printf( "a | b = %d (%08X)\n", a | b, a | b );
    printf( "a ^ b = %d (%08X)\n", a ^ b, a ^ b );
    printf( "~a = %d (%08X)\n", ~a, ~a );
    printf( "a << 1 = %d (%08X)\n", a << 1, a << 1 );
    printf( "a >> 1 = %d (%08X)\n", a >> 1, a >> 1 );

    return 0;
}
