#include <stdio.h>
#include <stdint.h>

void display_bits_signed( int32_t );
void display_bits_unsigned( uint32_t );

int main()
{
    int32_t     a = 100;
    uint32_t    b = 100;

    printf( "signed   100 = " );
    display_bits_signed( a );
    printf( "unsigned 100 = " );
    display_bits_unsigned( b );

    a = -100;
    printf( "signed  -100 = " );
    display_bits_signed( a );

    return 0;
}

void display_bits_signed( int32_t value )
{
    uint32_t    mask = 1 << 31;

    for( size_t i = 0 ; i < 32 ; i++ )
    {
        if( value & mask )
        {
            printf( "1" );
        }
        else
        {
            printf( "0" );
        }

        if( i % 8 == 7 )
        {
            printf( " " );
        }

        mask = mask >> 1;
    }

    putchar( '\n' );

    return;
}

void display_bits_unsigned( uint32_t value )
{
    uint32_t    mask = 1 << 31;

    for( size_t i = 0 ; i < 32 ; i++ )
    {
        if( value & mask )
        {
            printf( "1" );
        }
        else
        {
            printf( "0" );
        }

        if( i % 8 == 7 )
        {
            printf( " " );
        }

        mask = mask >> 1;
    }

    putchar( '\n' );

    return;
}

