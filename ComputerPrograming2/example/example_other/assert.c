#include <stdio.h>
#include <assert.h>

int main()
{
    FILE *fd;

    fd = fopen ( "file.txt", "r" );
    assert (fd);
    fclose (fd);

    return 0;
}

