#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "madoka.h"

#define SJMAX 20
#define MHSJMAX 4
#define MJMAX 3

int energy = 0;

void Delay(unsigned int secs)
{
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime)
        ;
}

int main(void)
{
    int r = 0;
    int sj_cnt = SJMAX - MHSJMAX - MJMAX;
    Shoujo *sj_list[SJMAX] = {0};
    Mahoushoujo *mhsj_list[MHSJMAX] = {0};
    Majo *mj_list[MJMAX] = {0};

    Mahoushoujo *homura = mhsj_list[1] = Mahoushoujo_ctor(malloc(sizeof(Mahoushoujo)), "Homura", "Madoka..", Homura_skill);
    Mahoushoujo *sayako = mhsj_list[2] = Mahoushoujo_ctor(malloc(sizeof(Mahoushoujo)), "Sayaka", "QQ", Sayaka_skill);
    Mahoushoujo *kyoko = mhsj_list[3] = Mahoushoujo_ctor(malloc(sizeof(Mahoushoujo)), "Kyoko", "QQ", Kyoko_skill);

    mj_list[0] = Majo_ctor(malloc(sizeof(Majo)), "No name", "Majo is hopeless.");

    sj_list[0] = Shoujo_ctor(malloc(sizeof(Shoujo)), "Madoka", "OAO");

    for (int i = 1; i < MHSJMAX; ++i)
        sj_list[i] = mhsj_list[i];

    sj_list[MHSJMAX] = mj_list[0];
    for (int i = MHSJMAX + MJMAX; i < SJMAX; ++i)
        sj_list[i] = Shoujo_ctor(malloc(sizeof(Shoujo)), "shoujo", "shoujo is blessing.");

    while (true)
    {
        Delay(1);
        printf("--------------------------\n");
        printf("energy: %d\n", energy);
        printf("--------------\n");
        for (int i = 0; i < SJMAX; ++i)
        {
            if (sj_list[i])
            {
                printf("%s: ", sj_list[i]->name);
                sj_list[i]->do_wish(sj_list[i]);
            }
        }

        for (int i = 0; i < MHSJMAX; ++i)
        {
            if (mhsj_list[i])
            {
                for (int o = 0; o < MJMAX; ++o)
                {
                    if (mj_list[o])
                    {
                        mhsj_list[i]->skill(mhsj_list[i], mj_list[o]);
                        mhsj_list[i]->attack(mhsj_list[i], mj_list[o]);
                    }
                }
            }
        }

        for (int i = 0; i < MJMAX; ++i)
        {
            if (!mj_list[i])
                continue;

            do
            {
                r = rand() % (MHSJMAX - 1) + 1;
            } while (!mhsj_list[r]);
            mj_list[i]->attack(mj_list[i], mhsj_list[r]);

            if (sj_cnt == 0)
                continue;
            do
            {
                r = rand() % (SJMAX - MJMAX - MHSJMAX) + MJMAX + MHSJMAX;
            } while (!sj_list[r]);
            mj_list[i]->kekkai(mj_list[i], sj_list[r]);
        }

        // 少女全部狀態檢查
        for (int i = 0; i < SJMAX; ++i)
        {
            if (!sj_list[i])
                continue;
            // 若少女絕望，生命歸0
            if (sj_list[i]->is_despair(sj_list[i]))
            {
                sj_list[i]->despair(sj_list[i]);
                // 若該人為Sayako 則轉為魔女
                if (i == 2)
                {
                    mhsj_list[2] = NULL;
                    mj_list[1] = sj_list[2] = (void *)mhsj_to_mj((Mahoushoujo *)sj_list[2]);
                    energy += 10000;
                }
            }
            // 若少女生命<=0
            if (sj_list[i]->is_dead(sj_list[i]))
            {
                // 將少女資料及少女位址free
                Shoujo_dtor(sj_list[i]);
                free(sj_list[i]);
                sj_list[i] = NULL;
                // 若是魔法少女
                if (i < MHSJMAX)
                {
                    mhsj_list[i] = NULL;
                    // Sayoka魔女初始化
                    if (i == 2)
                        sj_list[2 + MHSJMAX] = mj_list[2] = Majo_ctor(malloc(sizeof(Majo)), "Nightmare", "Hahaha.");
                }
                // 若是魔女
                else if (i < MHSJMAX + MJMAX)
                {
                    mj_list[i - MHSJMAX] = NULL;
                }
                // 少女
                else
                    sj_cnt--;
            }
        }

        if (((Shoujo *)homura)->kimoji <= -80)
        {
            Mahoushoujo *homura = mhsj_list[0] = Mahoushoujo_ctor(malloc(sizeof(Mahoushoujo)), "Madoka", "Mo daijobu daiyo", Madoka_skill);
        }
    }

    return 0;
}