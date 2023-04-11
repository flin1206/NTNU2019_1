#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "myvector.h"
#define PI 3.1415926

int main()
{
    sVector *pA = myvector_init(), *pB = myvector_init(), *pC = myvector_init();
    double x, y, m = 2, j = 7;
    myvector_set(pB, 1, 11, 0);
    myvector_set(pC, 1, 0, 5);
    myvector_print(pC, 1);
    myvector_inner_product(&x, pB, pC);
    printf("inn:%lf\n", x);
    myvector_area(&x, pB, pC);
    printf("area:%lf\n", x);
    return 0;
}