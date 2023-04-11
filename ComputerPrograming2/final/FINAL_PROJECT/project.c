#include "bang.h"
#include "card_func.h"
#include "linklist.h"

int main()
{
    // init character and card
    sCharacter character[CHARACTER_NUMBER];
    sCard card[CARD_NUMBER];
    init_character(character);
    init_card(card);
    int interface_choice = INTERFACE_LOGIN;
    while (interface_choice != INTERFACE_QUIT) // login interface
    {
        interface_switch(interface_choice);
        scanf("%d", &interface_choice);
        if (interface_choice == INTERFACE_START) // game start from here
        {
            // init player information
            sPlayer player[PLAYER_NUMBER];
            shuffleIdentity(player, PLAYER_NUMBER);
            shuffleCharacter(player, PLAYER_NUMBER, character, CHARACTER_NUMBER);

            // init the deck and discard_deck
            int deck[80], discard_deck[80];
            for (int i = 0; i < 80; i++)
            {
                deck[i] = i;
                discard_deck[i] = EMPTY;
            }
            shuffle(deck, 80);

            // init player seat and determined who first
            make_player_circularlist(player, PLAYER_NUMBER);
            sPlayer *whoseFirst = NULL;
            for (int i = 0; i < PLAYER_NUMBER; i++)
                if (player[i].identity == IDENTITY_SHERIFF)
                    whoseFirst = &player[i];

            // init hand card
            for (int i = 0; i < PLAYER_NUMBER; i++)
                for (int j = 0; j < player[i].hp; j++)
                    draw(&player[i], deck, discard_deck);

            sPlayer *whoseTurn = whoseFirst;

            while (1)
            {
                printf("=======================================================\n");
                /*                 // 印出死者訊息
                                if (whoseTurn->status == DEAD)
                                {
                                    printf("player %d: \n", whoseTurn->ID);
                                    printf("character: %s\n", whoseTurn->character.characterName);
                                    printIdentity(whoseTurn->identity);
                                } */
                // 活著才會輪到
                if (whoseTurn->status == LIVE)
                {

                    determined_status(whoseTurn, deck, discard_deck, card);
                    int selectCardId;
                    draw_status(whoseTurn, deck, discard_deck, card);

                    // 在監獄則跳過
                    if (whoseTurn->in_jail != HAVE)
                    {
                        //  殺計數
                        int countBang = 0;
                        //  當是玩家時
                        if (whoseTurn->ID == 0)
                        {
                            while (1)
                            {
                                print_interface_gaming(player, card, deck, discard_deck);
                                print_player_information(*whoseTurn);
                                printf("card num : %d\n", whoseTurn->hand.num);
                                print_hand_card(&whoseTurn->hand, card);
                                printf("input card ID you want to use or -1 to end :");
                                scanf("%d", &selectCardId);
                                printf("---------------------------------------\n\n");
                                //  -1則直接結束
                                if (selectCardId == -1)
                                    break;

                                if (card_exist_in_hand(whoseTurn, selectCardId)) // 檢查是否手上有
                                {
                                    if (selectCardId <= 24) // 殺
                                    {
                                        int BangTo;
                                        printf("Bang Player:");
                                        scanf("%d", &BangTo);
                                        if (countBang < 1 || whoseTurn->weapon == 1 || whoseTurn->character.id == CHARACTER_WILLY)
                                        {
                                            if (count_player_bang_distance(*whoseTurn, player[BangTo]) <= 1)
                                            {
                                                printf("You BANG player %d !", player[BangTo].ID);
                                                bang(whoseTurn, &player[BangTo], deck, discard_deck);
                                                countBang++;
                                                discard(selectCardId, discard_deck);
                                                del_node(selectCardId, &whoseTurn->hand);

                                                //有人死嗎
                                                if (determined_live_or_die(whoseTurn, &player[BangTo], deck, discard_deck))
                                                {
                                                    //  遊戲結束了嗎
                                                    if (detertermined_game_over(whoseTurn))
                                                    {
                                                        print_interface_victory(detertermined_game_over(whoseTurn));
                                                        return detertermined_game_over(whoseTurn);
                                                    }
                                                    // 反賊摸三張
                                                    determined_killer_get_three_card(whoseTurn, &player[BangTo], deck, discard_deck);
                                                }
                                            }
                                            else
                                            {
                                                printf("Too far !\n");
                                            }
                                        }
                                        else
                                        {
                                            printf("Bang times reach limit\n");
                                        }
                                    }
                                    else if (selectCardId <= 36) // 閃
                                    {
                                        printf("Not allowed.\n");
                                    }
                                    else if (selectCardId <= 37) // 萬箭齊發
                                    {
                                        printf("You use GALTING, everyone else should play MANCATO!\n");
                                        int result = galting(whoseTurn, deck, discard_deck);
                                        if (result)
                                        {
                                            print_interface_victory(result);
                                            return result;
                                        }
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 39) // 南蠻入侵
                                    {
                                        printf("You use INDIAN, everyone else should play BANG!\n");
                                        int result = indian(whoseTurn, deck, discard_deck);
                                        if (result)
                                        {
                                            print_interface_victory(result);
                                            return result;
                                        }

                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 43) // 順手牽羊
                                    {
                                        int BangTo;
                                        printf("Who do you want to steal Player:");
                                        scanf("%d", &BangTo);
                                        if (count_player_panic_distance(*whoseTurn, player[BangTo]) <= 1)
                                        {
                                            printf("You use panico on player %d\n", player[BangTo].ID);
                                            panico(whoseTurn, &player[BangTo]);
                                            discard(selectCardId, discard_deck);
                                            del_node(selectCardId, &whoseTurn->hand);
                                        }
                                        else
                                        {
                                            printf("Too Far\n");
                                        }
                                    }
                                    else if (selectCardId <= 47) // 過河拆橋
                                    {
                                        int BangTo;
                                        printf("Who do you want to cat_balou Player:");
                                        scanf("%d", &BangTo);
                                        printf("You use panico on player %d\n", player[BangTo].ID);
                                        cat_balou(whoseTurn, &player[BangTo], discard_deck);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 49) // 抽兩張
                                    {
                                        printf("You use diligenza (draw two card)\n");
                                        diligenza(whoseTurn, deck, discard_deck);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 50) // 抽三張
                                    {
                                        printf("You use wells_fargo (draw three card)\n");
                                        wells_fargo(whoseTurn, deck, discard_deck);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 52) // 五穀豐登
                                    {
                                        printf("You use emproio\n");
                                        emproio(whoseTurn, deck, discard_deck, card);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 58) // 桃
                                    {
                                        printf("You use birra\n");
                                        birra(whoseTurn);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 59) // 桃園結義
                                    {
                                        printf("You use sallon\n");
                                        sallon(whoseTurn);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 62) // 決鬥
                                    {
                                        int Bangto;
                                        printf("Duel with player:");
                                        scanf("%d", &Bangto);
                                        printf("You use Duel on player %d\n", Bangto);
                                        duello(whoseTurn, &player[Bangto], deck, discard_deck);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                        //有人死嗎
                                        if (determined_live_or_die(whoseTurn, &player[Bangto], deck, discard_deck))
                                        {
                                            //  遊戲結束了嗎
                                            if (detertermined_game_over(whoseTurn))
                                            {
                                                print_interface_victory(detertermined_game_over(whoseTurn));
                                                return detertermined_game_over(whoseTurn);
                                            }

                                            // 反賊摸三張
                                            determined_killer_get_three_card(whoseTurn, &player[Bangto], deck, discard_deck);
                                        }
                                    }
                                    else if (selectCardId <= 64) // 八卦陣
                                    {
                                        whoseTurn->barrel = HAVE;
                                        printf("You equiped with BARILE\n");
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 65) // -1馬
                                    {
                                        whoseTurn->decrease_one = HAVE;
                                        printf("You equiped with MIRINO\n");
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 67) // +1馬
                                    {
                                        whoseTurn->plus_one = HAVE;
                                        printf("You equiped with MUSTANG\n");
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 70) // 樂不思蜀
                                    {
                                        prigione(whoseTurn);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 71) // 閃電
                                    {
                                        printf("Dynamite is comming\n");
                                        dinamite(whoseTurn);
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 73) // 連努
                                    {
                                        printf("You equiped with VOLCANIC\n");
                                        whoseTurn->weapon = 1;
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 76) // 武器距離2
                                    {
                                        printf("You equiped with SCHOFIELD\n");
                                        whoseTurn->weapon = 2;
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 77) // 武器距離3
                                    {
                                        printf("You equiped with REMINTON\n");
                                        whoseTurn->weapon = 3;
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 78) // 武器距離4
                                    {
                                        printf("You equiped with REV.CARABINE\n");
                                        whoseTurn->weapon = 4;
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                    else if (selectCardId <= 79) // 武器距離5
                                    {
                                        printf("You equiped with WINCHESTER\n");
                                        whoseTurn->weapon = 5;
                                        discard(selectCardId, discard_deck);
                                        del_node(selectCardId, &whoseTurn->hand);
                                    }
                                }
                                else
                                {
                                    printf("Not exist in your hand\n");
                                }
                            }
                        }

                        // 非玩家時
                        else
                        {
                            print_interface_gaming(player, card, deck, discard_deck);
                            print_player_information(*whoseTurn);
                            printf("card num : %d\n", whoseTurn->hand.num);
                            // print_hand_card(&whoseTurn->hand, card);
                            //  計算手牌數
                            int count = whoseTurn->hand.num;
                            sListnode *selectCardId = whoseTurn->hand.head;

                            while (selectCardId != NULL) //  把手牌逐項跑一次
                            {
                                if (selectCardId->id <= 24) // 殺
                                {
                                    int BangTo = rand() % 4;
                                    if (player[BangTo].ID != whoseTurn->ID && player[BangTo].status == LIVE && player[BangTo].identity != whoseTurn->identity)
                                        if (countBang < 1 || whoseTurn->weapon == 1 || whoseTurn->character.id == CHARACTER_WILLY)
                                        {
                                            if (count_player_bang_distance(*whoseTurn, player[BangTo]) <= 1)
                                            {
                                                printf("player %d BANG player %d!\n", whoseTurn->ID, player[BangTo].ID);
                                                bang(whoseTurn, &player[BangTo], deck, discard_deck);
                                                countBang++;
                                                discard(selectCardId->id, discard_deck);
                                                del_node(selectCardId->id, &whoseTurn->hand);
                                            }
                                        }
                                }
                                else if (selectCardId->id <= 36) // 閃
                                {
                                }
                                else if (selectCardId->id <= 37) // 萬箭齊發
                                {
                                    printf("player %d use GALTING\n", whoseTurn->ID);
                                    galting(whoseTurn, deck, discard_deck);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 39) // 南蠻入侵
                                {
                                    printf("player %d use Indian\n", whoseTurn->ID);
                                    indian(whoseTurn, deck, discard_deck);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 43) // 順手牽羊
                                {
                                    int BangTo = rand() % 4;
                                    if (player[BangTo].ID != whoseTurn->ID && player[BangTo].status == LIVE && player[BangTo].identity != whoseTurn->identity)
                                        if (count_player_panic_distance(*whoseTurn, player[BangTo]) <= 1)
                                        {
                                            // printf("Steal Player: %d", BangTo);
                                            printf("player %d stole a card from player %d\n", whoseTurn->ID, BangTo);
                                            panico(whoseTurn, &player[BangTo]);
                                            discard(selectCardId->id, discard_deck);
                                            del_node(selectCardId->id, &whoseTurn->hand);
                                        }
                                }
                                else if (selectCardId->id <= 47) // 過河拆橋
                                {
                                    int BangTo = rand() % 4;
                                    if (player[BangTo].ID != whoseTurn->ID && player[BangTo].status == LIVE && player[BangTo].identity != whoseTurn->identity && player[BangTo].hand.num >= 2)
                                    {
                                        printf("player %d cat balou a card from player %d\n", whoseTurn->ID, BangTo);
                                        cat_balou(whoseTurn, &player[BangTo], discard_deck);
                                        discard(selectCardId->id, discard_deck);
                                        del_node(selectCardId->id, &whoseTurn->hand);
                                    }
                                }
                                else if (selectCardId->id <= 49) // 抽兩張
                                {
                                    diligenza(whoseTurn, deck, discard_deck);
                                    printf("player %d use diligenza\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 50) // 抽三張
                                {
                                    wells_fargo(whoseTurn, deck, discard_deck);
                                    printf("player %d use wells_fargo\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 52) // 五穀豐登
                                {
                                    printf("player %d use emproio\n", whoseTurn->ID);
                                    emproio(whoseTurn, deck, discard_deck, card);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 58) // 桃
                                {
                                    birra(whoseTurn);
                                    printf("player %d use birra\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 59) // 桃園結義
                                {
                                    sallon(whoseTurn);
                                    printf("player %d use saloon\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 62) // 決鬥
                                {
                                    int Bangto = rand() % 4;
                                    if (player[Bangto].ID != whoseTurn->ID && player[Bangto].status == LIVE && player[Bangto].identity != whoseTurn->identity)
                                    {
                                        printf("player %d DUEL with player %d\n", whoseTurn->ID, Bangto);
                                        duello(whoseTurn, &player[Bangto], deck, discard_deck);
                                        discard(selectCardId->id, discard_deck);
                                        del_node(selectCardId->id, &whoseTurn->hand);
                                    }
                                }
                                else if (selectCardId->id <= 64) // 八卦陣
                                {
                                    whoseTurn->barrel = HAVE;
                                    printf("player %d equiped with BARILE\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 65) // -1馬
                                {
                                    whoseTurn->decrease_one = HAVE;
                                    printf("player %d equiped with MIRINO\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 67) // +1馬
                                {
                                    whoseTurn->plus_one = HAVE;
                                    printf("player %d equiped with MUSTANG\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 70) // 樂不思蜀
                                {
                                    prigione(whoseTurn);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 71) // 閃電
                                {
                                    dinamite(whoseTurn);
                                    printf("player %d use DINAMITE\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 73) // 連努
                                {
                                    whoseTurn->weapon = 1;
                                    printf("player %d equiped with VOLCANIC\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 76) // 武器距離2
                                {
                                    whoseTurn->weapon = 2;
                                    printf("player %d equiped with SCHOFIELD\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 77) // 武器距離3
                                {
                                    whoseTurn->weapon = 3;
                                    printf("player %d equiped with REMINTON\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 78) // 武器距離4
                                {
                                    whoseTurn->weapon = 4;
                                    printf("player %d equiped with REV.CARABINE\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                else if (selectCardId->id <= 79) // 武器距離5
                                {
                                    whoseTurn->weapon = 5;
                                    printf("player %d equiped with WINCHESTER\n", whoseTurn->ID);
                                    discard(selectCardId->id, discard_deck);
                                    del_node(selectCardId->id, &whoseTurn->hand);
                                }
                                selectCardId = selectCardId->pNext;
                            }
                        }
                    }

                    //  棄牌階段
                    discard_status(whoseTurn, deck, discard_deck, card);
                    time_stop(3);
                }

                //  輪到下一個
                whoseTurn = whoseTurn->next;

                printf("=======================================================\n");
            }
        }
    }
    return 0;
}