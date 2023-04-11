#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926
#include "myvector.h"

// Memory allocation. Fill zeros to all memory block.
sVector *myvector_init()
{
    calloc(1, sizeof(sVector));
}

// If error , return -1; otherwise , return 0;
int myvector_set(sVector *pVector, uint8_t type, double a, double b)
{
    if (type == 1)
    {
        pVector->type = type;
        pVector->data.c.x = a;
        pVector->data.c.y = b;
    }
    else if (type == 2)
    {
        pVector->type = type;
        pVector->data.p.distance = a;
        while (b < 0)
        {
            b += 2 * PI;
        }
        while (b >= 2 * PI)
        {
            b -= 2 * PI;
        }
        pVector->data.p.angle = 180 * (b / PI);
    }
    else
    {
        return -1;
    }
}

// Print the given vector according to the given type.
// If Cartesian , print (x,y).
// If polar , print (distance , theta -pi). EX: distance=2 and angle=90 degree ,print (2,0.5-pi).
// Theta must be between 0 and 2.
// If error , return -1; otherwise , return 0;
int myvector_print(const sVector *pVector, uint8_t type)
{
    // if the type is same, just print it
    if (pVector == NULL)
    {
        return -1;
    }
    else if ((type == 1) && (pVector->type == 1))
    {
        printf("(%lf,%lf)\n", pVector->data.c.x, pVector->data.c.y);
    }
    else if ((type == 2) && (pVector->type == 2))
    {
        printf("(%lf,%lf-pi)\n", pVector->data.p.distance, pVector->data.p.angle / 180);
    }
    // if not, trans it to particular form and print it
    else if ((type == 1) && (pVector->type == 2))
    {
        sVector *pX = myvector_init();
        *pX = *pVector;
        myvector_ptoc(pX);
        printf("(%lf,%lf)\n", pX->data.c.x, pX->data.c.y);
        free(pX);
    }
    else if ((type == 2) && (pVector->type == 1))
    {
        sVector *pX = myvector_init();
        *pX = *pVector;
        myvector_ctop(pX);
        printf("(%lf,%lf-pi)\n", pX->data.p.distance, pX->data.p.angle / 180);
        free(pX);
    }
    else
    {
        return -1;
    }
    return 0;
}

// A = B + C
// A's type is set to B's type.
// If error , return -1; otherwise , return 0;
int myvector_add(sVector *pA, const sVector *pB, const sVector *pC)
{
    if ((pA == NULL) || (pB == NULL) || (pC == NULL))
    {
        return -1;
    }
    sVector *pD = myvector_init();
    sVector *pE = myvector_init();
    *pD = *pB;
    *pE = *pC;
    myvector_ptoc(pD);
    myvector_ptoc(pE);
    myvector_ptoc(pA);
    pA->data.c.x = pD->data.c.x + pE->data.c.x;
    pA->data.c.y = pD->data.c.y + pE->data.c.y;

    if (pB->type == 2)
    {
        myvector_ctop(pA);
    }
    free(pD);
    free(pE);
    return 0;
}

// A = B dot C
// If error , return -1; otherwise , return 0;
int myvector_inner_product(double *pA, const sVector *pB, const sVector *pC)
{
    if ((pA == NULL) || (pB == NULL) || (pC == NULL))
    {
        return -1;
    }
    sVector *pD = myvector_init();
    sVector *pE = myvector_init();
    *pD = *pB;
    *pE = *pC;
    myvector_ptoc(pD);
    myvector_ptoc(pE);
    *pA = pD->data.c.x * pE->data.c.x + pD->data.c.y * pE->data.c.y;
    free(pD);
    free(pE);
    return 0;
}

// Get the area of the parallelogram spanned by two vectors.
// If error , return -1; otherwise , return 0;
int myvector_area(double *pArea, const sVector *pB, const sVector *pC)
{
    if ((pArea == NULL) || (pB == NULL) || (pC == NULL))
    {
        return -1;
    }
    sVector *pD = myvector_init();
    sVector *pE = myvector_init();
    *pD = *pB;
    *pE = *pC;
    myvector_ptoc(pD);
    myvector_ptoc(pE);
    double Area = (pD->data.c.x * pE->data.c.y - pD->data.c.y * pE->data.c.x);
    if (Area < 0)
    {
        Area = Area * (-1);
    }
    *pArea = Area;
    free(pD);
    free(pE);
    return 0;
}

// Given a target point , find the closest point which can be combined from two given vectors with integer coefficients.
// (*pX,*pY) = m*A + n*B, m and n must be integers.
// (*pX,*pY) is the closet point to (*pTx ,*pTy)
// If error , return -1; otherwise , return 0;
int myvector_cvp(double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB)
{
    if ((pX == NULL) || (pY == NULL) || (pTx == NULL) || (pTy == NULL) || (pA == NULL) || (pB == NULL))
    {
        return -1;
    }

    // store pA and pB in pD and pE in cartesian form, do the simultaneous equations
    double o = 0, p = 0;
    sVector *pD = myvector_init();
    sVector *pE = myvector_init();
    *pD = *pA;
    *pE = *pB;
    myvector_ptoc(pD);
    myvector_ptoc(pE);
    // printf("v1x:%lf v1y:%lf v2x:%lf v2y:%lf\n",pD->data.c.x,pD->data.c.y,pE->data.c.x,pE->data.c.y);
    o = (*pTy - *pTx * pE->data.c.y / pE->data.c.x) / (pD->data.c.y - pD->data.c.x * pE->data.c.y / pE->data.c.x);
    p = (*pTx - o * pD->data.c.x) / pE->data.c.x;
    // printf("o:%lf p:%lf \n",o,p);

    // trans the double o p to int m n, find the nearest four point and compare the distance
    int m = (int)o;
    int n = (int)p;
    double distance[4], x[4], y[4];
    x[0] = m * pD->data.c.x + n * pE->data.c.x;
    y[0] = m * pD->data.c.y + n * pE->data.c.y;
    if (o > 0)
    {
        x[1] = (m + 1) * pD->data.c.x + n * pE->data.c.x;
        y[1] = (m + 1) * pD->data.c.y + n * pE->data.c.y;
        if (p > 0)
        {
            x[2] = m * pD->data.c.x + (n + 1) * pE->data.c.x;
            y[2] = m * pD->data.c.y + (n + 1) * pE->data.c.y;
            x[3] = (m + 1) * pD->data.c.x + (n + 1) * pE->data.c.x;
            y[3] = (m + 1) * pD->data.c.y + (n + 1) * pE->data.c.y;
        }
        else
        {
            x[2] = m * pD->data.c.x + (n - 1) * pE->data.c.x;
            y[2] = m * pD->data.c.y + (n - 1) * pE->data.c.y;
            x[3] = (m + 1) * pD->data.c.x + (n - 1) * pE->data.c.x;
            y[3] = (m + 1) * pD->data.c.y + (n - 1) * pE->data.c.y;
        }
    }
    else
    {
        x[1] = (m - 1) * pD->data.c.x + n * pE->data.c.x;
        y[1] = (m - 1) * pD->data.c.y + n * pE->data.c.y;
        if (p > 0)
        {
            x[2] = m * pD->data.c.x + (n + 1) * pE->data.c.x;
            y[2] = m * pD->data.c.y + (n + 1) * pE->data.c.y;
            x[3] = (m - 1) * pD->data.c.x + (n + 1) * pE->data.c.x;
            y[3] = (m - 1) * pD->data.c.y + (n + 1) * pE->data.c.y;
        }
        else
        {
            x[2] = m * pD->data.c.x + (n - 1) * pE->data.c.x;
            y[2] = m * pD->data.c.y + (n - 1) * pE->data.c.y;
            x[3] = (m - 1) * pD->data.c.x + (n - 1) * pE->data.c.x;
            y[3] = (m - 1) * pD->data.c.y + (n - 1) * pE->data.c.y;
        }
    }
    distance[0] = distance_2point(*pTx, *pTy, x[0], y[0]);
    *pX = x[0];
    *pY = y[0];
    double smallestDistance = distance[0];
    for (int i = 1; i < 4; i++)
    {
        distance[i] = distance_2point(*pTx, *pTy, x[i], y[i]);
        if (distance[i] < smallestDistance)
        {
            smallestDistance = distance[i];
            *pX = x[i];
            *pY = y[i];
        }
    }
    free(pD);
    free(pE);
    return 0;
}

// trans polar to cartesian
int myvector_ptoc(sVector *pX)
{
    if (pX->type == 1)
    {
        return 0;
    }
    else
    {
        pX->type = 1;
        double poDistance = pX->data.p.distance;
        double poAngle = pX->data.p.angle / 180;
        pX->data.p.distance = 0;
        pX->data.p.angle = 0;
        pX->data.c.x = poDistance * cos(PI * poAngle);
        pX->data.c.y = poDistance * sin(PI * poAngle);
        return 1;
    }
}

// trans cartesian to polar
int myvector_ctop(sVector *pX)
{
    if (pX->type == 2)
    {
        return 0;
    }
    else
    {
        pX->type = 2;
        double cX = pX->data.c.x;
        double cY = pX->data.c.y;
        pX->data.c.x = 0;
        pX->data.c.y = 0;
        pX->data.p.distance = sqrt(pow(cX, 2) + pow(cY, 2));
        if (pX->data.p.distance == 0)
        {
            pX->data.p.angle = 0;
        }
        pX->data.p.angle = 180 / PI * atan2(cX, cY);
        if (pX->data.p.angle < 0)
        {
            pX->data.p.angle = pX->data.p.angle + 360;
        }
        return 1;
    }
}

// calculate the distance between two point
double distance_2point(double pAx, double pAy, double pBx, double pBy)
{
    double ans = sqrt(pow(pAx - pBx, 2) + pow(pAy - pBy, 2));
    return ans;
}
