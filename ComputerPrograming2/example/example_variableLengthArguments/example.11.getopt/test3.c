#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>

struct option long_options[] = 
{  
     { "linenum",  0, NULL, 'n' },  
     { "color", 0, NULL, 'c' },  
     { "language", 1, NULL, 'l' },  
     {  0, 0, 0, 0},  
};  

int main( int argc, char *argv[] )
{
    printf( "argc: %d\n", argc );
    
    for( int32_t i = 0 ; i < argc ; i++ )
    {
        printf( "argv[%d]: %s\n", i, argv[i] );
    }
    
    puts( "---" );
    
    // getopt_long
    
    int32_t c = 0;
    int32_t index = 0;
    
    while ( ( c = getopt_long( argc, argv, "ncl:", long_options, &index ) ) != -1 )
    {
        printf( "index: %d\n", index );
        switch( c )
        {
            case 'n':
                printf( "option: -n\n" );
                break;
            case 'c':
                printf( "option: -c\n" );
                break;
            case 'l':
                printf( "option: -l, %s\n", optarg );
                break;
            case '?':
                printf( "option: ?\n" );
                break;
            default:
                printf( "option: unknown\n" ); 
                break;
        }
    }
    
    return 0;
}