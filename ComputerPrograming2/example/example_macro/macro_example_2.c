#include <stdio.h>
#include <stdint.h>

#define AND &&
#define OR ||
#define GOOD_THRESHOLD 80
#define FAIL_THRESHOLD 60
#define IS_GREAT(x) ( x >= GOOD_THRESHOLD )
#define IS_SOSO(x) ( x >= FAIL_THRESHOLD AND x < GOOD_THRESHOLD )
#define IS_FAILED(x) ( x < FAIL_THRESHOLD )
#define GREAT printf( "GREAT!!\n" ) 
#define SOSO  printf( "SOSO!!\n" )
#define ALERT printf( "Alert!!\n" ) 

void check( int32_t score )
{
    printf( "%d: ", score );    
    
    if( IS_GREAT( score ) )
    {
        GREAT;
    }
    
    if( IS_SOSO( score ) )
    {
        SOSO;
    }
    
    if( IS_FAILED( score ) )
    {
        ALERT;
    }
    
    return;
}

int main()
{
    check( 90 );
    check( 70 );
    check( 59 );
    
    return 0;
}
