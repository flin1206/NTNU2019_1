#include <stdio.h>
#include <stdint.h>

enum career
{
    SABER,
    LANCER,
    ARCHER,
    RIDER,
    CASTER,
    ASSASSIN,
    BERSAKER,
    RULER,
    CAREER_MAX = 31
};

typedef struct player
{
    char        name[64];
    enum career role;
    uint32_t    role2;
} Player;

int main()
{
    for( enum career i = SABER; i <= CAREER_MAX ; i++ )
    {
        printf( "%d\n", i );
    }

    Player alice = {0};
    snprintf( alice.name, 64, "Alice" );
    alice.role = BERSAKER;

    alice.role2 = alice.role2 | ( 1 << CASTER );
    alice.role2 = alice.role2 | ( 1 << ASSASSIN );

    printf( "Name: %s\n", alice.name );
    printf( "Role: %d\n", alice.role );
    printf( "Role2: %08X\n", alice.role2 );

    return 0;
}
