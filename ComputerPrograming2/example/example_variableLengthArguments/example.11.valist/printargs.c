#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

/* print all args one at a time until a negative argument is seen;
   all args are assumed to be of int type */
void printargs( int32_t arg1, ... )
{
    va_list ap;
    int32_t i;

    va_start( ap, arg1 ); 
    for ( int32_t i = arg1; i >= 0; i = va_arg( ap, int32_t ) )
    {
        printf( "%d ", i);
    }
    va_end( ap );
    putchar('\n');
    
    return;
}

int main()
{
    printargs(5, 2, 14, 84, 97, 15, -1, 48, -1);
    printargs(84, 51, -1);
    printargs(-1);
    printargs(1, -1);
    return 0;
}
