#include <stdio.h>
#include <stdint.h>

#if defined( _DEBUG_ )
    #define debug_print(fmt, ...) \
            fprintf( stderr, "%s:%d:%s(): " fmt, \
                    __FILE__, __LINE__, __func__, __VA_ARGS__ )
#else
    #define debug_print(fmt, ...) {}
#endif

int main()
{
    printf( "Hello, I am Po-Wen Chi.\n" );
    
    int32_t a = 1;
    
    debug_print( "This is a debug message %d.\n", a );
    
    return 0;
}
