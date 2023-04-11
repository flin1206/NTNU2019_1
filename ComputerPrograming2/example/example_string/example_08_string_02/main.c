#include <stdio.h>

int main()
{
    char    char_array[] = "Hello";

    printf( "%s (%lu)\n", char_array, sizeof( char_array ) );

    for( size_t i = 0 ; i < sizeof( char_array ) ; i++ )
    {
        printf( "%d %c\n", char_array[i], char_array[i] );
    }

    printf( "%s (%lu)\n", char_array + 1, sizeof( char_array + 1 ) );
    printf( "%s (%lu)\n", char_array - 1, sizeof( char_array - 1 ) );

    char_array[0] = 'W';
    printf( "%s (%lu)\n", char_array, sizeof( char_array ) );

    return 0;
}
