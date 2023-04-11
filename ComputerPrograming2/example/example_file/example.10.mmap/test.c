#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#include <sys/mman.h>

#include "upper_lower_api.h"

int main()
{
    int32_t fd = 0;
    int32_t choice = 0;
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
    
    fd = open( fileName, O_RDWR );
    
    // Open file descriptor
    if( fd == -1 )
    {
        printf( "Open file error!\n" );
        return -1;
    }
    
    // User Choice
    
    while( 1 )
    {
        printf( "1) To Upper Case; 2) To Lower Case\n" );
        printf( "Your Choice: " );
        scanf( "%d", &choice );
        
        if( choice == 1 || choice == 2 )
        {
            break;
        }
        else
        {
            printf( "Sorry, I do not understand!\n" );
        }
    }
    
    // MMAP
    
    char    *_pFile = NULL;
    uint64_t fileSize = util_getFdSize( fd );
    
    _pFile = mmap( 0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    
    for( uint64_t i = 0 ; i < fileSize ; i++ )
    {
        if( choice == 1 )
        {
            _pFile[i] = toUpper( _pFile[i] );
        }
        else
        {
            _pFile[i] = toLower( _pFile[i] );
        }
    }
    
    munmap( _pFile, fileSize );
    close( fd );
    
    return 0;
}
