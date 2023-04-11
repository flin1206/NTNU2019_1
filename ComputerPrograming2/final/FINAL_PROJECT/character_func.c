#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bang.h"
#include "card_func.h"

#define GAMER 0

void player_dead(sPlayer *player, int *discardDeck)
{
    sPlayer *p = player->next;
    sListnode *node = player->hand.head;
    int id, c = 0;

    while (p->ID != player->ID)
    {
        if (p->character.id == CHARACTER_VULTURE)
        {
            c = 1;
            break;
        }
    }

    while (node)
    {
        id = node->id;

        if (c == 1)
        {
            add_node(id, &p->hand);
            del_node(id, &player->hand);
        }
        else
        {
            discard(id, discardDeck);
            del_node(id, &player->hand);
        }
    }
}

// 判斷是否有人死 回傳死的人的id 沒死就回傳0
int detect_death(sPlayer *to)
{
    int per;
    sPlayer *p = to->next;

    per = to->ID;

    if (to->hp < 0)
    {
        return per;
    }

    while (p->ID != per)
    {
        if (p->hp < 0)
        {
            return p->ID;
        }

        p = p->next;
    }

    return 0;
}

// 問各個玩家要不要用桃 回傳0是沒人幫忙回 回傳1是有回到
int if_beer(sPlayer *to, int *discardDeck)
{
    int per, id, c;
    sPlayer *p = to->next;

    per = to->ID;

    // 先判斷本人要不要用
    if (to->ID = 0)
    {
        printf("Do you want to use a BIRRA? (yes:1 , no:2) : ");
        scanf("%d", &c);
        if (c == 1)
        {
            id = find_beer(&to->hand);
            if (id == -1)
            {
                printf("You don't have a BIRRA!\n");
            }
            else
            {
                printf("You gain one hp\n");
                discard(id, discardDeck);
                del_node(id, &to->hand);
                to->hp += 1;
                return 1;
            }
        }
    }
    else
    {
        id = find_beer(&to->hand);
        if (id == -1)
        {
        }
        else
        {
            discard(id, discardDeck);
            del_node(id, &to->hand);
            to->hp += 1;
            return 1;
        }
    }

    // 問其他人要不要用
    while (p->ID != per)
    {
        if (p->ID = 0)
        {
            printf("Do you want to use a BIRRA for player %d? (yes:1 , no:2) : ", per);
            scanf("%d", &c);
            if (c == 1)
            {
                id = find_beer(&p->hand);
                if (id == -1)
                {
                    printf("You don't have a BIRRA!\n");
                }
                else
                {
                    printf("You gain one hp\n");
                    discard(id, discardDeck);
                    del_node(id, &p->hand);
                    to->hp += 1;
                    return 1;
                }
            }
        }
        else
        {
            id = find_beer(&p->hand);
            if (id == -1)
            {
            }
            else
            {
                discard(id, discardDeck);
                del_node(id, &p->hand);
                to->hp += 1;
                return 1;
            }
        }
        p = p->next;
    }

    return 0;
}

// 傳入扣多少血
void bart_cassidy(sPlayer *to, int n, int *deck, int *discardDeck)
{
    if (to->character.id != CHARACTER_BART)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        draw(to, deck, discardDeck);
    }
}

// 先選擇要用殺還是閃
int calamity_janet(sPlayer *to)
{
    if (to->character.id != CHARACTER_CALAMITY)
    {
        return 0;
    }

    int c;
    printf("Choose to play a BANG! or a MANCATO! (BANG!:1 , MANCATO!:2) : ");
    scanf("%d", &c);
    return c;
}

// 拿一張 如果超過一血就多跑幾次 不然在這邊塞迴圈也行
void el_gringo(sPlayer *from, sPlayer *to)
{
    if (to->character.id != CHARACTER_EL)
    {
        return;
    }

    int n, m, count = 1, id;
    // 拿走對方手牌
    // 可以指定哪張手牌或是隨機拿走一張
    n = to->hand.num;
    printf("Choose which card to take (from 1 to %d): ", n);
    scanf("%d", &m);
    if (m > n)
    {
        printf("Out of range, will take the first card\n");
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

// 跟barrel一樣
void jourdonnais(sPlayer *to)
{
    if (to->character.id != CHARACTER_EL)
    {
        return;
    }
}

// 判定可以抽2張
int lucky_duke(sPlayer *to, int *deck, int *discardDeck)
{
    if (to->character.id != CHARACTER_LUCKY)
    {
        return -1;
    }

    int n1, n2, c;

    // 判定結果1存n1

    n1 = determined(deck, discardDeck);

    // 判定結果2存n2

    n2 = determined(deck, discardDeck);

    printf("choose which card to use (%d:1 , %d:2) : ", n1, n2);
    scanf("%d", &c);

    return c;
}

// 兩閃擋一殺
void slab_the_killer(sPlayer *from, sPlayer *to, int *discardDeck)
{
    if (to->character.id != CHARACTER_SLAB)
    {
        return;
    }

    int c, id;
    // 如果是GAMER要選擇是否要閃
    if (to->ID == GAMER)
    {
        printf("Do you want to play a MANCATO! (yes:1 ,no:0) : ");
        scanf("%d", &c);

        if (c == 1)
        {
            //找到閃
            id = find_mancato(&to->hand);

            if (id == -1)
            {
                printf("No MANCATO!\n");
                // GAMER 扣1血
                to->hp -= 1;
            }
            else
            {
                discard(id, discardDeck);
                del_node(id, &to->hand);
            }
        }
        else
        {
            // GAMER 扣1血
            to->hp -= 1;
        }
    }
    // 電腦
    else
    {
        //找到閃
        id = find_mancato(&to->hand);
        if (id == -1)
        {
            // player 扣1血
            to->hp -= 1;
        }
        else
        {
            discard(id, discardDeck);
            del_node(id, &to->hand);
        }
    }
}

// 沒牌就抽一張
void suzy_lafayette(sPlayer *to, int *deck, int *discardDeck)
{
    if (to->character.id != CHARACTER_SUZY)
    {
        return;
    }

    draw(to, deck, discardDeck);
}

void vulture_sam(sPlayer *from, sPlayer *to)
{
    sListhead *f = &from->hand;
    sListhead *t = &to->hand;
    sListnode *node = f->head;
    int id;

    while (f->num != 0)
    {
        id = node->id;
        del_node(id, f);
        add_node(id, t);
    }
}

void sid_ketchum(sPlayer *to, int *discardDeck, sCard *card)
{
    int n1, n2;

    sListhead *t = &to->hand;
    sListnode *node = t->head;

    if (t->num < 2)
    {
        printf("not enough card\n");
        return;
    }

    printf("your card: ");
    while (node)
    {
        printf("(%d) %s  ", node->id, card[node->id].name);
    }
    printf("Enter the ID of the first card you want to discard: ");
    scanf("%d", &n1);
    printf("Enter the ID of the second card you want to discard: ");
    scanf("%d", &n2);
    if (del_node(n1, t) == -1)
    {
        printf("You don't have that card, failed!\n");
        return;
    }
    if (del_node(n2, t) == -1)
    {
        printf("You don't have that card, failed!\n");
        add_node(n1, t);
        return;
    }

    to->hp += 1;
    discard(n1, discardDeck);
    discard(n2, discardDeck);
}