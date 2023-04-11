#pragma once

#include <stdint.h>
#include <stdlib.h>

#define MAX_SIZE    (100)

typedef struct _sQueue
{
    size_t  front;
    size_t  end;
    int32_t elements[MAX_SIZE];
} sQueue;

void init_queue( sQueue * );
int32_t is_empty_queue( sQueue * );
int32_t is_full_queue( sQueue * );
int32_t enqueue( sQueue *, int32_t );
int32_t dequeue( sQueue *, int32_t * );

