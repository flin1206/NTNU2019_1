#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE	*pFile = NULL;
    
    if( ( pFile = fopen( "/etc/passwd", "r" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    char	str[1024] = {0};
    char	delim = ':';
    char	account[32] = {0};
    char	password[32] = {0};
    char	uid[32] = {0};
    char	gid[32] = {0};
    char	account2[32] = {0};
    char	home[32] = {0};
    char	shell[32] = {0};
    char	*pCh = NULL;
        
    printf( "All user account information is:\n" );
    
    int32_t	i = 1;
    
    while( !feof( pFile ) )
    {
        fgets( str, 1024, pFile ); 

        //printf( "%s", str );
        
        if( ( pCh = strtok( str, &delim ) ) != NULL )
        {
            strncpy( account, pCh, 32 );
        }
        
        if( ( pCh = strtok( NULL, &delim ) ) != NULL )
        {
            strncpy( password, pCh, 32 );
        }
        
        if( ( pCh = strtok( NULL, &delim ) ) != NULL )
        {
            strncpy( uid, pCh, 32 );
        }
        
        if( ( pCh = strtok( NULL, &delim ) ) != NULL )
        {
            strncpy( gid, pCh, 32 );
        }
        
        if( ( pCh = strtok( NULL, &delim ) ) != NULL )
        {
            strncpy( account2, pCh, 32 );
        }
        
        if( ( pCh = strtok( NULL, &delim ) ) != NULL )
        {
            strncpy( home, pCh, 32 );
        }
        
        if( ( pCh = strtok( NULL, &delim ) ) != NULL )
        {
            strncpy( shell, pCh, 32 );
        }
        
        int32_t id = strtod( uid, NULL );
        
        if( id < 1000 )
        {
            continue;
        }
        
        printf( "%02d)\n", i );
        printf( "\tAccount: %s\n", account );
        printf( "\tUid: %s\n", uid );
        printf( "\tGid: %s\n", gid );
        printf( "\tHome: %s\n", home );
        printf( "\tShell: %s\n", shell );

        i++;        
    } 
    
    fclose( pFile );
    
    
    return 0;
}