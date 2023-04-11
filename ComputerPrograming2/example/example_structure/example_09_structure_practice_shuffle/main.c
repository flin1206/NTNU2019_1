#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct card
{
    uint8_t suit;
    uint8_t face;
}Card;

const char *poker_str[] =
{
    "Spade",
    "Heart",
    "Diamond",
    "Club"
};

void initilize( Card * const deck )
{
    for( size_t i = 0 ; i < 52 ; i++ )
    {
        deck[i].suit = i/13;
        deck[i].face = i%13;
    }

    return;
}

void shuffle( Card * const deck )
{
    srand( time( 0 ) );
    for( size_t i = 0 ; i < 10000 ; i++ )
    {
        size_t a = rand() % 52;
        size_t b = rand() % 52;
        Card tmp = deck[a];
        deck[a] = deck[b];
        deck[b] = tmp;
    }

    return;
}

int main()
{
    Card deck[52] = {0};

    initilize( deck );
    shuffle( deck );

    for( size_t i = 0 ; i < 13 ; i++ )
    {
        printf( "%s %d\n", poker_str[ deck[i].suit ], deck[i].face );
    }

    return 0;
}
