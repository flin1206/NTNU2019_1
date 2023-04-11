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
    int32_t src_fd = 0;
    int32_t dst_fd = 0;
    
    src_fd = open( "maldives.bmp", O_RDONLY );
    
    // Open SRC file descriptor
    if( src_fd == -1 )
    {
        printf( "Open source file error!\n" );
        return -1;
    }
    
    // Open DST file descriptor
    dst_fd = open( "maldives_copy.bmp", O_WRONLY | O_CREAT, 0644 );
    
    if( dst_fd == -1 )
    {
        printf( "Open destination file error!\n" );
        return -1;
    }
    
    
    // Copy
    
    uint8_t	buffer[BUF_SIZE] = {0};
    
    ssize_t ret_in = 0, ret_out = 0;
    

    while( ( ret_in = read ( src_fd, buffer, BUF_SIZE ) ) > 0 )
    {
        ret_out = write ( dst_fd, buffer, ret_in );
        
        if( ret_out != ret_in )
        {
            // Write error
            printf( "Write error!\n");
            return -1;
        }
    }
 
    // Close file descriptors
    close( src_fd );
    close( dst_fd );    
    
    return 0;
}