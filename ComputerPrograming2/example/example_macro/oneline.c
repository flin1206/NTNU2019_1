#include <stdio.h> #include <string.h>

int main()
{
    char *str1 = "Hello";
    char *str2 = "World";
    
    strncmp( str1, str2, 3 );
    
    return 0;
}