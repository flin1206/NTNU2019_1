#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "madoka.h"

Entity *Entity_ctor(Entity *this)
{
    this->hp = 100;
    this->is_dead = Entity_is_dead;
}
void Entity_dtor(Entity *this)
{
    free(this);
}
int Entity_is_dead(void *this)
{
    if (((Shoujo *)this)->base.hp <= 0)
    {
        return 1;
    }
    else
    {
        return 0;
        ;
    }
}

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish)
{
    Entity_ctor(&(this->base));
    this->name = malloc(sizeof(char) * strlen(name));
    this->wish = malloc(sizeof(char) * strlen(wish));
    strcpy(this->name, name);
    strcpy(this->wish, wish);
    this->kimoji = 100;
    this->is_dead = Entity_is_dead;
    this->is_despair = Shoujo_is_despair;
    this->do_wish = Shoujo_do_wish;
    this->despair = Shoujo_despair;
}
void Shoujo_dtor(Shoujo *this)
{
}
int Shoujo_is_despair(void *this)
{
    if (((Shoujo *)this)->kimoji <= -100)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Shoujo_do_wish(void *this)
{
    printf("%s\n", ((Shoujo *)this)->wish);
}
void Shoujo_despair(void *this)
{
    ((Shoujo *)this)->base.hp = 0;
}

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill)
{
    this->base = *Shoujo_ctor(this, name, wish);
    this->atk = 100;
    this->is_dead = Mahoushoujo_dtor;
    this->do_wish = Mahoushoujo_do_wish;
    this->attack = Mahoushoujo_attack;
    this->skill = skill;
}
void Mahoushoujo_dtor(Mahoushoujo *this)
{
    // free(this);
}
void Mahoushoujo_do_wish(void *this)
{
    printf("%s\n", ((Mahoushoujo *)this)->base.wish);
    printf("But nothing is good.\n");
    ((Mahoushoujo *)this)->base.kimoji -= 10;
}
void Mahoushoujo_attack(Mahoushoujo *this, void *enemy)
{
    ((Majo *)enemy)->base.base.hp -= 100;
}
void Mahoushoujo_despair(void *this)
{
    printf("Watashii de, hondo baga\n");
}

Majo *Majo_ctor(Majo *this, const char *name, const char *wish)
{
    this->base = *Shoujo_ctor(this, name, wish);
    this->atk = 10;
    this->base.base.hp = (this->base.base.hp) * 5;
    this->attack = Majo_attack;
    this->kekkai = Majo_kekkai;
    this->is_dead = Entity_is_dead;
}
void Majo_dtor(Majo *this)
{
}
void Majo_attack(Majo *this, void *enemy)
{
    ((Mahoushoujo *)enemy)->base.base.hp -= this->atk;
}
void Majo_kekkai(Majo *this, Shoujo *sj)
{
    sj->kimoji -= 100;
}
void Majo_despair(void *this)
{
}

Majo *mhsj_to_mj(Mahoushoujo *mhsj)
{
}

void Madoka_skill(void *this, void *target)
{
    printf("Madoka become god, end.\n");
    exit(0);
}
void Homura_skill(void *this, void *target)
{
    if ((((Mahoushoujo *)this))->base.base.hp < 50)
    {
        printf("This round is hopeless, Homura go to next round.\n");
        exit(0);
    }
}
void Sayaka_skill(void *this, void *target)
{
    ((Mahoushoujo *)this)->base.base.hp += 30;
    ((Mahoushoujo *)this)->base.kimoji -= 30;
}
void Kyoko_skill(void *this, void *target)
{
    if (((Majo *)target)->base.name = "Sayako")
    {
        ((Mahoushoujo *)this)->base.base.hp = 0;
        ((Majo *)target)->base.base.hp = 0;
    }
}
