#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void reverse( int*, int size );
void htob( int array[], int size );
void btoh( int array[], int size );

int main()
{
    char inputString [99999];
    char ans [99999];
    int array[99999];
    printf("Please enter the hex string:");
    scanf( "%s", inputString);
    
    // check validity
    for( int i = 0; i < strlen(inputString); i++ )
    {
        if( isxdigit(inputString[i]) == 0 )
        {
            printf( "ERROR : Invalid Format\n" );
            return 0;
        }
    }
    // check validity
    if(( inputString[strlen(inputString)-1] == '0' )&&( inputString[strlen(inputString)-2] == '0' )&&( strlen(inputString) % 2 == 0 ))
    {
        // make the last two digits to \0
        inputString[strlen(inputString)-1] = 0;
        inputString[strlen(inputString)-1] = 0;

        // change each char to num
        for(int i = 0 ; i < strlen( inputString ) ; i++)
        {
            // A = 65
            if( isupper( inputString[i] ) )
            {array[i] = inputString[i] - 55;}
            // a = 97
            else if( islower( inputString[i] ) )
            {array[i] = inputString[i] - 87;}
            // 0 = 48
            else
            {array[i] = inputString[i] - 48;}  
        }   
    }
    else
    {
        printf( "ERROR : Invalid Format\n" );
        return 0;
    }

    // trans hex to bin
    // reverse
    // trans bin to hex
    htob(array, strlen(inputString));
    reverse(array, strlen(inputString));
    btoh(array, strlen(inputString));

    // check if the number is able to transform to char
    for(int i = 0 ; i < strlen(inputString)/2; i++)
    {
        if(array[i]>126)
        {
            printf("ERROR : Not in ASCII\n");
            return 0;
        }
    }
    // print the answer
    for(int i = 0 ; i < strlen(inputString)/2; i++)
    {
        printf("%c",array[i]);
    }
    printf("\n");
    return 0;
}

//trans hex to bin
void htob( int array1[], int size )
{
    int count = 0;
    int array2[99999];

    // store the value of each digit in another array
    for( int i = 0, j = 0 ; i < (size/2) ; i++)
    {
        array2[i] = 16*array1[j] + array1[j+1];
        j += 2;
    }

    for( int i = 0 ; i < (size/2) ; i++)
    {
        for( int j = 7 ; j > -1 ; j--)
        {
            int x = array2[i] - pow(2,j);
            if( x >= 0 )
            {
                array1[count] = 1;
                array2[i] = array2[i] - pow(2,j);
            }
            else
            {
                array1[count] = 0;
            }
            count ++;
        }
    }

    return;
}


//trans bin to hex
void btoh( int array1[], int size )
{
    size = size / 2;
    int array2[99999];
    for(int i = 0; i < size; i++)
    {
        for(int j = 7; j > -1; j--)
        {
            array2[i] = array2[i] + pow(2,j) * array1[8*i+7-j]; 
            
        }
    }


    for(int i = 0; i < size; i++)
    {
        int tmp = array1[i];
        array1[i] = array2[i];
        array2[i] = tmp;
    }
    return;
}

//reverse per 8 bits
void reverse( int array[], int size )
{
    size = size / 2;
    for(int i = 0 ; i < size; i++)
    {
        for( int j = 7; j > 3; j-- )
        {
            int tmp = array[8*i+7-j];
            array[8*i+7-j] = array[8*i+j];
            array[8*i+j] = tmp;
        }
    }
    return;
}