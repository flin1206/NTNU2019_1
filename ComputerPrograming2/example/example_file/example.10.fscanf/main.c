#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE	*pFile = NULL;
    
    if( ( pFile = fopen( "score.txt", "r" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    uint32_t	id = 0;
    char		name[32] = {0};
    uint32_t	score = 0;
    uint32_t	total = 0;
    uint32_t	count = 0;
        
    printf( "Students score are as follows:\n" );
    
    while( !feof( pFile ) )
    {
        fscanf( pFile, "%u%31s%u", &id, name, &score );
        printf( "%02d) %s %13d\n", id, name, score );
        total += score;
        count++;
    } 
    
    fclose( pFile );
    
    printf( "Average: %lf\n", (double)total / count );
    
    
    return 0;
}