#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define ROW_SIZE    (12)
#define COLUMN_SIZE (15)

int32_t dir[8][2] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };

void print_maze( int32_t maze[ROW_SIZE][COLUMN_SIZE] )
{
    for( int32_t i = 0 ; i < ROW_SIZE; i++ )
    {
        for( int32_t j = 0 ; j < COLUMN_SIZE; j++ )
        {
            if ( maze[i][j] == -1 )
            {
                printf( " *" );
            }
            else
            {
                printf( "%2d", maze[i][j] );
            }
        }
        printf( "\n" );
    }
}

int32_t path( int32_t maze[ROW_SIZE][COLUMN_SIZE], int32_t row, int32_t column )
{
    maze[row][column] = 2;
    
    if( row == ( ROW_SIZE - 1 ) && column == ( COLUMN_SIZE - 1 ) )
    {
        return 0;
    }
    
    for( int32_t i = 0 ; i < 8 ; i++ )
    {
        if( row + dir[i][0] < 0 || row + dir[i][0] >= ROW_SIZE || 
            column + dir[i][1] < 0 || column + dir[i][1] >= COLUMN_SIZE )
        {
            continue;
        }
        
        if( maze[ row + dir[i][0] ][ column + dir[i][1] ] != 0 )
        {
            continue;
        }
        
        if( path( maze, row + dir[i][0], column + dir[i][1] ) == 0 )
        {
            return 0;
        }
    }
    
    maze[row][column] = -1;
    return -1;
}

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
                                            
    
    path( maze, 0, 0 );
    print_maze( maze );
    return 0;
}
