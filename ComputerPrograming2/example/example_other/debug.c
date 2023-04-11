#include <stdio.h>

int main()
{
    printf( "Hello World!!\n" );
    
#ifdef __DEBUG__
    printf( "debug!!\n" );
#endif
    
    return 0;
}
