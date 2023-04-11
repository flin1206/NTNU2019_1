#pragma once
typedef struct _sMixedNumber{
    int intpart;
    int x;
    int y;
}sMixedNumber;
int mystrsplit(char ***pppList , int *pCounter , const char *pStr, const char *pSeparator);
void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
void mixed_shift( sMixedNumber pNumber[], int32_t from , int32_t *size);
void array_shift( char *array,int32_t from , int32_t *size );