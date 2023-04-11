#include <stdio.h>
#include "queue.h"

void init_queue( sQueue *pQ )
{
    pQ -> front = 0;
    pQ -> end = 0;
    return ;
}

int32_t is_empty_queue( sQueue *pQ )
{
    return ( pQ -> front == pQ -> end );
}

int32_t is_full_queue( sQueue *pQ )
{
    return ( ( pQ -> end + 1 ) % MAX_SIZE == pQ -> front );
}

int32_t enqueue( sQueue *pQ, int32_t val )
{
    if( is_full_queue( pQ ) )
    {
        printf( "queue is full. %d cannot be enqueued.\n", val );
        return -1;
    }
    
    pQ -> elements[ pQ -> end ] = val;
    pQ -> end = ( pQ -> end + 1 ) % MAX_SIZE;
    return 0;
}

int32_t dequeue( sQueue *pQ, int32_t *pVal )
{
    if( is_empty_queue( pQ ) )
    {
        printf( "queue is empty. Nothing can be dequeued.\n" );
        return -1;
    }
        
    *pVal = pQ -> elements[ pQ -> front ]; 
    pQ -> front = ( pQ -> front + 1 ) % MAX_SIZE;
    return 0;
}

