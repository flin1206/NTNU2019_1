#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>
 
int main( )
{
	char        buffer[512];
	FILE        *pPing = NULL;
	uint32_t    counter = 0;
 
	pPing = popen( "ping -c 4 www.google.com", "r" );
	if( pPing == NULL )
	{
		printf("error end\n");
		exit( 1 );
	}
 
	while( fgets( buffer, 512, pPing ) )
	{
	    counter++;
	    printf( "--- %d ---\n", counter );
		printf( "%s", buffer );
	}
 
	pclose( pPing );
	
	return 0;
}

