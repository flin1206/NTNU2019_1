#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "linuxlist.h"

#define ROW_SIZE    (12)
#define COLUMN_SIZE (15)

// Start point: 0, 0
// End point: ROW_SIZE - 1, COLUMN_SIZE - 1
typedef struct _sMazeStack
{
    int32_t pos_row;
    int32_t pos_column;
    int32_t direction;
    int32_t maze[ROW_SIZE][COLUMN_SIZE];
    
    struct list_head list;
} sMazeStack;

void init_maze( int32_t [ROW_SIZE][COLUMN_SIZE] );

sMazeStack *alloc_maze( int32_t, int32_t, int32_t );
void free_maze( sMazeStack * );

int32_t         push_maze_stack( sMazeStack * );
sMazeStack *    pop_maze_stack( void );
sMazeStack *    get_top_maze_stack( void );
int32_t         is_maze_stack_empty( void );

int32_t         get_maze_status( int32_t, int32_t );
void            set_maze_status( int32_t, int32_t, int32_t );

void            print_maze( void );
void            print_maze_path( void );
