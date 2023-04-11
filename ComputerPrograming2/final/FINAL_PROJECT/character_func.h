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
#include "bang.h"

void player_dead(sPlayer *player, int *discardDeck);

// 判斷是否有人死 回傳死的人的id 沒死就回傳0
int detect_death(sPlayer *to);

// 找殺 沒找到回傳-1
int find_beer(sListhead *list);

// 問各個玩家要不要用桃 回傳0是沒人幫忙回 回傳1是有回到
int if_beer(sPlayer *to, int *discardDeck);

// 傳入扣多少血
void bart_cassidy(sPlayer *to, int n, int *deck, int *discardDeck);

// 先選擇要用殺還是閃
int calamity_janet(sPlayer *to);

// 拿一張 如果超過一血就多跑幾次 不然在這邊塞迴圈也行
void el_gringo(sPlayer *from, sPlayer *to);

// 跟barrel一樣
void jourdonnais(sPlayer *to);

// 判定可以抽2張
int lucky_duke(sPlayer *to, int *deck, int *discardDeck);

// 兩閃擋一殺
void slab_the_killer(sPlayer *from, sPlayer *to, int *discardDeck);
// 沒牌就抽一張
void suzy_lafayette(sPlayer *to, int *deck, int *discardDeck);

void vulture_sam(sPlayer *from, sPlayer *to);
void sid_ketchum(sPlayer *to, int *discardDeck, sCard *card);