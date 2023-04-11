#include "bang.h"
#include "card_func.h"
#include "linklist.h"

void printCharacterInformation(sCharacter character)
{
    printf("character : %s\n", character.characterName);
    printf("hp : %d\n", character.hp);
    printf("skill : %s\n", character.skill);
}

void init_character(sCharacter character[])
{
    strcpy(character[0].characterName, "Bart Cassidy");
    character[0].hp = 4;
    strcpy(character[0].skill, "Each time he loses a life point, he immediately draws a card from the deck.");
    character[0].id = CHARACTER_BART;

    strcpy(character[1].characterName, "Black Jack");
    character[1].hp = 4;
    strcpy(character[1].skill, "During phase 1 of his turn, he must show the second card he draws: if it’s Heart or Diamonds (just like a “draw!”), he draws one additional card (without revealing it).");
    character[1].id = CHARACTER_BLACK;

    strcpy(character[2].characterName, "Calamity Janet");
    character[2].hp = 4;
    strcpy(character[2].skill, "She can use BANG! cards as Missed! cards and vice versa. If she plays a Missed! as a BANG! , she cannot play another BANG! card that turn (unless she has a Volcanic in play).");
    character[2].id = CHARACTER_CALAMITY;

    strcpy(character[3].characterName, "El Gringo");
    character[3].hp = 3;
    strcpy(character[3].skill, "Each time he loses a life point due to a card played by another player, he draws a random card from the hands of that player (one card for each life point). If that player has no more cards, too bad!, he does not draw. Note that Dynamite damages are not caused by any player.");
    character[3].id = CHARACTER_EL;

    strcpy(character[4].characterName, "Jesse Jones");
    character[4].hp = 4;
    strcpy(character[4].skill, "During phase 1 of his turn, he may choose to draw the first card from the deck, or randomly from the hand of any other player. Then he draws the second card from the deck.");
    character[4].id = CHARACTER_JESSE;

    strcpy(character[5].characterName, "Jourdonnais");
    character[5].hp = 4;
    strcpy(character[5].skill, "He is considered to have a Barrel in play at all times; he can “draw!” when he is the target of a BANG! , and on a Heart he is missed. If he has another real Barrel card in play, he can count both of them, giving him two chances to cancel the BANG! before playing a Missed! .");
    character[5].id = CHARACTER_JOURDONNAIS;

    strcpy(character[6].characterName, "Kit Carlson");
    character[6].hp = 4;
    strcpy(character[6].skill, "During phase 1 of his turn, he looks at the top three cards of the deck: he chooses 2 to draw, and puts the other one back on the top of the deck, face down.");
    character[6].id = CHARACTER_KIT;

    strcpy(character[7].characterName, "Lucky Duke");
    character[7].hp = 4;
    strcpy(character[7].skill, "Each time he is required to “draw!”, he flips the top two cards from the deck, and chooses the result he prefers. Discard both cards afterwards.");
    character[7].id = CHARACTER_LUCKY;

    strcpy(character[8].characterName, "Paul Regret");
    character[8].hp = 3;
    strcpy(character[8].skill, "He is considered to have a Mustang in play at all times; all other players must add 1 to the distance to him. If he has another real Mustang in play, he can count both of them, increasing all distances to him by a total of 2.");
    character[8].id = CHARACTER_PAUL;

    strcpy(character[9].characterName, "Pedro Ramirez");
    character[9].hp = 4;
    strcpy(character[9].skill, "During phase 1 of his turn, he may choose to draw the first card from the top of the discard pile or from the deck. Then, he draws the second card from the deck.");
    character[9].id = CHARACTER_PEDRO;

    strcpy(character[10].characterName, "Rose Doolan");
    character[10].hp = 4;
    strcpy(character[10].skill, "She is considered to have a Scope in play at all times; she sees the other players at a distance decreased by 1. If she has another real Scope in play, she can count both of them, reducing her distance to all other players by a total of 2.");
    character[10].id = CHARACTER_ROSE;

    strcpy(character[11].characterName, "Sid Ketchum");
    character[11].hp = 4;
    strcpy(character[11].skill, "At any time, he may discard 2 cards from his hand to regain one life point. If he is willing and able, he can use this ability more than once at a time. But remember: you cannot have more life points than your starting amount!");
    character[11].id = CHARACTER_SID;

    strcpy(character[12].characterName, "Slab the Killer");
    character[12].hp = 4;
    strcpy(character[12].skill, "Players trying to cancel his BANG! cards need to play 2 Missed! . The Barrel effect, if successfully used, only counts as one Missed! .");
    character[12].id = CHARACTER_SLAB;

    strcpy(character[13].characterName, "Suzy Lafayette");
    character[13].hp = 4;
    strcpy(character[13].skill, "As soon as she has no cards in her hand, she draws a card from the draw pile.");
    character[13].id = CHARACTER_SUZY;

    strcpy(character[14].characterName, "Vulture Sam");
    character[14].hp = 4;
    strcpy(character[14].skill, "Whenever a character is eliminated from the game, Sam takes all the cards that player had in his hand and in play, and adds them to his hand.");
    character[14].id = CHARACTER_VULTURE;

    strcpy(character[15].characterName, "Willy the Kid");
    character[15].hp = 4;
    strcpy(character[15].skill, "He can play any number of BANG! cards during his turn.");
    character[15].id = CHARACTER_WILLY;
}

void SWAP(int *pX, int *pY)
{
    int tmp = *pX;
    *pX = *pY;
    *pY = tmp;
}

void swap_card(sCard *pX, sCard *pY)
{
    sCard tmp = *pX;
    *pX = *pY;
    *pY = tmp;
}

void shuffle(int *ary, int length)
{
    srand(time(NULL));
    for (int i = length - 1; i; i--)
    {
        int idx = rand() % i;
        SWAP(&ary[idx], &ary[i]);
    }
}

void shuffleIdentity(sPlayer player[], int playerNumber)
{
    if (playerNumber == 4)
    {
        int ID[4] = {0, 2, 2, 3};
        shuffle(ID, 4);
        for (int i = 0; i < playerNumber; i++)
        {
            player[i].identity = ID[i];
        }
    }
    else if (playerNumber == 5)
    {
        int ID[5] = {0, 1, 2, 2, 3};
        shuffle(ID, 5);
        for (int i = 0; i < playerNumber; i++)
        {
            player[i].identity = ID[i];
        }
    }
    else if (playerNumber == 6)
    {
        int ID[6] = {0, 1, 2, 2, 2, 3};
        shuffle(ID, 6);
        for (int i = 0; i < playerNumber; i++)
        {
            player[i].identity = ID[i];
        }
    }
    else if (playerNumber == 7)
    {
        int ID[7] = {0, 1, 1, 2, 2, 2, 3};
        shuffle(ID, 7);
        for (int i = 0; i < playerNumber; i++)
        {
            player[i].identity = ID[i];
        }
    }
    for (int i = 0; i < playerNumber; i++)
    {
        player[i].ID = i;
        player[i].status = LIVE;
        player[i].weapon = EMPTY;
        player[i].barrel = EMPTY;
        player[i].plus_one = EMPTY;
        player[i].decrease_one = EMPTY;
        player[i].in_jail = EMPTY;
        player[i].on_bomb = EMPTY;
    }
}

void shuffleCharacter(sPlayer player[], int playerNumber, sCharacter character[], int characterNumber)
{
    int characterID[characterNumber];
    for (int i = 0; i < characterNumber; i++)
    {
        characterID[i] = i;
    }
    shuffle(characterID, characterNumber);
    for (int i = 0; i < playerNumber; i++)
    {
        player[i].character = character[characterID[i]];
        if (player[i].identity == IDENTITY_SHERIFF) // sheriff have one more blood
            player[i].hp = character[characterID[i]].hp + 1;
        else
            player[i].hp = character[characterID[i]].hp;
    }
}

void time_stop(int t)
{
    time_t result = time(NULL);

    while (1)
    {
        time_t a = time(NULL);
        if ((result + t) == a)
        {
            break;
        }
    }
}

void IDtoCardName(int ID, char *name)
{
    if (ID < 25)
        strcpy(name, "BANG!");
    else if (ID < 37)
        strcpy(name, "MANCATO!");
    else if (ID < 38)
        strcpy(name, "GATLING");
    else if (ID < 40)
        strcpy(name, "INDIANI!");
    else if (ID < 44)
        strcpy(name, "PANICO!");
    else if (ID < 48)
        strcpy(name, "CAT BALOU");
    else if (ID < 50)
        strcpy(name, "DILIGENZA");
    else if (ID < 51)
        strcpy(name, "WELLS FARGO");
    else if (ID < 53)
        strcpy(name, "EMPORIO");
    else if (ID < 59)
        strcpy(name, "BIRRA");
    else if (ID < 60)
        strcpy(name, "SALOON");
    else if (ID < 63)
        strcpy(name, "DUELLO");
    else if (ID < 65)
        strcpy(name, "BARILE");
    else if (ID < 66)
        strcpy(name, "MIRINO");
    else if (ID < 68)
        strcpy(name, "MUSTANG");
    else if (ID < 71)
        strcpy(name, "PRIGIONE");
    else if (ID < 72)
        strcpy(name, "DINAMITE");
    else if (ID < 74)
        strcpy(name, "GATLING");
    else if (ID < 77)
        strcpy(name, "SCHOFIELD");
    else if (ID < 78)
        strcpy(name, "REMINTON");
    else if (ID < 79)
        strcpy(name, "REV.CARABINE");
    else
        strcpy(name, "WINCHESTER");
}

void IDtoCardPoker(int ID, int *pokerNumber)
{
    if (ID == 0)
        *pokerNumber = 0;
    if (ID == 1)
        *pokerNumber = 13;
    if (ID == 2)
        *pokerNumber = 24;
    if (ID == 3)
        *pokerNumber = 25;
    if (ID == 4)
        *pokerNumber = 26;
    if (ID == 5)
        *pokerNumber = 27;
    if (ID == 6)
        *pokerNumber = 28;
    if (ID == 7)
        *pokerNumber = 29;
    if (ID == 8)
        *pokerNumber = 30;
    if (ID == 9)
        *pokerNumber = 31;
    if (ID == 10)
        *pokerNumber = 32;
    if (ID == 11)
        *pokerNumber = 33;
    if (ID == 12)
        *pokerNumber = 34;
    if (ID == 13)
        *pokerNumber = 35;
    if (ID == 14)
        *pokerNumber = 36;
    if (ID == 15)
        *pokerNumber = 37;
    if (ID == 16)
        *pokerNumber = 38;
    if (ID == 17)
        *pokerNumber = 40;
    if (ID == 18)
        *pokerNumber = 41;
    if (ID == 19)
        *pokerNumber = 42;
    if (ID == 20)
        *pokerNumber = 43;
    if (ID == 21)
        *pokerNumber = 44;
    if (ID == 22)
        *pokerNumber = 45;
    if (ID == 23)
        *pokerNumber = 46;
    if (ID == 24)
        *pokerNumber = 47;

    if (ID == 25)
        *pokerNumber = 1;
    if (ID == 26)
        *pokerNumber = 2;
    if (ID == 27)
        *pokerNumber = 3;
    if (ID == 28)
        *pokerNumber = 4;
    if (ID == 29)
        *pokerNumber = 5;
    if (ID == 30)
        *pokerNumber = 6;
    if (ID == 31)
        *pokerNumber = 7;
    if (ID == 32)
        *pokerNumber = 39;
    if (ID == 33)
        *pokerNumber = 48;
    if (ID == 34)
        *pokerNumber = 49;
    if (ID == 35)
        *pokerNumber = 50;
    if (ID == 36)
        *pokerNumber = 51;

    if (ID == 37)
        *pokerNumber = 22;

    if (ID == 38)
        *pokerNumber = 26;
    if (ID == 39)
        *pokerNumber = 38;

    if (ID == 40)
        *pokerNumber = 13;
    if (ID == 41)
        *pokerNumber = 23;
    if (ID == 42)
        *pokerNumber = 24;
    if (ID == 43)
        *pokerNumber = 33;

    if (ID == 44)
        *pokerNumber = 25;
    if (ID == 45)
        *pokerNumber = 34;
    if (ID == 46)
        *pokerNumber = 35;
    if (ID == 47)
        *pokerNumber = 36;

    if (ID == 48)
        *pokerNumber = 8;
    if (ID == 49)
        *pokerNumber = 8;

    if (ID == 50)
        *pokerNumber = 15;

    if (ID == 51)
        *pokerNumber = 11;
    if (ID == 52)
        *pokerNumber = 47;

    if (ID == 53)
        *pokerNumber = 18;
    if (ID == 54)
        *pokerNumber = 19;
    if (ID == 55)
        *pokerNumber = 20;
    if (ID == 56)
        *pokerNumber = 21;
    if (ID == 57)
        *pokerNumber = 22;
    if (ID == 58)
        *pokerNumber = 23;

    if (ID == 59)
        *pokerNumber = 17;

    if (ID == 60)
        *pokerNumber = 10;
    if (ID == 61)
        *pokerNumber = 37;
    if (ID == 62)
        *pokerNumber = 46;

    if (ID == 63)
        *pokerNumber = 11;
    if (ID == 64)
        *pokerNumber = 12;

    if (ID == 65)
        *pokerNumber = 0;

    if (ID == 66)
        *pokerNumber = 20;
    if (ID == 67)
        *pokerNumber = 21;

    if (ID == 68)
        *pokerNumber = 9;
    if (ID == 69)
        *pokerNumber = 10;
    if (ID == 70)
        *pokerNumber = 16;

    if (ID == 71)
        *pokerNumber = 14;

    if (ID == 72)
        *pokerNumber = 9;
    if (ID == 73)
        *pokerNumber = 48;

    if (ID == 74)
        *pokerNumber = 12;
    if (ID == 75)
        *pokerNumber = 49;
    if (ID == 76)
        *pokerNumber = 50;

    if (ID == 77)
        *pokerNumber = 51;

    if (ID == 78)
        *pokerNumber = 39;
    if (ID == 79)
        *pokerNumber = 7;
}

void showPoker(int number)
{
    if (number < 13)
        printf("spade");
    else if (number < 26)
        printf("heart");
    else if (number < 39)
        printf("diamond");
    else
        printf("club");

    if (number % 13 == 0)
        printf("A");
    else if (number % 13 == 10)
        printf("J");
    else if (number % 13 == 11)
        printf("Q");
    else if (number % 13 == 12)
        printf("K");
    else
        printf("%d", number % 13 + 1);
    printf("\n");
}

void init_card(sCard card[])
{
    for (int i = 0; i < CARD_NUMBER; i++)
    {
        card[i].ID = i;
        IDtoCardName(card[i].ID, card[i].name);
        IDtoCardPoker(card[i].ID, &card[i].pokerNumber);
    }
}

void shuffleCard(sCard card[], int cardNumber)
{
    srand(time(NULL));
    for (int i = cardNumber - 1; i; i--)
    {
        int idx = rand() % i;
        swap_card(&card[idx], &card[i]);
    }
}

void print_interface()
{
    puts("██████████████████████████████████████████████████████████████████████████████████████████");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██     ██████████████   ██████████████ ██████          ██████ ██████████████ ██████     ██");
    puts("██     ██          ██   ██          ██ ██  ██████████  ██  ██ ██          ██ ██  ██     ██");
    puts("██     ██  ██████  ██   ██  ██████  ██ ██          ██  ██  ██ ██  ██████████ ██  ██     ██");
    puts("██     ██  ██████  ████ ██  ██████  ██ ██  ██████  ██  ██  ██ ██  ██         ██  ██     ██");
    puts("██     ██            ██ ██          ██ ██  ██  ██  ██  ██  ██ ██  ██  ██████ ██  ██     ██");
    puts("██     ██  ████████  ██ ██  ██████  ██ ██  ██  ██  ██  ██  ██ ██  ██  ██  ██ ██████     ██");
    puts("██     ██  ██    ██  ██ ██  ██  ██  ██ ██  ██  ██  ██████  ██ ██  ██  ██  ██            ██");
    puts("██     ██  ████████  ██ ██  ██  ██  ██ ██  ██  ██          ██ ██  ██████  ██ ██████     ██");
    puts("██     ██            ██ ██  ██  ██  ██ ██  ██  ██████████  ██ ██          ██ ██  ██     ██");
    puts("██     ████████████████ ██████  ██████ ██████          ██████ ██████████████ ██████     ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                    1. START                                          ██");
    puts("██                                                                                      ██");
    puts("██                                    2. INTRODUCE                                      ██");
    puts("██                                                                                      ██");
    puts("██                                    3. OPERATE                                        ██");
    puts("██                                                                                      ██");
    puts("██                                    4. QUIT                                           ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██████████████████████████████████████████████████████████████████████████████████████████");
    return;
}

void print_interface_gaming(sPlayer *player, sCard *card, int *deck, int *decardDeck)
{
    printf("██████████████████████████████████████████████████████████████████████████████████████████\n");
    printf("██                                          █                                           ██\n");
    printf("██  player 0                                █  player 1                                 ██\n");

    char str[200] = "██  character :                             █  character :                              ██\n";
    memccpy(&str[20], player[0].character.characterName, sizeof(char), strlen(player[0].character.characterName));
    memccpy(&str[65], player[1].character.characterName, sizeof(char), strlen(player[1].character.characterName));
    printf("%s", str);

    strcpy(str, "██  identity  :                             █  identity  :                              ██\n");
    if (player[0].identity == IDENTITY_SHERIFF)
        memccpy(&str[20], "SHERIFF", sizeof(char), strlen("SHERIFF"));
    else if (player[0].identity == IDENTITY_DEPUTY)
        memccpy(&str[20], "DEPUTY", sizeof(char), strlen("DEPUTY"));
    else if (player[0].identity == IDENTITY_OUTLAW)
        memccpy(&str[20], "OUTLAW", sizeof(char), strlen("OUTLAW"));
    else if (player[0].identity == IDENTITY_RENEGADE)
        memccpy(&str[20], "RENEGADE", sizeof(char), strlen("RENEGADE"));

    if (player[1].identity == IDENTITY_SHERIFF)
        memccpy(&str[65], "SHERIFF", sizeof(char), strlen("SHERIFF"));
    else
    {
        if (player[1].status == DEAD)
        {
            if (player[1].identity == IDENTITY_DEPUTY)
                memccpy(&str[65], "DEPUTY", sizeof(char), strlen("DEPUTY"));
            else if (player[1].identity == IDENTITY_OUTLAW)
                memccpy(&str[65], "OUTLAW", sizeof(char), strlen("OUTLAW"));
            else if (player[1].identity == IDENTITY_RENEGADE)
                memccpy(&str[65], "RENEGADE", sizeof(char), strlen("RENEGADE"));
        }
        else
        {
            memccpy(&str[65], "SECRET", sizeof(char), strlen("SECRET"));
        }
    }
    printf("%s", str);

    strcpy(str, "██  hp        :                             █  hp        :                              ██\n");
    if (player[0].status == LIVE)
        str[20] = player[0].hp + '0';
    if (player[1].status == LIVE)
        str[65] = player[1].hp + '0';
    printf("%s", str);

    strcpy(str, "██  hand num  :                             █  hand num  :                              ██\n");
    if (player[0].status == LIVE)
        str[20] = player[0].hand.num + '0';
    if (player[1].status == LIVE)
        str[65] = player[1].hand.num + '0';
    printf("%s", str);
    strcpy(str, "██  weapon    :                             █  weapon    :                              ██\n");

    if (player[0].status == LIVE)
    {
        if (player[0].weapon == 1)
            memccpy(&str[20], "VOLCANIC", sizeof(char), strlen("VOLCANIC"));
        else if (player[0].weapon == 2)
            memccpy(&str[20], "SCHOFIELD", sizeof(char), strlen("SCHOFIELD"));
        else if (player[0].weapon == 3)
            memccpy(&str[20], "REMINTON", sizeof(char), strlen("REMINTON"));
        else if (player[0].weapon == 4)
            memccpy(&str[20], "REV.CARABINE", sizeof(char), strlen("REV.CARABINE"));
        else if (player[0].weapon == 5)
            memccpy(&str[20], "WINCHESTER", sizeof(char), strlen("WINCHESTER"));
    }

    if (player[1].status == LIVE)
    {
        if (player[1].weapon == 1)
            memccpy(&str[65], "VOLCANIC", sizeof(char), strlen("VOLCANIC"));
        else if (player[1].weapon == 2)
            memccpy(&str[65], "SCHOFIELD", sizeof(char), strlen("SCHOFIELD"));
        else if (player[1].weapon == 3)
            memccpy(&str[65], "REMINTON", sizeof(char), strlen("REMINTON"));
        else if (player[1].weapon == 4)
            memccpy(&str[65], "REV.CARABINE", sizeof(char), strlen("REV.CARABINE"));
        else if (player[1].weapon == 5)
            memccpy(&str[65], "WINCHESTER", sizeof(char), strlen("WINCHESTER"));
    }
    printf("%s", str);

    strcpy(str, "██  barrel    :                             █  barrel    :                              ██\n");
    if (player[0].barrel == HAVE && player[0].status == LIVE)
        memccpy(&str[20], "HAVE", sizeof(char), strlen("HAVE"));
    if (player[1].barrel == HAVE && player[1].status == LIVE)
        memccpy(&str[65], "HAVE", sizeof(char), strlen("HAVE"));
    printf("%s", str);

    strcpy(str, "██  MUSTANG   :                             █  MUSTANG   :                              ██\n");
    if (player[0].plus_one == HAVE && player[0].status == LIVE)
        memccpy(&str[20], "HAVE", sizeof(char), strlen("HAVE"));
    if (player[1].plus_one == HAVE && player[1].status == LIVE)
        memccpy(&str[65], "HAVE", sizeof(char), strlen("HAVE"));
    printf("%s", str);

    strcpy(str, "██  MIRINO    :                             █  MIRINO    :                              ██\n");
    if (player[0].decrease_one == HAVE && player[0].status == LIVE)
        memccpy(&str[20], "HAVE", sizeof(char), strlen("HAVE"));
    if (player[1].decrease_one == HAVE && player[1].status == LIVE)
        memccpy(&str[65], "HAVE", sizeof(char), strlen("HAVE"));
    printf("%s", str);

    printf("██                                          █                                           ██\n");
    printf("██████████████████████████████████████████████████████████████████████████████████████████\n");
    printf("██                                          █                                           ██\n");
    printf("██                                          █                                           ██\n");
    printf("██  player 3                                █  player 2                                 ██\n");

    strcpy(str, "██  character :                             █  character :                              ██\n");
    memccpy(&str[20], player[3].character.characterName, sizeof(char), strlen(player[3].character.characterName));
    memccpy(&str[65], player[2].character.characterName, sizeof(char), strlen(player[2].character.characterName));
    printf("%s", str);

    strcpy(str, "██  identity  :                             █  identity  :                              ██\n");
    if (player[3].identity == IDENTITY_SHERIFF)
        memccpy(&str[20], "SHERIFF", sizeof(char), strlen("SHERIFF"));
    else
    {
        if (player[3].status == DEAD)
        {
            if (player[3].identity == IDENTITY_DEPUTY)
                memccpy(&str[20], "DEPUTY", sizeof(char), strlen("DEPUTY"));
            else if (player[3].identity == IDENTITY_OUTLAW)
                memccpy(&str[20], "OUTLAW", sizeof(char), strlen("OUTLAW"));
            else if (player[3].identity == IDENTITY_RENEGADE)
                memccpy(&str[20], "RENEGADE", sizeof(char), strlen("RENEGADE"));
        }
        else
        {
            memccpy(&str[20], "SECRET", sizeof(char), strlen("SECRET"));
        }
    }

    if (player[2].identity == IDENTITY_SHERIFF)
        memccpy(&str[65], "SHERIFF", sizeof(char), strlen("SHERIFF"));
    else
    {
        if (player[2].status == DEAD)
        {
            if (player[2].identity == IDENTITY_DEPUTY)
                memccpy(&str[65], "DEPUTY", sizeof(char), strlen("DEPUTY"));
            else if (player[2].identity == IDENTITY_OUTLAW)
                memccpy(&str[65], "OUTLAW", sizeof(char), strlen("OUTLAW"));
            else if (player[2].identity == IDENTITY_RENEGADE)
                memccpy(&str[65], "RENEGADE", sizeof(char), strlen("RENEGADE"));
        }
        else
        {
            memccpy(&str[65], "SECRET", sizeof(char), strlen("SECRET"));
        }
    }
    printf("%s", str);

    strcpy(str, "██  hp        :                             █  hp        :                              ██\n");
    if (player[3].status == LIVE)
        str[20] = player[3].hp + '0';
    if (player[2].status == LIVE)
        str[65] = player[2].hp + '0';
    printf("%s", str);

    strcpy(str, "██  hand num  :                             █  hand num  :                              ██\n");
    if (player[3].status == LIVE)
        str[20] = player[3].hand.num + '0';
    if (player[2].status == LIVE)
        str[65] = player[2].hand.num + '0';
    printf("%s", str);
    strcpy(str, "██  weapon    :                             █  weapon    :                              ██\n");

    if (player[3].status == LIVE)
    {
        if (player[3].weapon == 1)
            memccpy(&str[20], "VOLCANIC", sizeof(char), strlen("VOLCANIC"));
        else if (player[3].weapon == 2)
            memccpy(&str[20], "SCHOFIELD", sizeof(char), strlen("SCHOFIELD"));
        else if (player[3].weapon == 3)
            memccpy(&str[20], "REMINTON", sizeof(char), strlen("REMINTON"));
        else if (player[3].weapon == 4)
            memccpy(&str[20], "REV.CARABINE", sizeof(char), strlen("REV.CARABINE"));
        else if (player[3].weapon == 5)
            memccpy(&str[20], "WINCHESTER", sizeof(char), strlen("WINCHESTER"));
    }

    if (player[2].status == LIVE)
    {
        if (player[2].weapon == 1)
            memccpy(&str[65], "VOLCANIC", sizeof(char), strlen("VOLCANIC"));
        else if (player[2].weapon == 2)
            memccpy(&str[65], "SCHOFIELD", sizeof(char), strlen("SCHOFIELD"));
        else if (player[2].weapon == 3)
            memccpy(&str[65], "REMINTON", sizeof(char), strlen("REMINTON"));
        else if (player[2].weapon == 4)
            memccpy(&str[65], "REV.CARABINE", sizeof(char), strlen("REV.CARABINE"));
        else if (player[2].weapon == 5)
            memccpy(&str[65], "WINCHESTER", sizeof(char), strlen("WINCHESTER"));
    }
    printf("%s", str);

    strcpy(str, "██  barrel    :                             █  barrel    :                              ██\n");
    if (player[3].barrel == HAVE && player[3].status == LIVE)
        memccpy(&str[20], "HAVE", sizeof(char), strlen("HAVE"));
    if (player[2].barrel == HAVE && player[2].status == LIVE)
        memccpy(&str[65], "HAVE", sizeof(char), strlen("HAVE"));
    printf("%s", str);

    strcpy(str, "██  MUSTANG   :                             █  MUSTANG   :                              ██\n");
    if (player[3].plus_one == HAVE && player[3].status == LIVE)
        memccpy(&str[20], "HAVE", sizeof(char), strlen("HAVE"));
    if (player[2].plus_one == HAVE && player[2].status == LIVE)
        memccpy(&str[65], "HAVE", sizeof(char), strlen("HAVE"));
    printf("%s", str);

    strcpy(str, "██  MIRINO    :                             █  MIRINO    :                              ██\n");
    if (player[3].decrease_one == HAVE && player[3].status == LIVE)
        memccpy(&str[20], "HAVE", sizeof(char), strlen("HAVE"));
    if (player[2].decrease_one == HAVE && player[2].status == LIVE)
        memccpy(&str[65], "HAVE", sizeof(char), strlen("HAVE"));
    printf("%s", str);

    printf("██                                          █                                           ██\n");
    printf("██████████████████████████████████████████████████████████████████████████████████████████\n");
}

void print_interface_introduce()
{
    puts("██████████████████████████████████████████████████████████████████████████████████████████");
    puts("██                                                                                      ██");
    puts("██                            ▀█▀  █▄▄ █ ▀▀█▀▀  █▀▀█  █▀▀▀█                             ██");
    puts("██                             █   █ █ █   █    █▄▄▀  █   █                             ██");
    puts("██                            ▄█▄  █ ▀▀█   █    █  █  █▄▄▄█                             ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██     The game is played by four to seven players.                                     ██");
    puts("██     Sheriff (always 1)                                                               ██");
    puts("██     Deputy (min. 0, max. 2)                                                          ██");
    puts("██     Outlaw (min. 2, max. 3)                                                          ██");
    puts("██     Renegade (min. 1, max. 2 with expansions)                                        ██");
    puts("██     Each player also receives a unique character card with special abilities         ██");
    puts("██     and a certain number of 'bullets'                                                ██");
    puts("██     The objective of the game is different for every role:                           ██");
    puts("██     The Outlaws must kill the Sheriff;                                               ██");
    puts("██     The Sheriff and his Deputies must kill the Outlaws and the Renegade(s);          ██");
    puts("██     Each Renegade's objective is to be the last player in play.                      ██");
    puts("██     The Renegade(s) must kill all the players with  sheriff being the last one dead. ██");
    puts("██                                                                                      ██");
    puts("██                                    1. START                                          ██");
    puts("██                                    2. INTRODUCE                                      ██");
    puts("██                                    3. OPERATE                                        ██");
    puts("██                                    4. QUIT                                           ██");
    puts("██                                                                                      ██");
    puts("██████████████████████████████████████████████████████████████████████████████████████████");
    return;
}

void print_interface_operation()
{
    puts("██████████████████████████████████████████████████████████████████████████████████████████");
    puts("██                                                                                      ██");
    puts("██                       █▀▀█ █▀▀█ █▀▀ █▀▀█ █▀▀█ ▀▀█▀▀  ▀  █▀▀█ █▀▀▄                    ██");
    puts("██                       █  █ █  █ █▀▀ █▄▄▀ █▄▄█   █   ▀█▀ █  █ █  █                    ██");
    puts("██                       ▀▀▀▀ █▀▀▀ ▀▀▀ ▀ ▀▀ ▀  ▀   ▀   ▀▀▀ ▀▀▀▀ ▀  ▀                    ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██     Use keyboard to input the number you want to select.                             ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██                                    1. START                                          ██");
    puts("██                                                                                      ██");
    puts("██                                    2. INTRODUCE                                      ██");
    puts("██                                                                                      ██");
    puts("██                                    3. OPERATE                                        ██");
    puts("██                                                                                      ██");
    puts("██                                    4. QUIT                                           ██");
    puts("██                                                                                      ██");
    puts("██                                                                                      ██");
    puts("██████████████████████████████████████████████████████████████████████████████████████████");
}

void print_interface_victory(int x)
{
    if (x == WIN_SHERIFF_AND_DEPUTY)
    {
        puts("██████████████████████████████████████████████████████████████████████████████████████████");
        puts("██                                                                                      ██");
        puts("██                    █▀▀█ █▀▀█ █▀▄▀█ █▀▀▀   █▀▀▀█  █   █ █▀▀▀ █▀▀█                     ██");
        puts("██                    █ ▄▄ █▄▄█ █ █ █ █▀▀▀   █   █   █ █  █▀▀▀ █▄▄▀                     ██");
        puts("██                    █▄▄█ █  █ █   █ █▄▄▄   █▄▄▄█   ▀▄▀  █▄▄▄ █  █                     ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                         Victory belongs to sheriff and deputy.                       ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██████████████████████████████████████████████████████████████████████████████████████████");
    }
    else if (x == WIN_OUTLAW)
    {
        puts("██████████████████████████████████████████████████████████████████████████████████████████");
        puts("██                                                                                      ██");
        puts("██                    █▀▀█ █▀▀█ █▀▄▀█ █▀▀▀   █▀▀▀█  █   █ █▀▀▀ █▀▀█                     ██");
        puts("██                    █ ▄▄ █▄▄█ █ █ █ █▀▀▀   █   █   █ █  █▀▀▀ █▄▄▀                     ██");
        puts("██                    █▄▄█ █  █ █   █ █▄▄▄   █▄▄▄█   ▀▄▀  █▄▄▄ █  █                     ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                            Victory belongs to outlaw.                                ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██████████████████████████████████████████████████████████████████████████████████████████");
    }
    else if (x == WIN_RENEGADE)
    {
        puts("██████████████████████████████████████████████████████████████████████████████████████████");
        puts("██                                                                                      ██");
        puts("██                    █▀▀█ █▀▀█ █▀▄▀█ █▀▀▀   █▀▀▀█  █   █ █▀▀▀ █▀▀█                     ██");
        puts("██                    █ ▄▄ █▄▄█ █ █ █ █▀▀▀   █   █   █ █  █▀▀▀ █▄▄▀                     ██");
        puts("██                    █▄▄█ █  █ █   █ █▄▄▄   █▄▄▄█   ▀▄▀  █▄▄▄ █  █                     ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                             Victory belongs to renegade.                             ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██                                                                                      ██");
        puts("██████████████████████████████████████████████████████████████████████████████████████████");
    }
}

int interface_switch(int choice)
{
    if (choice == INTERFACE_LOGIN)
    {
        print_interface();
    }
    else if (choice == INTERFACE_INTRO)
    {
        print_interface_introduce();
    }
    else if (choice == INTERFACE_OPERA)
    {
        print_interface_operation();
    }
    else if (choice == INTERFACE_QUIT)
    {
        return 0;
    }
}

void printIdentity(int ID)
{
    if (ID == 0)
        printf("identity : SHERIFF\n");
    else if (ID == 1)
        printf("identity : DEPUTY\n");
    else if (ID == 2)
        printf("identity : OUTLAW\n");
    else if (ID == 3)
        printf("identity : RENEGADE\n");
}

void printWeapon(int ID)
{
    printf("weapon   :");
    switch (ID)
    {
    case 1:
        printf("VOLCANIC  , distance = 1, ability : no limit times BANG!");
        break;
    case 2:
        printf("SCHOFIELD , distance = 2");
        break;
    case 3:
        printf("REMINTON  , distance = 3");
        break;
    case 4:
        printf("CARABINE  , distance = 4");
        break;
    case 5:
        printf("WINCHESTER, distance = 5");
        break;
    default:
        break;
    }
    printf("\n");
}

void print_player_information(sPlayer player)
{
    if (player.status == DEAD)
    {
        printf("player   : %d\n", player.ID);
        printf("character: %s\n", player.character.characterName);
        printIdentity(player.identity);
        printf("status   : dead\n");
    }
    else
    {
        if (player.ID == 0)
        {
            printf("player   : %d\n", player.ID);
            printf("character: %s\n", player.character.characterName);
            printIdentity(player.identity);
            printf("hp       : %d\n", player.hp);
        }
        else
        {
            if (player.identity == IDENTITY_SHERIFF)
            {
                printf("player   : %d\n", player.ID);
                printf("character: %s\n", player.character.characterName);
                printIdentity(player.identity);
                printf("hp       : %d\n", player.hp);
            }
            else
            {
                printf("player   : %d\n", player.ID);
                printf("character: %s\n", player.character.characterName);
                printf("Identity : SECRET\n");
                printf("hp       : %d\n", player.hp);
            }
        }
        if (player.weapon != EMPTY)
            printWeapon(player.weapon);
        if (player.barrel != EMPTY)
            printf("equipment: barrel   ,ability : can use determined when need to use MANCATO!\n");
        if (player.in_jail != EMPTY)
            printf("status   : PRIGIONE\n");
        if (player.on_bomb != EMPTY)
            printf("status   : on bomb\n");
    }
}

int32_t print_hand_card(sListhead *pList, sCard *card)
{
    sListnode *pNode = pList->head;
    while (pNode)
    {
        printf("ID:%d , card name:%s , poker number:%d\n", pNode->id, card[pNode->id].name, card[pNode->id].pokerNumber);
        pNode = pNode->pNext;
    }
    printf("\n");

    return 0;
}

void make_player_circularlist(sPlayer player[], int playerNumber)
{
    player[0].prev = &player[playerNumber - 1];
    player[0].next = &player[1];
    player[playerNumber - 1].prev = &player[playerNumber - 2];
    player[playerNumber - 1].next = &player[0];
    for (int i = 1; i < playerNumber - 1; i++)
    {
        player[i].prev = &player[i - 1];
        player[i].next = &player[i + 1];
    }
    return;
}

int count_player_bang_distance(sPlayer from, sPlayer to)
{
    sPlayer *p = &from;
    int countNext = 1, countPrev = 1;

    while (p->next->ID != to.ID)
    {
        // printf("%s\n", p->character.characterName);
        if (p->status = LIVE)
            countNext++;

        p = p->next;
    }
    p = &from;
    while (p->prev->ID != to.ID)
    {
        // printf("%s\n", p->character.characterName);
        if (p->status = LIVE)
            countPrev++;
        p = p->prev;
    }

    // 判斷武器
    if (from.weapon > 1)
    {
        countNext = countNext - from.weapon + 1;
        countPrev = countPrev - from.weapon + 1;
    }

    // 判斷 to 是否是 PAUL (+1)
    if (to.ID == CHARACTER_PAUL)
    {
        countNext++;
        countPrev++;
    }

    // 判斷 from 是否是 ROSE (-1)
    if (from.ID == CHARACTER_ROSE)
    {
        countNext--;
        countPrev--;
    }

    // 判斷+1
    if (to.plus_one != EMPTY)
    {
        countNext++;
        countPrev++;
    }

    // 判斷-1
    if (from.decrease_one != EMPTY)
    {
        countNext--;
        countPrev--;
    }

    // printf("countNext: %d, countPrev: %d\n", countNext, countPrev);
    if (countNext < countPrev)
        return countNext;
    else
        return countPrev;
}

int count_player_panic_distance(sPlayer from, sPlayer to)
{
    sPlayer *p = &from;
    int countNext = 1, countPrev = 1;

    while (p->next->ID != to.ID)
    {
        // printf("%s\n", p->character.characterName);
        countNext++;
        p = p->next;
    }
    p = &from;
    while (p->prev->ID != to.ID)
    {
        // printf("%s\n", p->character.characterName);
        countPrev++;
        p = p->prev;
    }

    // 判斷 to 是否是 PAUL (+1)
    if (to.ID == CHARACTER_PAUL)
    {
        countNext++;
        countPrev++;
    }

    // 判斷 from 是否是 ROSE (-1)
    if (from.ID == CHARACTER_ROSE)
    {
        countNext--;
        countPrev--;
    }

    // 判斷+1
    if (to.plus_one != EMPTY)
    {
        countNext++;
        countPrev++;
    }

    // 判斷-1
    if (from.decrease_one != EMPTY)
    {
        countNext--;
        countPrev--;
    }

    // printf("countNext: %d, countPrev: %d\n", countNext, countPrev);
    if (countNext < countPrev)
        return countNext;
    else
        return countPrev;
}

int draw(sPlayer *Player, int *deck, int *discardDeck)
{
    int i, j;
    for (i = 0; i < 80; i++)
    {
        if (deck[i] != EMPTY)
        {
            add_node(deck[i], &Player->hand);
            deck[i] = EMPTY;
            return 0;
        }
    }
    if (i == 80)
    {
        wash_discard_to_desk(deck, discardDeck);
        draw(Player, deck, discardDeck);
    }
    return 0;
}

void print_card_information(int id, sCard *card)
{
    printf("ID:%2d , card name:%s , poker number:%d\n", id, card[id].name, card[id].pokerNumber);
}

int draw_status(sPlayer *Player, int *deck, int *discardDeck, sCard *card) // 抽牌階段
{
    if (Player->character.id == CHARACTER_BLACK) // 必須展示抽到的第二張, 若為紅心或方塊, 則在抽一張
    {
        draw(Player, deck, discardDeck);
        draw(Player, deck, discardDeck);
        printf("second card is:\n");
        printf("ID:%d , card name:%s , poker number:%d\n", Player->hand.tail->id, card[Player->hand.tail->id].name, card[Player->hand.tail->id].pokerNumber);
        if (determined_poker_diamond(card[Player->hand.tail->id].pokerNumber) || determined_poker_heart(card[Player->hand.tail->id].pokerNumber))
        {
            printf("second one is red, so you can draw one more\n");
            draw(Player, deck, discardDeck);
        }

        return 0;
    }
    else if (Player->character.id == CHARACTER_JESSE) // 第一張可以決定要抽對手的還是牌堆的 第二張抽牌堆
    {
        int choice = 0;
        if (Player->ID == 0)
        {
            puts("Do you want to steal others hand as your first draw ? (0: No, 1: YES)");
            scanf("%d", &choice);
            while (1)
            {
                if (choice == 0)
                {
                    draw(Player, deck, discardDeck);
                    draw(Player, deck, discardDeck);
                    return 0;
                }
                else
                {
                    int stealId, noCard = 0;
                    sPlayer *whichPlayer = Player->next;
                    printf("steal player : ");
                    scanf("%d", &stealId);
                    while (whichPlayer->ID != Player->ID)
                    {
                        if (stealId == whichPlayer->ID) //找到了
                        {
                            if (whichPlayer->hand.num == 0) //沒牌
                            {
                                printf("he has no card!\n");
                                draw(Player, deck, discardDeck);
                                return 0;
                            }
                            else //技能成功
                            {
                                int whichCard = whichPlayer->hand.head->id;
                                del_node(whichPlayer->hand.head->id, &whichPlayer->hand); // 刪掉對手第一張
                                add_node(whichCard, &Player->hand);
                                draw(Player, deck, discardDeck);
                                return 0;
                            }
                        }
                        whichPlayer = whichPlayer->next;
                    }
                }
                printf("you cant choose that player\n");
            }
        }
        else
        {
            if (rand() % 2 == 1)
            {
                puts("Do you want to steal others hand as your first draw ? (0: No, 1: YES) 1");
                int stealId, noCard = 0;
                sPlayer *whichPlayer = Player->next;
                while (whichPlayer->hand.num < 1 && whichPlayer->ID != Player->ID)
                {
                    whichPlayer = whichPlayer->next;
                }
                if (whichPlayer->ID == Player->ID)
                {
                    draw(Player, deck, discardDeck);
                    draw(Player, deck, discardDeck);
                    return 0;
                }
                printf("steal player : %d\n", whichPlayer->ID);
                int whichCard = whichPlayer->hand.head->id;
                del_node(whichPlayer->hand.head->id, &whichPlayer->hand); // 刪掉對手第一張
                add_node(whichCard, &Player->hand);
                draw(Player, deck, discardDeck);
                return 0;
            }
        }
    }
    else if (Player->character.id == CHARACTER_KIT) // 看三張選兩張
    {
        int count = 0, chooseCard1 = 1, chooseCard2 = 2;
        int firstId, secondID, thirdID, i, j;
        printf("Here are first three card:\n");
        for (i = 0; i < 80 && count < 3; i++) //印出前三張
        {
            if (deck[i] != EMPTY)
            {
                if (count == 0)
                {
                    printf("first card:\n");
                    firstId = i;
                    print_card_information(deck[i], card);
                }
                else if (count == 1)
                {
                    printf("second card:\n");
                    secondID = i;
                    print_card_information(deck[i], card);
                }
                else if (count == 2)
                {
                    printf("third card:\n");
                    thirdID = i;
                    print_card_information(deck[i], card);
                }
                count++;
            }
        }
        if (i == 80) //抽到沒牌
        {
            wash_discard_to_desk(deck, discardDeck);
        }
        // 玩家
        if (Player->ID == 0)
        {
            printf("choose two card ( 1 or 2 or 3 ):"); //決定哪三張
            scanf("%d %d", &chooseCard1, &chooseCard2);
        }
        //電腦
        else
        {
            printf("choose two card ( 1 or 2 or 3 ): %d %d\n", chooseCard1, chooseCard2); //決定哪三張
        }

        if (chooseCard1 == 1 || chooseCard2 == 1)
        {
            add_node(deck[firstId], &Player->hand);
            deck[firstId] = EMPTY;
        }
        if (chooseCard1 == 2 || chooseCard2 == 2)
        {
            add_node(deck[secondID], &Player->hand);
            deck[secondID] = EMPTY;
        }
        if (chooseCard1 == 3 || chooseCard2 == 3)
        {
            add_node(deck[thirdID], &Player->hand);
            deck[thirdID] = EMPTY;
        }
    }
    else if (Player->character.id == CHARACTER_PEDRO) // 選擇棄牌堆頂的那一張作為抽兩張牌的第一張
    {
        int choice = 0;
        if (Player->ID == 0)
        {
            printf("Do you get first card of discard stack as your first draw ? (0: No, 1: YES) ");
            scanf("%d", &choice);
        }
        else
        {
            printf("Do you get first card of discard stack as your first draw ? (0: No, 1: YES) \n0\n");
        }

        if (choice)
        {
            for (int i = 0; i < 80; i++) // 取棄牌頂的第一張
            {
                if (discardDeck[i] != EMPTY)
                {
                    add_node(discardDeck[i], &Player->hand);
                    discardDeck[i] = EMPTY;
                    break;
                }
            }
            draw(Player, deck, discardDeck);
        }
        else
        {
            draw(Player, deck, discardDeck);
            draw(Player, deck, discardDeck);
        }
    }
    else // 其他角色
    {
        draw(Player, deck, discardDeck);
        draw(Player, deck, discardDeck);
    }
}

int wash_discard_to_desk(int *deck, int *discardDeck)
{
    int i, j;
    for (i = 79, j = 0; discardDeck[i] != EMPTY; i--, j++)
    {
        deck[j] = discardDeck[i];
        discardDeck[i] = EMPTY;
    }
    shuffle(deck, j);
}

void discard_status(sPlayer *Player, int *deck, int *discardDeck, sCard *card) // 棄牌階段
{
    if (Player->ID == 0) //是玩家
    {
        // printf("player %d\n", Player->ID);
        while (Player->hand.num > Player->hp)
        {
            int choice;
            print_hand_card(&Player->hand, card);
            printf("You have to discard %d card\n", Player->hand.num - Player->hp);
            printf("Your Choice ( card id ):\n");
            scanf("%d", &choice);
            if (card_exist_in_hand(Player, choice))
            {
                discard(choice, discardDeck);
                del_node(choice, &Player->hand);
            }
        }
    }
    else // 非玩家
    {
        // 超過要刪除
        if (Player->hand.num > Player->hp)
        {
            printf("Player %d have to discard %d card\n", Player->ID, Player->hand.num - Player->hp);
            while (Player->hand.num > Player->hp)
            {
                int choice = Player->hand.head->id;
                //  印出全部
                // print_hand_card(&Player->hand, card);
                printf("Player %d Choice ( card id ):\n", Player->ID);
                if (card_exist_in_hand(Player, choice))
                {
                    print_card_information(choice, card);
                    discard(choice, discardDeck);
                    del_node(choice, &Player->hand);
                }
            }
        }
    }

    return;
}

void discard(int id, int *discarddesk)
{
    for (int i = 79; i < -1; i--)
    {
        if (discarddesk[i] == EMPTY)
        {
            discarddesk[i] = id;
            break;
        }
    }
    return;
}

int card_exist_in_hand(sPlayer *player, int id)
{
    if (check_node(id, &player->hand))
        return 1;
    else
        return 0;
}

int determined_poker_heart(int num)
{
    if (num / 13 == 1)
        return 1;
    else
        return 0;
}

int determined_poker_diamond(int num)
{
    if (num / 13 == 2)
        return 1;
    else
        return 0;
}

int determined(int *deck, int *discardDeck)
{
    int i, j;
    for (i = 0; i < 80; i++)
    {
        if (deck[i] != EMPTY)
        {
            int value = deck[i];
            discard(value, discardDeck);
            deck[i] = EMPTY;
            return value;
        }
    }
    if (i == 80)
    {
        wash_discard_to_desk(deck, discardDeck);
        return determined(deck, discardDeck);
    }
}

int determined_status(sPlayer *Player, int *deck, int *discardDeck, sCard *card)
{
    // 判斷閃電
    if (Player->on_bomb == HAVE)
    {
        printf("Determined Dinamit\n");
        int result = determined(deck, discardDeck);
        printf("The poker determination of Bomb is %d\n", card[result].pokerNumber);
        if (card[result].pokerNumber >= 1 && card[result].pokerNumber <= 8)
        {
            Player->on_bomb = NONE;
            discard(card[result].pokerNumber, discardDeck);
            printf("BOMMMMMMMMMM!\n");
            Player->hp -= 3;
            if (determined_live_or_die(NULL, Player, deck, discardDeck))
            {
                //  遊戲結束了嗎
                if (detertermined_game_over(Player))
                {
                    print_interface_victory(detertermined_game_over(Player));
                    return detertermined_game_over(Player);
                }
                // 反賊摸三張
                determined_killer_get_three_card(NULL, Player, deck, discardDeck);
            }
        }
        else
        {
            Player->on_bomb = NONE;
            Player->next->on_bomb = HAVE;
            printf("Nothing happended\n");
        }
    }

    // 判斷監獄
    if (Player->in_jail == HAVE)
    {
        printf("Determined JAIL\n");
        int result = determined(deck, discardDeck);
        printf("The poker determination of Jail is %d\n", card[result].pokerNumber);
        discard(card[result].pokerNumber, discardDeck);
        if (card[result].pokerNumber / 13 != 1)
        {
            printf("YOU ARE IN JAIL!\n");
        }
        else
        {
            printf("Nothing happended\n");
            Player->in_jail = NONE;
        }
    }
}

int detertermined_game_over(sPlayer *Player)
{
    int isSheriff = 0, isDiputy = 0, isOutlaw = 0, isRegnade = 0;

    sPlayer *whoseTurn = Player->next;

    //檢查頭
    if (Player->status == LIVE)
    {
        if (Player->identity == IDENTITY_SHERIFF)
            isSheriff = 1;
        if (Player->identity == IDENTITY_RENEGADE)
            isRegnade = 1;
        if (Player->identity == IDENTITY_OUTLAW)
            isOutlaw = 1;
        if (Player->identity == IDENTITY_DEPUTY)
            isDiputy = 1;
    }

    // 逐項找
    while (whoseTurn->ID != Player->ID)
    {
        if (whoseTurn->status == LIVE)
        {
            if (whoseTurn->identity == IDENTITY_SHERIFF)
                isSheriff = 1;
            if (whoseTurn->identity == IDENTITY_RENEGADE)
                isRegnade = 1;
            if (whoseTurn->identity == IDENTITY_OUTLAW)
                isOutlaw = 1;
            if (whoseTurn->identity == IDENTITY_DEPUTY)
                isDiputy = 1;
        }
        whoseTurn = whoseTurn->next;
    }
    if (isOutlaw == 0 && isRegnade == 0)
        return WIN_SHERIFF_AND_DEPUTY;
    else if (isOutlaw == 0 && isSheriff == 0 && isDiputy == 0)
        return WIN_RENEGADE;
    else if (isSheriff == 0)
        return WIN_OUTLAW;
    else
        return 0;
}

int count_player_number(sPlayer *p)
{
    sPlayer *tmp = p->next;
    int count = 1;
    while (tmp->ID != p->ID)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}

// from:傷害來源 to:傷害者
int determined_live_or_die(sPlayer *from, sPlayer *to, int *deck, int *discard_deck)
{
    sPlayer *whoseturn = to->next;
    // 瀕死
    if (to->hp <= 0)
    {
        //  是否還可以用桃
        if (count_player_number(whoseturn) > 2)
        {
            int beerID = find_beer(&to->hand);
            //  有桃
            if (beerID != EMPTY)
            {
                //  是否自救
                printf("player %d is almost dead, will he help himself?( 1:yes ,0:no )", to->ID);
                //  玩家
                int c;
                if (to->ID == 0)
                {
                    scanf("%d", &c);
                    // 要救
                    if (c == 1)
                    {
                        printf("you offer a beer to yourself\n");
                        to->hp++;
                        discard(beerID, discard_deck);
                        del_node(beerID, &to->hand);
                        if (to->hp > 0)
                            return 1;
                    }
                }
                else
                {
                    printf("player %d offer a beer to himself\n", to->ID);
                    to->hp++;
                    discard(beerID, discard_deck);
                    del_node(beerID, &to->hand);
                    if (to->hp > 0)
                        return 1;
                }
            }
            // 外人是否救
            while (to->ID != whoseturn->ID)
            {
                beerID = find_beer(&to->hand);
                if (beerID != EMPTY)
                {
                    printf("player %d is almost dead, can player %d help?( 1:yes ,0:no )\n", to->ID, whoseturn->ID);
                    //  玩家
                    int c;
                    if (to->ID == 0)
                    {
                        scanf("%d", &c);
                        // 要救
                        if (c == 1)
                        {
                            printf("player %d offer a beer to player %d\n", whoseturn->ID, to->ID);
                            to->hp++;
                            discard(beerID, discard_deck);
                            del_node(beerID, &to->hand);
                            if (to->hp > 0)
                                return 1;
                        }
                    }
                    // 電腦
                    else
                    {
                        if (to->identity == from->identity)
                        {
                            printf("player %d offer a beer to player %d\n", whoseturn->ID, to->ID);
                            to->hp++;
                            discard(beerID, discard_deck);
                            del_node(beerID, &to->hand);
                            if (to->hp > 0)
                                return 1;
                        }
                    }
                }
                whoseturn = whoseturn->next;
            }
            // 沒人救
            if (to->hp <= 0)
            {
                printf("player %d is DEAD\n", to->ID);
                to->status = DEAD;
                return 0;
            }
        }
        // 死亡
        else
        {
            printf("player %d is DEAD\n", to->ID);
            to->status = DEAD;
            return 0;
        }
    }
}

void determined_killer_get_three_card(sPlayer *from, sPlayer *to, int *deck, int *discard_deck)
{
    // 確認死亡及死者是反賊
    if (to->status == DEAD && to->identity == IDENTITY_OUTLAW)
    {
        if (from != NULL)
        {
            printf("player %d kill a OUTLAW !\n", from->ID);
            printf("player %d draw three times\n", from->ID);
            draw(from, deck, discard_deck);
            draw(from, deck, discard_deck);
            draw(from, deck, discard_deck);
        }
    }
}
