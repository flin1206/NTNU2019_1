#include <stdio.h>
#include "maze_stack.h"

static int32_t maze[ROW_SIZE][COLUMN_SIZE] = {0};
struct list_head maze_stack;

void init_maze( int32_t input[ROW_SIZE][COLUMN_SIZE] )
{
    for( int32_t i = 0 ; i < ROW_SIZE ; i++ )
    {
        for( int32_t j = 0 ; j < COLUMN_SIZE ; j++ )
        {
            maze[i][j] = input[i][j];
        }
    }
    
    maze_stack.next = &maze_stack;
    maze_stack.prev = &maze_stack;
    
    return;
}

sMazeStack *alloc_maze( int32_t row, int32_t column )
{
    sMazeStack  *pNewOne = calloc( 1, sizeof( sMazeStack ) );
    
    pNewOne -> pos_row = row;
    pNewOne -> pos_column = column;

    return pNewOne;
}

void free_maze( sMazeStack *pMaze )
{
    free( pMaze );
    return;
}

int32_t push_maze_stack( sMazeStack *pNew )
{
    list_add( &( pNew -> list ), &maze_stack );
    return 0;
}

sMazeStack * pop_maze_stack( void )
{
    if( is_maze_stack_empty() )
    {
        return NULL;
    }
    
    sMazeStack *pStack = list_first_entry( &maze_stack, sMazeStack, list );
    list_del( &( pStack -> list ) );
    return pStack;
}

int32_t is_maze_stack_empty( void )
{
    return list_empty( &maze_stack );
}

int32_t get_maze_status( int32_t pow, int32_t column )
{
    return maze[pow][column];
}

void set_maze_status( int32_t pow, int32_t column, int32_t val )
{
    maze[pow][column] = val;
}

void print_maze( void )
{
    for( int32_t i = 0 ; i < ROW_SIZE; i++ )
    {
        for( int32_t j = 0 ; j < COLUMN_SIZE; j++ )
        {
            printf( "%2d", maze[i][j] );
        }
        printf( "\n" );
    }
}
