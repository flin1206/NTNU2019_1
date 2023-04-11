#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "queue.h"

int main()
{
    sQueue  queue;
    
    init_queue( &queue );
    
    for( int32_t i = 0 ; i < 101 ; i++ )
    {
        enqueue( &queue, i );
    }
    
    int32_t val = 0;
    while( !is_empty_queue( &queue ) )
    {
        dequeue( &queue, &val );
        printf( "%d ", val );
    }   
    
    return 0;
}
