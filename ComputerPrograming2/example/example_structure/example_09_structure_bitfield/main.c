#include <stdio.h>
#include <stdint.h>

typedef struct card
{
    uint8_t    face : 4;
    uint8_t    suit : 2;
    uint8_t    color: 1;
} Card;

typedef struct example
{
    uint32_t    a : 13;
    uint32_t      : 19;
    uint32_t    b : 4;
} Example;

typedef struct example2
{
    uint32_t    a : 13;
    uint32_t      : 0;  // skip the remaining bits of the storage unit.
    uint32_t      : 4;
} Example2;

int main()
{
    printf("sizeof \"Card\" = %lu\n", sizeof( Card ) );
    printf("sizeof \"Example\" = %lu\n", sizeof( Example ) );
    printf("sizeof \"Example2\" = %lu\n", sizeof( Example2 ) );

    Card    poker = {0};
    poker.face = 10;
    poker.suit = 2;
    poker.color = 1;

    printf( "%02X\n", poker );

    return 0;
}
