#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "maze_stack.h"

const int32_t dir[8][2] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };

int main()
{
    int32_t maze[ROW_SIZE][COLUMN_SIZE] = { { 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1}, 
                                            { 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1},
                                            { 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
                                            { 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0},
                                            { 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
                                            { 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
                                            { 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
                                            { 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                                            { 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
                                            { 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
                                            { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
                                            { 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0} };
                                            
    init_maze( maze );
    print_maze();
    
    int32_t is_reached = 0;
    int32_t pos_row = 0, pos_column = 0;
    sMazeStack *pStack = alloc_maze( pos_row, pos_column );
    
    push_maze_stack( pStack );
    
    while( !is_maze_stack_empty() && !is_reached)
    {
        pStack = pop_maze_stack();
        set_maze_status( pStack -> pos_row, pStack -> pos_column, 2 );
        
        for( int32_t d = 0 ; d < 8 ; d++ )
        {
            pos_row = pStack -> pos_row + dir[d][0];
            pos_column = pStack -> pos_column + dir[d][1];
            
            if( pos_row == ROW_SIZE - 1 && pos_column == COLUMN_SIZE - 1 )
            {
                printf( "Reach the exit!\n" );
                set_maze_status( pos_row, pos_column, 2 );
                is_reached = 1;
                break;
            }
            
            if( pos_row < ROW_SIZE && pos_row >= 0 &&
                pos_column < COLUMN_SIZE && pos_column >= 0 &&
                get_maze_status( pos_row, pos_column ) == 0 )
            {
                sMazeStack *pStackNew = alloc_maze( pos_row, pos_column );
                push_maze_stack( pStackNew );
            }
        }
    }
    
    if( is_reached == 1 )
    {
        print_maze();
    }
    else
    {
        puts( "No path." );
    }
    
    return 0;
}
