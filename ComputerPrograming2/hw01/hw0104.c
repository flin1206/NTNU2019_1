#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mystring.h"

int main(){
    const char  *str = "I have an apple.";

    int c = 'a';

    printf( "str: \"%s\"\n", str );
    printf( "mystrchr( str, c ) = %s\n", mystrchr( str, c ) );
    printf( "location is %ld\n", mystrchr( str, c ) - str );
    printf( "mystrrchr( str, c ) = %s\n", mystrrchr( str, c ) );
    printf( "location is %ld\n", mystrrchr( str, c ) - str );

    printf( "strchr( str, c ) = %s\n", strchr( str, c ) );
    printf( "location is %ld\n", strchr( str, c ) - str );
    printf( "strrchr( str, c ) = %s\n", strrchr( str, c ) );
    printf( "location is %ld\n", strrchr( str, c ) - str );

    printf( "\n" );

    const char  *str2 = "the value of pi is 3.14";
    const char  *accept = " ";
    const char  *reject = "of";
    const char  *accept2 = "abc";

    printf( "str2: \"%s\"\n", str2 );
    printf( "accept: \"%s\"\n", accept );
    printf( "reject: \"%s\"\n", reject );
    printf( "accept2: \"%s\"\n", accept2 );

    printf( "mystrspn( str2, accept ) = %ld\n", mystrspn( str2, accept ) );
    printf( "mystrcspn( str2, reject ) = %ld\n", mystrcspn( str2, reject ) );
    printf( "mystrpbrk( str2, accept2 ) = %c, which is in %ld\n", *( strpbrk( str2, accept2 ) ), strpbrk( str2, accept2 ) - str2 );

    printf( "strspn( str2, accept ) = %ld\n", strspn( str2, accept ) );
    printf( "strcspn( str2, reject ) = %ld\n", strcspn( str2, reject ) );
    printf( "strpbrk( str2, accept2 ) = %c, which is in %ld\n", *( strpbrk( str2, accept2 ) ), strpbrk( str2, accept2 ) - str2 );

    printf( "\n" );

    const char  *needle = "pi";

    printf( "needle: \"%s\"\n", needle );
    printf( "mystrstr( str2, needle ): %s\n", mystrstr( str2, needle ) );
    printf( "strstr( str2, needle ): %s\n", strstr( str2, needle ) );

    printf( "\n" );

    char    str3[] = "This is - www.gitbook.net - website";
    char    *token = mystrtok( str3," " );
    int32_t i = 0;
    //printf("%s\n",token);

    while( token != NULL )
    {
        printf( "%d:%s\n", i, token );
        token = mystrtok( NULL, " " );
        i++;
    }


    return 0;
}