#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE	(1024)

int main()
{
    int32_t fd = 0;
    char	fileName[256] = {0};
    
    printf( "Please enter the file name: " );
    
    if( fgets( fileName, sizeof( fileName ), stdin ) == NULL )
    {
        printf( "Error!\n" );
        return 0;
    }
    
    // Since fgets will include '\n', we need to remove this character.
    if( fileName[ strlen( fileName ) - 1 ] == '\n' )
    {
        fileName[ strlen( fileName ) - 1 ] = 0;
    }
    
    fd = open( fileName, O_RDONLY );
    
    // Open file descriptor
    if( fd == -1 )
    {
        printf( "Open file error!\n" );
        return -1;
    }
    
    // Get file stat
    
    struct stat file_stat;
    
    fstat( fd, &file_stat );
    printf( "File Size: %ld bytes\n", file_stat.st_size );
 
    // Close file descriptor
    close( fd );
    
    return 0;
}