#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

#include "linuxlist.h"

typedef struct _sCharStack
{
    int32_t c;
    struct list_head list;
} sCharStack;

void push( struct list_head *pHead, sCharStack *pNode )
{
    list_add( &( pNode -> list ), pHead );
    return;
}

int32_t is_empty( struct list_head *pHead )
{
    return list_empty( pHead );
}

sCharStack *pop( struct list_head *pHead )
{
    if( is_empty( pHead ) )
    {
        return NULL;
    }
    
    sCharStack *pStack = list_first_entry( pHead, sCharStack, list );
    list_del( &( pStack -> list ) );
    return pStack;
}

sCharStack *get_first( struct list_head *pHead )
{
    if( is_empty( pHead ) )
    {
        return NULL;
    }
    
    sCharStack *pStack = list_first_entry( pHead, sCharStack, list );
    return pStack;
}

int32_t prec( int32_t ch )
{
    switch (ch) 
    { 
        case '+': 
        case '-': 
            return 1; 
  
        case '*': 
        case '/': 
            return 2; 
  
        case '^': 
            return 3; 
        
        default:
            return -1;
    } 
}

void infixToPostfix( char *pStr )
{
    LIST_HEAD( char_stack );
    
    for( int32_t i = 0 ; *( pStr + i ) != '\0' ; i++ )
    {
        int32_t c = *( pStr + i );
        if( c == ' ' )
        {
            continue;
        }
        
        if( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) )
        {
            printf( "%c", c );
            continue;
        }
        
        while( !is_empty( &char_stack ) && prec( get_first( &char_stack ) -> c ) >= prec( c ) )
        {
            sCharStack *pOperator = pop( &char_stack );
            printf( "%c", pOperator -> c );
            free( pOperator );
        } 
        
        sCharStack *pOperator = calloc( 1, sizeof( sCharStack ) );
        pOperator -> c = c;
        push( &char_stack, pOperator );
    } 
    
    while( !is_empty( &char_stack ) )
    {
        sCharStack *pOperator = pop( &char_stack );
        printf( "%c", pOperator -> c );
        free( pOperator );
    } 
    
    return;
}

int main()
{
    char exp[] = "a/b-c+d*e-a*c"; 
    infixToPostfix( exp ); 
    char exp2[] = "a/b-c+d*e^f-a*c"; 
    infixToPostfix( exp2 ); 
    return 0; 
}
