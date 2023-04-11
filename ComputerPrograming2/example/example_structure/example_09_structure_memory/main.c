#include <stdio.h>
#include <stdint.h>

struct  student
{
    char        name[64];
    uint8_t     height;
    uint8_t     weight;
    uint8_t     gender;
    uint16_t    id;

    uint8_t grade[8];
};

int main()
{
    struct student  alice;

    printf( "Sizeof \"struct student\" is %ld\n", sizeof( struct student ) );

    printf( "&( alice ) = %p\n", &( alice ) );
    printf( "&( alice.name ) = %p\n", &( alice.name ) );
    printf( "&( alice.height ) = %p\n", &( alice.height ) );
    printf( "&( alice.weight ) = %p\n", &( alice.weight ) );
    printf( "&( alice.gender ) = %p\n", &( alice.gender ) );
    printf( "&( alice.id ) = %p\n", &( alice.id ) );
    printf( "&( alice.grade ) = %p\n", &( alice.grade ) );

    return 0;
}
