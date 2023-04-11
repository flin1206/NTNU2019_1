#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "maze_stack.h"

int32_t dir[8][2] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };

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
    sMazeStack *pStack = alloc_maze( pos_row, pos_column, 0 );
    
    push_maze_stack( pStack );
    
    while( !is_maze_stack_empty() && !is_reached )
    {
        pStack = get_top_maze_stack();
        set_maze_status( pStack -> pos_row, pStack -> pos_column, 2 );
        printf( "%d %d\n", pStack -> pos_row, pStack -> pos_column );
        
        if( pStack -> pos_row == ROW_SIZE - 1 && pStack -> pos_column == COLUMN_SIZE - 1 )
        {
            printf( "Reach the exit!\n" );
            is_reached = 1;
            break;
        }
        
        if( pStack -> direction == 8 )
        {
            pStack = pop_maze_stack();
            set_maze_status( pStack -> pos_row, pStack -> pos_column, 0 );
            continue;
        }
        
        pos_row = pStack -> pos_row + dir[pStack -> direction][0];
        pos_column = pStack -> pos_column + dir[pStack -> direction][1];
            
        if( pos_row < ROW_SIZE && pos_row >= 0 &&
            pos_column < COLUMN_SIZE && pos_column >= 0 &&
            get_maze_status( pos_row, pos_column ) == 0 )
        {
            sMazeStack *pStackNew = alloc_maze( pos_row, pos_column, 0 );
            push_maze_stack( pStackNew );
        }
        
        pStack -> direction++;
    }
            
    if( is_reached == 1 )
    {
        print_maze();
        print_maze_path();
    }
    else
    {
        puts( "No path." );
    }
    
    return 0;
}
