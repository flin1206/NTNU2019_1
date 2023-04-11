#include <stdio.h>
#include <string.h>

int main()
{
    const char *s1 = "Happy New Year";
    const char *s2 = "Happy New Year";
    const char *s3 = "Happy XMAS";

    printf( "s1: %s\ns2: %s\ns3: %s\n\n", s1, s2, s3 );

    printf( "strcmp( s1, s2 ) = %d\n", strcmp( s1, s2 ) );
    printf( "strcmp( s1, s3 ) = %d\n", strcmp( s1, s3 ) );
    printf( "strcmp( s2, s3 ) = %d\n", strcmp( s2, s3 ) );

    printf( "strncmp( s1, s3, 6 ) = %d\n", strncmp( s1, s3, 6 ) );
    printf( "strncmp( s1, s3, 7 ) = %d\n", strncmp( s1, s3, 7 ) );
    printf( "strncmp( s3, s1, 7 ) = %d\n", strncmp( s3, s1, 7 ) );

    return 0;
}
