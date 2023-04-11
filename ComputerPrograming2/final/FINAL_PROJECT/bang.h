#pragma once

#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include "linklist.h"

#define CHARACTER_NUMBER 16
#define PLAYER_NUMBER 4
#define CARD_NUMBER 80

#define INTERFACE_LOGIN 0
#define INTERFACE_START 1
#define INTERFACE_INTRO 2
#define INTERFACE_OPERA 3
#define INTERFACE_QUIT 4

#define IDENTITY_SHERIFF 0
#define IDENTITY_DEPUTY 1
#define IDENTITY_OUTLAW 2
#define IDENTITY_RENEGADE 3

#define WIN_SHERIFF_AND_DEPUTY 1
#define WIN_OUTLAW 2
#define WIN_RENEGADE 3

#define LIVE 1
#define DEAD 0

#define CHARACTER_BART 0        //扣一滴抽一張牌
#define CHARACTER_BLACK 1       //@必須展示抽到的第二張, 若為紅心或方塊, 則在抽一張
#define CHARACTER_CALAMITY 2    //殺當閃閃當殺
#define CHARACTER_EL 3          //若被對方扣一滴, 可以抽對方一張牌
#define CHARACTER_JESSE 4       //@第一張可以決定要抽對手的還是牌堆的 第二張抽牌堆
#define CHARACTER_JOURDONNAIS 5 //當他成為「砰！」的目標，他可以進行「抽牌判定！」，如果是紅心就閃過
#define CHARACTER_KIT 6         //@抽牌階段改為看三張選兩張
#define CHARACTER_LUCKY 7       //當他進行「抽牌判定！」，可以從牌庫頂直接翻開兩張牌，並選一張作為判定結果
#define CHARACTER_PAUL 8        //@所有玩家看他距離+1
#define CHARACTER_PEDRO 9       //@可選擇棄牌堆頂的那一張作為抽兩張牌的第一張
#define CHARACTER_ROSE 10       //看所有玩家的距離-1
#define CHARACTER_SID 11        //棄兩張回一滴
#define CHARACTER_SLAB 12       //殺要用兩張閃檔
#define CHARACTER_SUZY 13       //沒牌可以抽一張
#define CHARACTER_VULTURE 14    //當有玩家死亡 獲得他所有牌
#define CHARACTER_WILLY 15      //出牌階段無限出殺

#define HAVE 1
#define NONE 0

#define EMPTY -1 // card

typedef struct _sCharacter
{
    int id;
    char characterName[1000];
    char skill[1000];
    int32_t hp;
} sCharacter;

typedef struct _sPlayer
{
    sCharacter character;  // 角色
    int ID;                // 玩家編號
    int hp;                // 生命值
    int status;            // 狀態
    int identity;          // 身分
    sListhead hand;        // 手牌
    int plus_one;          // +1
    int decrease_one;      // -1
    int weapon;            // 武器
    int barrel;            // 防具
    int in_jail;           // 是否在監獄
    int on_bomb;           // 是否有炸藥
    struct _sPlayer *prev; // 上一位
    struct _sPlayer *next; // 下一位
} sPlayer;

typedef struct _sCard
{
    int ID;
    char name[1000];
    int32_t pokerNumber;
} sCard;

void time_stop(int t);

void printCharacterInformation(sCharacter character);
void showPoker(int number);

void init_character(sCharacter character[]);
void init_card(sCard card[]);

void SWAP(int *pX, int *pY);
void swap_card(sCard *pX, sCard *pY);

void shuffle(int *ary, int length);
void shuffleIdentity(sPlayer player[], int playerNumber);
void shuffleCharacter(sPlayer player[], int playerNumber, sCharacter character[], int characterNumber);
void shuffleCard(sCard card[], int cardNumber);

void IDtoIdentity(int ID, char *identity);
void IDtoCardPoker(int ID, int *pokerNumber);
void printIdentity(int ID);

int interface_switch(int);
void print_interface(void);

void print_interface_gaming(sPlayer *player, sCard *card, int *deck, int *decardDeck);
void print_interface_gameStart(void);
void print_interface_introduce(void);
void print_interface_operation(void);

// for test
void print_player_information(sPlayer player);
void print_card_information(int id, sCard *card);
void print_interface_victory(int x);
int32_t print_hand_card(sListhead *pList, sCard *card);

// circular list
void make_player_circularlist(sPlayer player[], int playerNumber);
int count_player_bang_distance(sPlayer from, sPlayer to);
int count_player_panic_distance(sPlayer from, sPlayer to);

// determined status
int determined(int *deck, int *discardDeck);
int determined_status(sPlayer *Player, int *deck, int *discardDeck, sCard *card);
int detertermined_game_over(sPlayer *Player);

// draw card
int draw(sPlayer *Player, int *deck, int *discardDeck);
int draw_status(sPlayer *Player, int *deck, int *discardDeck, sCard *card);
int wash_discard_to_desk(int *deck, int *discardDeck);

// discard card
void discard(int id, int *discarddesk);
void discard_status(sPlayer *Player, int *deck, int *discardDeck, sCard *card);

// play
int play_status(sPlayer *Player, int *deck, int *discardDeck, sCard *card);

// skill

// check
int card_exist_in_hand(sPlayer *Player, int id);

// determined poker
int determined_poker_heart(int num);
int determined_poker_diamond(int num);

// 決定生死
int count_player_number(sPlayer *p);
int determined_live_or_die(sPlayer *from, sPlayer *to, int *deck, int *discard_deck);
void determined_killer_get_three_card(sPlayer *from, sPlayer *to, int *deck, int *discard_deck);
