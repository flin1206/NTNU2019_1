#include "linklist.h"

int32_t add_node(int id, sListhead *list)
{
    sListnode *pNewNode = calloc(1, sizeof(sListnode));
    pNewNode->id = id;
    pNewNode->pNext = NULL;

    if (list->num == 0)
    {
        list->head = pNewNode;
        list->tail = pNewNode;
    }
    else
    {
        list->tail->pNext = pNewNode;
        list->tail = pNewNode;
    }

    list->num += 1;

    return 0;
}

int32_t del_node(int id, sListhead *list)
{
    if (list->num == 0)
    {
        return -1;
    }

    sListnode *pNode = list->head;
    sListnode *pPreNode = NULL;

    if (pNode->id == id)
    {
        if (list->head == list->tail)
        {
            free(list->head);
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->head = pNode->pNext;
            free(pNode);
        }
        list->num -= 1;
        return 0;
    }

    while (pNode != NULL && pNode->id != id)
    {
        pPreNode = pNode;
        pNode = pNode->pNext;
    }

    if (pNode)
    {
        pPreNode->pNext = pNode->pNext;

        if (list->tail == pNode)
        {
            list->tail = pPreNode;
        }

        free(pNode);
        list->num -= 1;
        return 0;
    }
    return -1;
}

int32_t check_node(int id, sListhead *list)
{

    if (list->num == 0)
    {
        return 0;
    }
    else
    {
        sListnode *pNode = list->head;
        while (pNode)
        {
            if(pNode->id == id)
                return 1;
            pNode = pNode->pNext;
        }
    }
    return 0;
}