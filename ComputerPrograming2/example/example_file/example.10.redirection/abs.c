#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t input = 0;
    
    while(1)
    {
        scanf( "%d", &input );
        
        if( input == 0 )
        {
            printf( "End.\n" );
            break;
        }
        else if( input < 0 )
        {
            printf( "%d\n", input * -1 );
        }
        else
        {
            printf( "%d\n", input );
        }
    }
    
    return 0;
}
