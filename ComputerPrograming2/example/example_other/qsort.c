#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define SIZE (20)

typedef struct _sStudent
{
    int32_t id;
    int32_t math;
    int32_t english;
    int32_t programming;
} sStudent;

void init( sStudent array[], int32_t size )
{
    srand( time( 0 ) );
    for( int32_t i = 0 ; i < size ; i++ )
    {
        array[i].id = i + 1;
        array[i].math = rand() % 101;
        array[i].english = rand() % 101;
        array[i].programming = rand() % 101;
    }
    return;
}

void print( sStudent array[], int32_t size )
{
    printf( "ID        Math     English Programming\n" );
    
    for( int32_t i = 0 ; i < size ; i++ )
    {
        printf( "%2d%12d%12d%12d\n", array[i].id, array[i].math, array[i].english, array[i].programming );
    }
    return;
}

int32_t prompt( void )
{
    int32_t choice = 0;
    
    printf( "Please enter your choice:\n" );
    printf( "\t1) Sort by ID\n" ); 
    printf( "\t2) Sort by Math\n" );
    printf( "\t3) Sort by English\n" );
    printf( "\t4) Sort by Programming\n" );
    printf( "\t5) Exit\n" );
    
    scanf( "%d", &choice );    
    int32_t c = 0;
    while ( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    
    return choice;
}

int compare_id( const void *pSTudent01, const void *pSTudent02 )
{
    if( ( ( sStudent * ) pSTudent01 ) -> id > ( ( sStudent * ) pSTudent02 ) -> id )
    {
        return 1;
    }
    else if ( ( ( sStudent * ) pSTudent01 ) -> id < ( ( sStudent * ) pSTudent02 ) -> id )
    {
        return -1;
    }
    return 0;
}

int compare_math( const void *pSTudent01, const void *pSTudent02 )
{
    if( ( ( sStudent * ) pSTudent01 ) -> math > ( ( sStudent * ) pSTudent02 ) -> math )
    {
        return 1;
    }
    else if ( ( ( sStudent * ) pSTudent01 ) -> math < ( ( sStudent * ) pSTudent02 ) -> math )
    {
        return -1;
    }
    return 0;
}

int compare_english( const void *pSTudent01, const void *pSTudent02 )
{
    if( ( ( sStudent * ) pSTudent01 ) -> english > ( ( sStudent * ) pSTudent02 ) -> english )
    {
        return 1;
    }
    else if ( ( ( sStudent * ) pSTudent01 ) -> english < ( ( sStudent * ) pSTudent02 ) -> english )
    {
        return -1;
    }
    return 0;
}

int compare_programming( const void *pSTudent01, const void *pSTudent02 )
{
    if( ( ( sStudent * ) pSTudent01 ) -> programming > ( ( sStudent * ) pSTudent02 ) -> programming )
    {
        return 1;
    }
    else if ( ( ( sStudent * ) pSTudent01 ) -> programming < ( ( sStudent * ) pSTudent02 ) -> programming )
    {
        return -1;
    }
    return 0;
}

int main()
{
    sStudent    student_list[SIZE] = {0};
    int32_t     running = 1;
    
    init( student_list, SIZE );
    
    while( running )
    {
        int32_t choice = prompt();
        
        switch( choice )
        {
            case 1:
                qsort( student_list, SIZE, sizeof( sStudent ), compare_id );
                print( student_list, SIZE );
                break;
            case 2:
                qsort( student_list, SIZE, sizeof( sStudent ), compare_math );
                print( student_list, SIZE );
                break;
            case 3:
                qsort( student_list, SIZE, sizeof( sStudent ), compare_english );
                print( student_list, SIZE );
                break;
            case 4:
                qsort( student_list, SIZE, sizeof( sStudent ), compare_programming );
                print( student_list, SIZE );
                break;
            case 5:
                printf( "Exit.\n" );
                running = 0;
                break;
            default:
                printf( "Wrong input.\n" );
                break;
        }
    }
    
    return 0;
}
