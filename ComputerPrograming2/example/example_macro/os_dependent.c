#include <stdio.h>

int main()
{
    printf( "Hello, I am Po-Wen Chi.\n" );
    printf( "My computer's OS is " );
    
#ifdef OS_LINUX
    printf( "Linux :)\n" );
#endif

#ifdef OS_WIN
    printf( "MS Windows :(\n" );
#endif
    
    return 0;
}
