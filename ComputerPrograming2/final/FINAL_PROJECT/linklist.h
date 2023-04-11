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

typedef struct __listnode
{
    int id;
    struct __listnode *pNext;
    struct __listnode *pPrev;

} sListnode;

typedef struct __listhead
{
    int32_t num;
    sListnode *head;
    sListnode *tail;
} sListhead;

int32_t add_node(int id, sListhead *list);


int32_t del_node(int id, sListhead *list);


int32_t check_node(int id, sListhead *list);
