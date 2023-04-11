#include <stdio.h>

int main()
{
    printf("line: %d \n", __LINE__);
    printf("file: %s \n", __FILE__);
    printf("function: %s \n", __FUNCTION__);
    printf("function: %s \n", __func__);
    printf("time: %s \n", __TIME__);
    printf("date: %s \n", __DATE__);
    printf("STDC: %d \n", __STDC__);
    printf("STDC_VERSION: %ld \n", __STDC_VERSION__);
    printf("TIMESTAMP: %s \n", __TIMESTAMP__);
    
    return 0;
}
