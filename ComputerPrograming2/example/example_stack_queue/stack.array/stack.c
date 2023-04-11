#include <stdio.h>
#include "stack.h"

void init_stack( sStack *pS )
{
    pS -> top = 0;
    return ;
}

int32_t is_empty_stack( sStack *pS )
{
    return ( pS -> top <= 0 );
}

int32_t is_full_stack( sStack *pS )
{
    return ( pS -> top >= MAX_SIZE );
}

int32_t push_stack( sStack *pS, int32_t val )
{
    if( is_full_stack( pS ) )
    {
        printf( "Stack is full. %d cannot be pushed.\n", val );
        return -1;
    }
    
    pS -> elements[ pS -> top ] = val;
    pS -> top += 1;
    return 0;
}

int32_t pop_stack( sStack *pS, int32_t *pVal )
{
    if( is_empty_stack( pS ) )
    {
        printf( "Stack is empty. Nothing can be popped.\n" );
        return -1;
    }
    
    pS -> top -= 1;
    *pVal = pS -> elements[ pS -> top ];    
    return 0;
}

