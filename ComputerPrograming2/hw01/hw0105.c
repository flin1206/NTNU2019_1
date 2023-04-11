#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysplit.h"
#include <signal.h>
#include "except.h"
#include "ANSI-color-codes.h"

#ifdef DEBUG
    #define D_INFO(x, ...) printf(RED "DEBUG_INFO: " CRESET x "\n", ##__VA_ARGS__)
#else
    #define D_INFO(x, ...)
#endif

#define P_INFO(x, ...) printf(RED "INFO: " CRESET x "\n", ##__VA_ARGS__)

#define EXC 1

TRYBUF(QQ);

void handler(int sig)
{
    SIGTHROW(QQ, EXC);
}

int score = 20;

int main(void)
{
    signal(SIGFPE, handler);
    signal(SIGSEGV, handler);

    char **list = NULL;
    int ctr = 0;
    int ret = 0;

    P_INFO("1. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, "aaaa,bcb,cc,d", ",");
        for(int i = 0; i < ctr; i++)
        {
            printf("%s\n",list[i]);
        }
    }
    SIGCATCH(EXC)
    {
        score -= 3;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("2. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, "aaaa   bcb  cc d ", "  ");
        if (ctr != 3 || ret != 0)
            SIGTHROW(QQ, EXC);
        for (int i = 0; i < ctr; ++i)
            D_INFO("list[%d]: %s", i, list[i]);
        if ( strcmp(list[0], "aaaa") || strcmp(list[1], " bcb"), 
            strcmp(list[2], "cc d "))
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 3;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("3. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, "aaa   bb ", " ");
        if (ctr != 5 || ret != 0)
            SIGTHROW(QQ, EXC);
        for (int i = 0; i < ctr; ++i)
            D_INFO("list[%d]: %s", i, list[i]);
        if ( strcmp(list[0], "aaa") || strcmp(list[1], ""), 
            strcmp(list[2], "") || strcmp(list[3], "bb") || strcmp(list[4], ""))
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 3;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("4. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, "aaaa,bcb,cc,d", ",");
        if (ctr != 4 || ret != 0)
            SIGTHROW(QQ, EXC);
        list[0][0] = 'e';
        for (int i = 0; i < ctr; ++i)
            D_INFO("list[%d]: %s", i, list[i]);
        if ( strcmp(list[0], "eaaa") || strcmp(list[1], "bcb"), 
            strcmp(list[2], "cc") || strcmp(list[3], "d"))
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 3;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("5. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, NULL, ",");
        if (ret != -1)
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 2;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("6. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, "aaa,bb,c", "");
        if (ret != -1)
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 2;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("7. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, "aaaa   bcb		cc	 d", NULL);
        if (ctr != 4 || ret != 0)
            SIGTHROW(QQ, EXC);
        for (int i = 0; i < ctr; ++i)
            D_INFO("list[%d]: %s", i, list[i]);
        if ( strcmp(list[0], "aaaa") || strcmp(list[1], "bcb"), 
            strcmp(list[2], "cc") || strcmp(list[3], "d"))
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 2;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

	P_INFO("8. ");
    SIGTRY(QQ)
    {
        ret = mystrsplit(&list, &ctr, "	 	aaaa   bcb		cc	 d 	 ", NULL);
        if (ctr != 4 || ret != 0)
            SIGTHROW(QQ, EXC);
        for (int i = 0; i < ctr; ++i)
            D_INFO("list[%d]: %s", i, list[i]);
        if ( strcmp(list[0], "aaaa") || strcmp(list[1], "bcb"), 
            strcmp(list[2], "cc") || strcmp(list[3], "d"))
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 2;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("score: %d", score);

    return 0;
}