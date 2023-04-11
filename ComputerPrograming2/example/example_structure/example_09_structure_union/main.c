#include <stdio.h>
#include <stdint.h>

typedef union number
{
    int8_t  x;
    int32_t y;
    double  z;
}Number;

int main()
{
    Number  value;
    uint8_t *ptr = NULL;

    printf( "sizeof \"Number\" is %lu\n", sizeof( Number ) );

    value.x = 100;
    printf( "value.x = %d\n", value.x );
    printf( "value.y = %d\n", value.y );
    printf( "value.z = %f\n", value.z );

    ptr = ( uint8_t * )&value;
    printf( "Hex of value:\n" );

    for( size_t i = 0 ; i < sizeof( Number ) ; i++ )
    {
        printf( "%02X ", *( ptr + i ) );
    }
    printf( "\n\n" );

    value.y = 257;
    printf( "value.x = %d\n", value.x );
    printf( "value.y = %d\n", value.y );
    printf( "value.z = %f\n", value.z );

    ptr = ( uint8_t * )&value;
    printf( "Hex of value:\n" );

    for( size_t i = 0 ; i < sizeof( Number ) ; i++ )
    {
        printf( "%02X ", *( ptr + i ) );
    }
    printf( "\n\n" );

    value.z = 100.0;
    printf( "value.x = %d\n", value.x );
    printf( "value.y = %d\n", value.y );
    printf( "value.z = %f\n", value.z );

    ptr = ( uint8_t * )&value;
    printf( "Hex of value:\n" );

    for( size_t i = 0 ; i < sizeof( Number ) ; i++ )
    {
        printf( "%02X ", *( ptr + i ) );
    }
    printf( "\n\n" );

    return 0;
}
