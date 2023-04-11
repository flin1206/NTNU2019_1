#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct card
{
    uint8_t suit;
    uint8_t face;
};

const char *poker_str[] =
{
    "Spade",
    "Heart",
    "Diamond",
    "Club"
};

int main()
{
    printf( "The size of \"struct card\" is %ld\n", sizeof( struct card ) );

    struct card a_card = {0};

    printf( "The card is %s %d\n", poker_str[ a_card.suit ], a_card.face );

    struct card b_card = {1, 12};

    printf( "The card is %s %d\n", poker_str[ b_card.suit ], b_card.face );

    struct card c_card =
    {
        .suit = 2,
        .face = 5
    };

    printf( "The card is %s %d\n", poker_str[ c_card.suit ], c_card.face );

    struct card d_card = c_card;

    printf( "The card is %s %d\n", poker_str[ d_card.suit ], d_card.face );

    return 0;
}
