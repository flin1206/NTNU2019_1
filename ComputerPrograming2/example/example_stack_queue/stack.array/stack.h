#pragma once

#include <stdint.h>
#include <stdlib.h>

#define MAX_SIZE    (100)

typedef struct _sStack
{
    size_t  top;
    int32_t elements[MAX_SIZE];
} sStack;

void init_stack( sStack * );
int32_t is_empty_stack( sStack * );
int32_t is_full_stack( sStack * );
int32_t push_stack( sStack *, int32_t );
int32_t pop_stack( sStack *, int32_t * );

