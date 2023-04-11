#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
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

int main(void)
{
    signal(SIGFPE, handler);
    signal(SIGSEGV, handler);

    int score = 20;

    char *s = NULL;
    char *endptr = NULL;
    long n = 0;

    P_INFO("1. ");
    SIGTRY(QQ)
    {
        s = "123456a";
        endptr = NULL;
        n = mystrtol(s, &endptr, 10);
        printf("n: %ld, endptr: %c", n, *endptr);
        if (n != 123456 || *endptr != '\0')
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 4;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("2. ");
    SIGTRY(QQ)
    {
        s = "0x123456a";
        endptr = NULL;
        n = mystrtol(s, &endptr, 10);
        printf("n: %ld, endptr: %c", n, *endptr);
        if (n != 0 || *endptr != 'x')
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 4;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("3. ");
    SIGTRY(QQ)
    {
        s = "0x123456a";
        endptr = NULL;
        n = mystrtol(s, &endptr, 16);
        printf("n: %ld, endptr: %c", n, *endptr);
        if (n != 1193046 || *endptr != '\0')
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 4;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("4. ");
    SIGTRY(QQ)
    {
        s = "-0123456a";
        endptr = NULL;
        n = mystrtol(s, &endptr, 8);
        printf("n: %ld, endptr: %c", n, *endptr);
        if (n != -42798 || *endptr != '\0')
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 4;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("5. ");
    SIGTRY(QQ)
    {
        s = "123456a";
        endptr = NULL;
        n = mystrtol(s, &endptr, 23);
        printf("n: %ld, endptr: %c", n, *endptr);
        if (n != 7034763 || *endptr != '\0')
            SIGTHROW(QQ, EXC);
        P_INFO("correct");
    }
    SIGCATCH(EXC)
    {
        score -= 4;
        P_INFO("wrong");
    }
    SIGFINALLY {}
    SIGETRY;

    P_INFO("score: %d", score);

    return 0;
}