#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int32_t menu( void )
{
    int32_t	choice = 0;
     
    printf( "Please enter your choice:\n" );
    printf( "0) List\n" );
    printf( "1) Average\n" );
    printf( "2) Count\n" );
    printf( "3) Sum\n" );
    printf( "4) Fail\n" );
    printf( "5) Exit\n" );
    printf( "--> " );
    
    if( scanf( "%d", &choice ) != 1 )
    {
        return -1;
    }
    
    if( choice < 0 || choice > 5 )
    {
        return -1;
    }
    
    return choice;
}

void list( FILE *pFile )
{
    uint32_t	id = 0;
    char		name[32] = {0};
    uint32_t	score = 0;
    uint32_t	total = 0;
    uint32_t	count = 0;
        
    printf( "Students score are as follows:\n" );
    
    while( !feof( pFile ) )
    {
        fscanf( pFile, "%u%31s%u", &id, name, &score );
        printf( "%02d) %13s\t%d\n", id, name, score );
        total += score;
        count++;
    }
    
    return;
}

void average( FILE *pFile )
{
    uint32_t	id = 0;
    char		name[32] = {0};
    uint32_t	score = 0;
    uint32_t	total = 0;
    uint32_t	count = 0;
        
    printf( "Students score are as follows:\n" );
    
    while( !feof( pFile ) )
    {
        fscanf( pFile, "%u%31s%u", &id, name, &score );
        total += score;
        count++;
    }
    
    printf( "Average: %3.2f\n", ( double ) total / count );
    
    return;
}

void count( FILE *pFile )
{
    uint32_t	id = 0;
    char		name[32] = {0};
    uint32_t	score = 0;
    uint32_t	total = 0;
    uint32_t	count = 0;
        
    printf( "Students score are as follows:\n" );
    
    while( !feof( pFile ) )
    {
        fscanf( pFile, "%u%31s%u", &id, name, &score );
        count++;
    }
    
    printf( "Total student: %d\n", count );
    return;
}

void sum( FILE *pFile )
{
    uint32_t	id = 0;
    char		name[32] = {0};
    uint32_t	score = 0;
    uint32_t	total = 0;
    uint32_t	count = 0;
        
    printf( "Students score are as follows:\n" );
    
    while( !feof( pFile ) )
    {
        fscanf( pFile, "%u%31s%u", &id, name, &score );
        total += score;
    }
    
    printf( "Total score: %d\n", total );
    
    return;
}

void fail( FILE *pFile )
{
    uint32_t	id = 0;
    char		name[32] = {0};
    uint32_t	score = 0;
    uint32_t	total = 0;
    uint32_t	count = 0;
        
    printf( "Students score are as follows:\n" );
    
    while( !feof( pFile ) )
    {
        fscanf( pFile, "%u%31s%u", &id, name, &score );
        
        if( score < 60 )
        {
            printf( "%02d) %13s\t%d\n", id, name, score );
        }
    }
    
    return;
}

int main()
{
    FILE	*pFile = NULL;
    
    if( ( pFile = fopen( "score.txt", "r" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    while( 1 )
    {
        int32_t choice = menu();
        
        if( choice == -1 )
        {
            continue;
        }
        else if( choice == 5 )
        {
            break;
        }
        
        switch( choice )
        {
            case 0:
                list( pFile );
                break;
            case 1:
                average( pFile );
                break;
            case 2:
                count( pFile );
                break;
            case 3:
                sum( pFile );
                break;
            case 4:
                fail( pFile );
                break;
            default:
                break;
        }
        
        rewind( pFile );
    }
    
    fclose( pFile );
    
    return 0;
}