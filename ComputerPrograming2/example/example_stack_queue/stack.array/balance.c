#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

bool is_balanced( char * );

int main()
{
    puts( "Please enter a string:" );
    
    char input[256] = {0};
    
    fgets( input, 256, stdin );
    
    if( is_balanced( input ) == true )
    {
        puts( "Balanced." );
    }
    else
    {
        puts( "Not Balanced." );
    }
    
    return 0;
}

bool is_balanced( char *pStr )
{
    if( pStr == NULL )
    {
        puts( "NULL pointer." );
        return false;
    }
    
    sStack stack;
    init_stack( &stack );
    bool balanced = true;
    int32_t element = 0;
    int32_t popret = 0;
    
    for( size_t i = 0 ; *( pStr + i ) != '\0' && balanced == true; i++ )
    {
        switch( *( pStr + i ) )
        {
            case '(':
            case '[':
            case '{':
                push_stack( &stack, *( pStr + i ) );
                break;
            case ')':
                popret = pop_stack( &stack, &element );
                if( element != '(' || popret == -1 )
                {
                    balanced = false;
                }
                break;
            case ']':
                popret = pop_stack( &stack, &element );
                if( element != '[' || popret == -1 )
                {
                    balanced = false;
                }
                break;
            case '}':
                popret = pop_stack( &stack, &element );
                if( element != '{' || popret == -1 )
                {
                    balanced = false;
                }
                break;
            default:
                break;
        }
    }
    
    if( !is_empty_stack( &stack ) )
    {
        balanced = false;
    }
    
    return balanced;
}
