#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h"

int main()
{
    sStack  stack;
    
    init_stack( &stack );
    
    for( int32_t i = 0 ; i < 50 ; i++ )
    {
        push_stack( &stack, i );
    }
    
    int32_t val = 0;
    while( !is_empty_stack( &stack ) )
    {
        pop_stack( &stack, &val );
        printf( "%d ", val );
    }    
    
    return 0;
}
