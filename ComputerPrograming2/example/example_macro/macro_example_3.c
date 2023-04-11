#include <stdio.h>
#include <stdint.h>

#define SIZE 10
#define INIT_ARRAY(x) for( int32_t i = 0 ; i < SIZE ; i++ ) \
                    {\
                        x[i] = i;\
                    }
#define PRINT_ARRAY(x) for( int32_t i = 0 ; i < SIZE ; i++ ) \
                    {\
                        printf( "%02d ", x[i] );\
                    }\
                    printf( "\n" );
#define ADD(x,y) x+y

int main()
{
    int32_t array[SIZE] = {0};
    
    INIT_ARRAY( array );
    PRINT_ARRAY( array );
    
    for( int32_t i = 0 ; i < SIZE ; i++ )
    {
        array[i] = ADD( array[i], 3 ) * 10;
    }
    
    PRINT_ARRAY( array );
    
    return 0;
}
