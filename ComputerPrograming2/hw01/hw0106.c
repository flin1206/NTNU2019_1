#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    if ((fp = fopen(argv[1],"r"))== NULL)
    {
        perror("perror");
        printf("strerror:%s\n",strerror(errno));
    }
    return 0;
}