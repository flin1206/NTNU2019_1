#pragma once
#include "bang.h"
#include "linklist.h"

#define int int32_t

// 找桃 沒找到回傳-1
int find_beer(sListhead *list);

// 找殺 沒找到回傳-1
int find_bang(sListhead *list);

// 找閃 沒找到回傳-1
int find_mancato(sListhead *list);

// 要在外面先判斷距離
void bang(sPlayer *from, sPlayer *to, int *deck, int *discardDeck);

void mancato();

// 沒打閃就扣一血 電腦會自動打閃
int galting(sPlayer *from, int *deck, int *discardDeck);

// 不打殺就扣血 電腦自動打殺
int indian(sPlayer *from, int *deck, int *discardDeck);

// 距離內可以拿走對方一件裝備或手牌
void panico(sPlayer *from, sPlayer *to);

// 棄掉任一手牌或裝備
void cat_balou(sPlayer *from, sPlayer *to, int *discardDeck);

// 抽2張牌
void diligenza(sPlayer *player, int *deck, int *discardDeck);

// 抽3張牌
void wells_fargo(sPlayer *player, int *deck, int *discardDeck);

// 先抽n張牌 依序選擇要什麼牌
void emproio(sPlayer *to, int *deck, int *discardDeck, sCard *cardDic);

// 血量加1
void birra(sPlayer *to);

// 全體血量加1
void sallon(sPlayer *player);

// 決鬥
void duello(sPlayer *from, sPlayer *to, int *deck, int *discardDeck);

// 被殺可以判定
int barile();

// 判定 跳過回合
void prigione(sPlayer *from);

// 閃電
void dinamite(sPlayer *to);