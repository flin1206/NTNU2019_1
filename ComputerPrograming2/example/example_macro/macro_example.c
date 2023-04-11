#include <stdio.h>
#include <stdint.h>

#define AND &&
#define OR ||
#define GOOD_THRESHOLD 80
#define FAIL_THRESHOLD 60
#define MID_THRESHOLD (GOOD_THRESHOLD + FAIL_THRESHOLD)/2
#define GREAT printf( "GREAT!!\n" ) 
#define ALERT printf( "Alert!!\n" ) 

int main()
{
    int32_t math = 90;
    int32_t english = 90;
    
    printf( "MID_THRESHOLD = %d\n", MID_THRESHOLD );
    
    if( math >= GOOD_THRESHOLD AND english >= GOOD_THRESHOLD )
    {
        GREAT;
    }
    else if( math < FAIL_THRESHOLD OR english < FAIL_THRESHOLD )
    {
        ALERT;
    }
    
    return 0;
}
