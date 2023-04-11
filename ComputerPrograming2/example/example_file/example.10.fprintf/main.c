#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
    FILE	*pFile = NULL;
    char	fileName[32] = {0};
    
    printf( "Please enter the file name: " );	
    
    if( fgets( fileName, sizeof( fileName ), stdin ) == NULL )
    {
        perror("Error");
        return 0;
    }
    
    // Since fgets will include '\n', we need to remove this character.
    
    if( fileName[ strlen( fileName ) - 1 ] == '\n' )
    {
        fileName[ strlen( fileName ) - 1 ] = 0;
    }
    
    if( ( pFile = fopen( fileName, "w" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        perror( "Error" );
        return 0;
    }
    
    char	account[32] = {0};
    char	password[32] = {0};
    int32_t	i = 1;
    
    while( !feof( stdin ) )
    {
        printf( "Please enter your account and password.\n" );
        printf( "The length of account and password cannot be over 31.\n" );
        
        printf( "Account: " );
        fgets( account, 32, stdin );
        
        if( account[ strlen( account ) - 1 ] == '\n' )
        {
            account[ strlen( account ) - 1 ] = 0;
        }
                
        printf( "Password: " );
        fgets( password, 32, stdin );
        
        if( password[ strlen( password ) - 1 ] == '\n' )
        {
            password[ strlen( password ) - 1 ] = 0;
        }
        
        fprintf( pFile, "%02d %s/%s\n", i, account, password );
        i++;        
    } 
    
    fclose( pFile );
    
    
    return 0;
}