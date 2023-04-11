#include <stdio.h>
#include <stdlib.h>

int main()
{
    system( "cd /etc" );
    system( "cat passwd" );
    return 0;
}
