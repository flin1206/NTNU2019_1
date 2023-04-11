#include <stdarg.h> 
#include <stdio.h> 
#include <stdint.h>
  
double average( int32_t num, ... ) 
{ 
    va_list valist; 
  
    int32_t sum = 0; 
  
    va_start( valist, num ); 
    for ( int32_t i = 0; i < num; i++ )
    {  
        sum += va_arg( valist, int32_t ); 
    }
    va_end( valist ); 
  
    return sum / ( double )num; 
} 
  
// Driver code 
int main() 
{ 
    printf( "Average of { 3, 4 } = %lf\n", average( 2, 3, 4 ) ); 
    printf( "Average of { 5, 10, 15 } = %lf\n", average( 3, 5, 10, 15 ) ); 
    return 0; 
} 