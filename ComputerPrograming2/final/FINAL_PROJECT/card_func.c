#include "card_func.h"
#include "character_func.h"
#define GAMER 0

// 定義裝備

#define int int32_t

// 找桃 沒找到回傳-1
int find_beer(sListhead *list)
{
    sListnode *pNode = list->head;

    while (pNode != NULL && pNode->id >= 53 && pNode->id < 58)
    {
        pNode = pNode->pNext;
    }

    if (pNode)
    {
        return pNode->id;
    }

    return -1;
}

// 找殺 沒找到回傳-1
int find_bang(sListhead *list)
{
    sListnode *pNode = list->head;

    while (pNode != NULL && pNode->id >= 0 && pNode->id < 25)
    {
        pNode = pNode->pNext;
    }

    if (pNode)
    {
        return pNode->id;
    }

    return -1;
}

// 找閃 沒找到回傳-1
int find_mancato(sListhead *list)
{
    sListnode *pNode = list->head;

    while (pNode != NULL && pNode->id >= 25 && pNode->id < 37)
    {
        pNode = pNode->pNext;
    }

    if (pNode)
    {
        return pNode->id;
    }
    return -1;
}

void bang(sPlayer *from, sPlayer *to, int *deck, int *discardDeck)
{
    int c = 0, id = 0, r;

    // 先判定八卦鏡
    if (to->barrel == 1)
    {
        if (barile(to, deck, discardDeck) == 0)
        {
            printf("Player %d use BARILE to MANCATO!\n", to->ID);
            return;
        }
    }

    // 如果是GAMER要選擇是否要閃
    if (to->ID == GAMER)
    {

        printf("Do you want to play a MANCATO! (yes:1 ,no:0) : ");
        scanf("%d", &c);

        if (c == 1)
        {

            r = calamity_janet(to);

            //找到閃
            if (r == 1)
            {
                id = find_bang(&to->hand);
            }
            else
            {
                id = find_mancato(&to->hand);
            }

            if (id == -1)
            {
                printf("Player %d hp -1\n", to->ID);
                // GAMER 扣1血
                to->hp -= 1;
                bart_cassidy(to, 1, deck, discardDeck);
                el_gringo(from, to);
            }
            else
            {
                printf("Player %d use MANCATO!\n", to->ID);
                discard(id, discardDeck);
                del_node(id, &to->hand);
                slab_the_killer(from, to, discardDeck);
            }
        }
        else
        {
            printf("Player %d hp -1\n", to->ID);
            // GAMER 扣1血
            to->hp -= 1;
            bart_cassidy(to, 1, deck, discardDeck);
            el_gringo(from, to);
        }
    }
    // 電腦
    else
    {
        //找到閃
        id = find_mancato(&to->hand);
        if (id == -1)
        {
            printf("Player %d hp -1\n", to->ID);
            // player 扣1血
            to->hp -= 1;
            bart_cassidy(to, 1, deck, discardDeck);
            el_gringo(from, to);
        }
        else
        {
            printf("Player %d use MANCATO!\n", to->ID);
            discard(id, discardDeck);
            del_node(id, &to->hand);
            slab_the_killer(from, to, discardDeck);
        }
    }
}

void mancato()
{
}

// 沒打閃就扣一血 電腦會自動打閃
int galting(sPlayer *from, int *deck, int *discardDeck)
{
    int c, id, r;
    sPlayer *whoseTurn = from->next; // 不會打到自己

    while (whoseTurn->ID != from->ID)
    {
        // 找閃

        // 若是玩家 給予決定是否出閃
        if (whoseTurn->ID == GAMER)
        {
            printf("Do you want to play a MANCATO! (yes:1 ,no:0) : ");
            scanf("%d", &c);

            if (c == 1)
            {
                r = calamity_janet(whoseTurn);

                //找到閃
                if (r == 1)
                {
                    id = find_bang(&whoseTurn->hand);
                }
                else
                {
                    id = find_mancato(&whoseTurn->hand);
                }

                // 沒閃時 必扣血
                if (id == -1)
                {
                    whoseTurn->hp--;
                    bart_cassidy(whoseTurn, 1, deck, discardDeck);
                    el_gringo(from, whoseTurn);
                    //有人死嗎
                    if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
                    {
                        //  遊戲結束了嗎
                        if (detertermined_game_over(from))
                            return detertermined_game_over(from);
                        // 反賊摸三張
                        determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
                    }
                }
                else
                {
                    discard(id, discardDeck);
                    del_node(id, &whoseTurn->hand);
                }
            }
            else
            {
                whoseTurn->hp--;
                bart_cassidy(whoseTurn, 1, deck, discardDeck);
                el_gringo(from, whoseTurn);
                //有人死嗎
                if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
                {
                    //  遊戲結束了嗎
                    if (detertermined_game_over(from))
                        return detertermined_game_over(from);
                    // 反賊摸三張
                    determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
                }
            }
        }
        else
        {
            // 電腦一律有閃出閃
            id = find_mancato(&whoseTurn->hand);

            if (id == -1)
            {
                whoseTurn->hp -= 1;
                bart_cassidy(whoseTurn, 1, deck, discardDeck);
                el_gringo(from, whoseTurn);
                //有人死嗎
                if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
                {
                    //  遊戲結束了嗎
                    if (detertermined_game_over(from))
                        return detertermined_game_over(from);
                    // 反賊摸三張
                    determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
                }
            }
            else
            {
                discard(id, discardDeck);
                del_node(id, &whoseTurn->hand);
            }
        }
        whoseTurn = whoseTurn->next;
    }
}

// 不打殺就扣血 電腦自動打殺
int indian(sPlayer *from, int *deck, int *discardDeck)
{
    int c, id, r;

    // 會打到自己
    sPlayer *whoseTurn = from;

    if (whoseTurn->ID == GAMER)
    {
        printf("Do you want to play a BANG! (yes:1 ,no:0) : ");
        scanf("%d", &c);

        if (c == 1)
        {
            r = calamity_janet(whoseTurn);

            //找到殺
            if (r == 2)
            {
                id = find_mancato(&whoseTurn->hand);
            }
            else
            {
                id = find_bang(&whoseTurn->hand);
            }

            // 沒殺時 必扣血
            if (id == -1)
            {
                if (r == 2)
                {
                    printf("No MANCATO!\n");
                }
                else
                {
                    printf("No BANG!\n");
                }

                whoseTurn->hp--;
                bart_cassidy(whoseTurn, 1, deck, discardDeck);
                //有人死嗎
                if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
                {
                    //  遊戲結束了嗎
                    if (detertermined_game_over(from))
                        return detertermined_game_over(from);
                    // 反賊摸三張
                    determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
                }
            }
            else
            {
                discard(id, discardDeck);
                del_node(id, &whoseTurn->hand);
            }
        }
        else
        {
            whoseTurn->hp--;
            bart_cassidy(whoseTurn, 1, deck, discardDeck);
            //有人死嗎
            if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
            {
                //  遊戲結束了嗎
                if (detertermined_game_over(from))
                    return detertermined_game_over(from);
                // 反賊摸三張
                determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
            }
        }
    }
    else
    {
        id = find_bang(&whoseTurn->hand);

        // 沒殺必定扣血
        if (id == EMPTY)
        {
            whoseTurn->hp -= 1;
            bart_cassidy(whoseTurn, 1, deck, discardDeck);
            el_gringo(from, whoseTurn);
            //有人死嗎
            if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
            {
                //  遊戲結束了嗎
                if (detertermined_game_over(from))
                    return detertermined_game_over(from);
                // 反賊摸三張
                determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
            }
        }
        else
        {
            discard(id, discardDeck);
            del_node(id, &whoseTurn->hand);
        }
    }
    whoseTurn = whoseTurn->next;

    //  出牌者以外的玩家
    while (whoseTurn->ID != from->ID)
    {
        if (whoseTurn->ID == GAMER)
        {
            printf("Do you want to play a BANG! (yes:1 ,no:0) : ");
            scanf("%d", &c);

            if (c == 1)
            {
                r = calamity_janet(whoseTurn);

                //找到殺
                if (r == 2)
                {
                    id = find_mancato(&whoseTurn->hand);
                }
                else
                {
                    id = find_bang(&whoseTurn->hand);
                }

                // 沒殺時 必扣血
                if (id == -1)
                {
                    if (r == 2)
                    {
                        printf("No MANCATO!\n");
                    }
                    else
                    {
                        printf("No BANG!\n");
                    }

                    whoseTurn->hp--;
                    bart_cassidy(whoseTurn, 1, deck, discardDeck);
                    el_gringo(from, whoseTurn);
                    //有人死嗎
                    if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
                    {
                        //  遊戲結束了嗎
                        if (detertermined_game_over(from))
                            return detertermined_game_over(from);
                        // 反賊摸三張
                        determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
                    }
                }
                else
                {
                    discard(id, discardDeck);
                    del_node(id, &whoseTurn->hand);
                }
            }
            else
            {
                whoseTurn->hp--;
                bart_cassidy(whoseTurn, 1, deck, discardDeck);
                el_gringo(from, whoseTurn);
                //有人死嗎
                if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
                {
                    //  遊戲結束了嗎
                    if (detertermined_game_over(from))
                        return detertermined_game_over(from);
                    // 反賊摸三張
                    determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
                }
            }
        }
        else
        {
            id = find_bang(&whoseTurn->hand);

            // 沒殺必定扣血
            if (id == EMPTY)
            {
                whoseTurn->hp -= 1;
                bart_cassidy(whoseTurn, 1, deck, discardDeck);
                el_gringo(from, whoseTurn);
                //有人死嗎
                if (determined_live_or_die(from, whoseTurn, deck, discardDeck))
                {
                    //  遊戲結束了嗎
                    if (detertermined_game_over(from))
                        return detertermined_game_over(from);
                    // 反賊摸三張
                    determined_killer_get_three_card(from, whoseTurn, deck, discardDeck);
                }
            }
            else
            {
                discard(id, discardDeck);
                del_node(id, &whoseTurn->hand);
            }
        }
        whoseTurn = whoseTurn->next;
    }
}

// 距離內可以拿走對方一件裝備或手牌
void panico(sPlayer *from, sPlayer *to)
{
    int c, id, c2;

    if (from->ID == GAMER)
    {
        printf("Choose to choose from hand or equipment (hand:1 ,equipment:2): ");
        scanf("%d", &c);

        if (c == 1)
        {
            int n, m, count = 1;
            // 拿走對方手牌
            // 可以指定哪張手牌或是隨機拿走一張
            n = to->hand.num;
            printf("Choose which card to discard (from 1 to %d): ", n);
            scanf("%d", &m);
            if (m > n)
            {
                printf("Out of range, will discard the first card\n");
                m = 1;
            }

            // 找到第m張牌的ID
            sListnode *pNode = to->hand.head;

            while (pNode != NULL && count != m)
            {
                pNode = pNode->pNext;
                count++;
            }

            if (pNode)
            {
                id = pNode->id;
            }

            // 刪除
            del_node(id, &to->hand);
            add_node(id, &from->hand);
        }
        else if (c == 2)
        {
            // 拿走對方裝備
            // 選擇哪個裝備 附上對方是否有裝備
            printf("Choose which equipment you want to discard ");
            printf("(MUSTANG:1(%d) MIRINO:2(%d) WEAPON:3(%d) BARILE:4(%d) PRIGIONE:5(%d) DINAMITE:6(%d) (if 0 -> not equipped)) :", to->plus_one, to->decrease_one, to->weapon, to->barrel, to->in_jail, to->on_bomb);
            scanf("%d", &c2);

            if (c2 == 1 && to->plus_one == 1)
            {
                from->plus_one = 1;
                to->plus_one = 0;
            }
            else if (c2 == 2 && to->decrease_one == 1)
            {
                from->decrease_one = 1;
                to->decrease_one = 0;
            }
            else if (c2 == 3 && to->weapon != 0)
            {
                from->weapon = to->weapon;
                to->weapon = 0;
            }
            else if (c2 == 4 && to->barrel == 1)
            {
                from->barrel = 1;
                to->barrel = 0;
            }
            else if (c2 == 5 && to->in_jail == 1)
            {
                from->in_jail = 1;
                to->in_jail = 0;
            }
            else if (c == 6 && to->on_bomb == 1)
            {
                from->on_bomb = 1;
                to->on_bomb = 0;
            }
            else
            {
                // 選到對方沒有的裝備就直接拿對方第一張手牌 沒有再重選了
                printf("The player doesn't have the equipment! You will get his first card in his hand\n");
                sListnode *pNode = to->hand.head;

                id = pNode->id;

                del_node(id, &to->hand);
                add_node(id, &from->hand);
            }
        }
    }
    else
    {
        sListnode *pNode = to->hand.head;

        id = pNode->id;

        // 刪除
        del_node(id, &to->hand);
        add_node(id, &from->hand);
    }
}

// 棄掉任一手牌或裝備
void cat_balou(sPlayer *from, sPlayer *to, int *discardDeck)
{
    int c, id, c2;

    if (from->ID == GAMER)
    {
        printf("Choose to choose from hand or equipment (hand:1 ,equipment:2): ");
        scanf("%d", &c);

        if (c == 1)
        {
            int n, m, count = 1;
            // 棄掉對方手牌
            // 可以指定哪張手牌或是隨機棄掉一張
            n = to->hand.num;
            printf("Choose which card to discard (from 1 to %d): ", n);
            scanf("%d", &m);
            if (m > n)
            {
                printf("Out of range, will discard the first card\n");
                m = 1;
            }

            // 找到第m張牌的ID
            sListnode *pNode = to->hand.head;

            while (pNode != NULL && count != m)
            {
                pNode = pNode->pNext;
                count++;
            }

            if (pNode)
            {
                id = pNode->id;
            }

            // 刪除
            discard(id, discardDeck);
            del_node(id, &to->hand);
        }
        else if (c == 2)
        {
            // 棄掉對方裝備
            // 選擇哪個裝備 附上對方是否有裝備
            printf("Choose which equipment you want to discard ");
            printf("(MUSTANG:1(%d) MIRINO:2(%d) WEAPON:3(%d) BARILE:4(%d) PRIGIONE:5(%d) DINAMITE:6(%d) (if 0 -> not equipped)) :", to->plus_one, to->decrease_one, to->weapon, to->barrel, to->in_jail, to->on_bomb);
            scanf("%d", &c2);

            if (c2 == 1)
            {
                to->plus_one = 0;
            }
            else if (c2 == 2)
            {
                to->decrease_one = 0;
            }
            else if (c2 == 3)
            {
                to->weapon = 0;
            }
            else if (c2 == 4)
            {
                to->barrel = 0;
            }
            else if (c2 == 5)
            {
                to->in_jail = 0;
            }
            else if (c == 6)
            {
                to->on_bomb = 0;
            }
        }
    }
    else
    {
        sListnode *pNode = to->hand.head;

        id = pNode->id;

        // 刪除
        discard(id, discardDeck);
        del_node(id, &to->hand);
    }
}

// 抽2張牌
void diligenza(sPlayer *player, int *deck, int *discardDeck)
{
    draw(player, deck, discardDeck);
    draw(player, deck, discardDeck);
}

// 抽3張牌
void wells_fargo(sPlayer *player, int *deck, int *discardDeck)
{
    draw(player, deck, discardDeck);
    draw(player, deck, discardDeck);
    draw(player, deck, discardDeck);
}

// 先抽n張牌 依序選擇要什麼牌
void emproio(sPlayer *to, int *deck, int *discardDeck, sCard *cardDic)
{
    int c = 0, id, check = 0, n = 0, i = 0;
    sPlayer *recent = to;

    // 先看有多少活人
    for (int i = 0; i < 4; i++)
    {
        if (recent->status == 1)
        {
            n++;
        }
        recent = recent->next;
    }

    int card[n];
    // 抽n張牌 放在card
    for (i = 0; i < 80; i++)
    {
        if (c == n)
        {
            break;
        }

        if (deck[i] != EMPTY)
        {
            card[c] = deck[i];
            discard(deck[i], discardDeck);
            deck[i] = EMPTY;
            c++;
        }
    }

    // 輪流選牌
    for (int i = 0; i < n; i++)
    {
        if (recent->ID == GAMER)
        {
            printf("which card do you want to get?\n");
            for (int j = 0; j < n; j++)
            {
                if (card[j] != -1)
                {
                    printf("(%d) %s  ", card[j], cardDic[card[j]].name);
                }
            }
            printf("Your choice (enter the card id): ");
            scanf("%d", &id);

            for (int j = 0; j < n; j++)
            {
                if (id == card[j])
                {
                    check = 1;
                    break;
                }
            }

            if (check == 0)
            {
                printf("Not in the range! You will get the first card\n");
                for (int j = 0; j < n; j++)
                {
                    if (card[j] != -1)
                    {
                        id = card[j];
                        card[j] = -1;
                        break;
                    }
                }
            }

            add_node(id, &recent->hand);
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                if (card[j] != -1)
                {
                    id = card[j];
                    card[j] = -1;
                    break;
                }
            }
            add_node(id, &recent->hand);
        }

        recent = recent->next;
    }
}

// 血量加1
void birra(sPlayer *to)
{
    if (to->identity == IDENTITY_SHERIFF)
    {
        if (to->hp <= to->character.hp)
            to->hp++;
    }
    else if (to->hp < to->character.hp)
        to->hp++;
}

// 全體血量加1
void sallon(sPlayer *player)
{
    sPlayer *whoseTurn = player;

    // 先判斷玩家本身
    if (whoseTurn->identity == IDENTITY_SHERIFF)
    {
        if (whoseTurn->hp <= player->character.hp)
        {
            printf("player %d hp +1\n",player->ID);
            whoseTurn->hp++;
        }
            
    }
    else
    {
        if (whoseTurn->hp < player->character.hp)
        {
            printf("player %d hp +1\n",player->ID);
            whoseTurn->hp++;
        }
    }

    // 逐項判斷
    whoseTurn = player->next;
    while (whoseTurn->ID != player->ID)
    {
        // 小於才可加血
        if (whoseTurn->hp < whoseTurn->character.hp)
        {
             printf("player %d hp +1\n",whoseTurn->ID);
            whoseTurn->hp++;
        }
        whoseTurn = whoseTurn->next;
    }
}

// 決鬥
void duello(sPlayer *from, sPlayer *to, int *deck, int *discardDeck)
{
    int check = 1, c, id, r;
    while (check)
    {
        // 由to先丟BANG
        printf("Player %d's turn\n", to->ID);

        // GAMER
        if (to->ID == GAMER)
        {
            printf("Choose if you want to play a BANG (yes:1 ,no:2) : ");
            scanf("%d", &c);

            if (c == 1)
            {
                r = calamity_janet(to);

                //找到殺
                if (r == 2)
                {
                    id = find_mancato(&to->hand);
                }
                else
                {
                    id = find_bang(&to->hand);
                }

                if (id == -1)
                {
                    printf("No BANG!\n");
                    to->hp -= 1;
                    bart_cassidy(to, 1, deck, discardDeck);
                    el_gringo(from, to);
                    break;
                }
                else
                {
                    discard(id, discardDeck);
                    del_node(id, &to->hand);
                }
            }
            else if (c == 2)
            {
                to->hp -= 1;
                bart_cassidy(to, 1, deck, discardDeck);
                el_gringo(from, to);
                break;
            }
        }
        else
        {
            // npc
            id = find_bang(&to->hand);

            if (id == -1)
            {
                printf("No BANG!\n");
                to->hp -= 1;
                printf("player %d hp -1\n",to->ID);
                bart_cassidy(to, 1, deck, discardDeck);
                el_gringo(from, to);
                break;
            }
            else
            {
                discard(id, discardDeck);
                del_node(id, &to->hand);
            }
        }

        // 換from丟BANG
        printf("Player %d's turn\n", from->ID);
        // GAMER
        if (from->ID == GAMER)
        {
            printf("Choose if you want to play a BANG (yes:1 ,no:2) : ");
            scanf("%d", &c);

            if (c == 1)
            {
                r = calamity_janet(from);

                //找到殺
                if (r == 2)
                {
                    id = find_mancato(&from->hand);
                }
                else
                {
                    id = find_bang(&from->hand);
                }

                if (id == -1)
                {
                    printf("No BANG!\n");
                    from->hp -= 1;
                    bart_cassidy(from, 1, deck, discardDeck);
                    break;
                }
                else
                {
                    discard(id, discardDeck);
                    del_node(id, &from->hand);
                }
            }
            else if (c == 2)
            {
                from->hp -= 1;
                bart_cassidy(from, 1, deck, discardDeck);
                break;
            }
        }
        else
        {
            // npc
            id = find_bang(&from->hand);

            if (id == -1)
            {
                printf("No BANG!\n");
                from->hp -= 1;
                printf("player %d hp -1\n", from->ID);
                bart_cassidy(from, 1, deck, discardDeck);
                break;
            }
            else
            {
                discard(id, discardDeck);
                del_node(id, &from->hand);
            }
        }
    }
}

// 被殺可以判定 回傳1就沒閃 0就有閃
int barile(sPlayer *to, int *deck, int *discardDeck)
{
    int n;

    // 判定結果放到n

    if (to->character.id == CHARACTER_LUCKY)
    {
        n = lucky_duke(to, deck, discardDeck);
    }
    else
    {
        n = determined(deck, discardDeck);
    }

    // 檢查判定結果
    if (n >= 13 && n <= 25)
    {
        return 0;
    }

    return 1;
}

// 判定 跳過回合 回傳1就跳過 0就繼續
void prigione(sPlayer *from)
{
    int n;
    sPlayer *recent = from->next;

    if (from->ID == GAMER)
    {
        printf("Choose the player you want to send to jail (from 1 to 3) :");
        scanf("%d", &n);

        while (recent && recent->ID != n)
        {
            recent = recent->next;
        }

        if (recent->status == DEAD)
        {
            printf("Player %d is dead!\n", recent->ID);
            return;
        }

        recent->in_jail = 1;
    }
    // 電腦直接判定下家
    else
    {
        while (recent->status == DEAD)
        {
            recent = recent->next;
        }
        if (recent->ID != from->ID)
        {
            printf("player %d use PRIGIONE to player %d\n", from->ID, recent->ID);
            recent->in_jail = 1;
        }
    }
}

// 閃電
void dinamite(sPlayer *to)
{
    // 設定閃電

    to->on_bomb = 1;
}
