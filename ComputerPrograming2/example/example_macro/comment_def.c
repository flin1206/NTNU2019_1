#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t score[5] = {60, 70, 80, 85, 90};
#if 0    
    for( int32_t i = 0 ; i < 5; i++ )
    {
        score[i] += 10; /* Curve */
    }
#endif    
    for( int32_t i = 0 ; i < 5; i++ )
    {
        printf( "%02d %d\n", i, score[i] );
    }
   
    return 0;
}
