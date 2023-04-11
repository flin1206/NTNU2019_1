#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void reverseArr(int arr[], int from, int to);

int main()
{

    double input, fractionPart;
    int exponent[11] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int fraction[52] = {0};
    printf("Please enter a floating -point number (double precision):");
    scanf("%lf", &input);
    if (input == 0)
    {
        printf("Sign: 1\nExponent:00000000000\nFraction:0000000000000000000000000000000000000000000000000000\n0 = 0\n");
        return 0;
    }

    // define positive
    int sign = 0;
    if (input < 0)
    {
        sign = 1;
    }

    // store int and frac part
    int intPart = (int)input;
    fractionPart = input - intPart;
    intPart = abs(intPart);
    if (fractionPart < 0)
    {
        fractionPart = fractionPart * (-1);
    }

    // put int digit in fraction part
    int countExponent = 0;
    for (int i = 0; intPart != 0; i++)
    {
        fraction[i] = intPart % 2;
        intPart = intPart / 2;
        if (intPart != 0)
        {
            exponent[10]++;
        }
        countExponent = i;
    }

    // reverse the digit
    reverseArr(fraction, 0, countExponent);

    // make it be right format
    for (int i = 0; i < 51; i++)
    {
        fraction[i] = fraction[i + 1];
    }

    // put fraction part into array ( from pos countExponent )
    for (int i = countExponent; i < 52; i++)
    {
        if (fractionPart >= pow(0.5, i - countExponent + 1))
        {
            fractionPart -= pow(0.5, i - countExponent + 1);
            fraction[i] = 1;
        }
    }

    // situation when there is no int
    intPart = (int)abs(input);
    if (intPart == 0)
    {
        countExponent = 0;
        for (int i = 0; i < 51; i++)
        {
            if (fraction[i] == 1)
            {
                countExponent = i;
                break;
            }
        }

        for (int i = 0; i < countExponent + 1; i++)
        {
            exponent[10]--;
            for (int j = 0; j < 51; j++)
            {
                fraction[j] = fraction[j + 1];
            }
        }
    }

    // shift exponent
    for (int i = 10; i > 0; i--)
    {
        if (exponent[i] != 1)
        {
            exponent[i - 1] += (exponent[i] / 2);
        }
        if (exponent[i] % 2 == -1)
        {
            exponent[i - 1] -= 1;
        }
        exponent[i] = abs(exponent[i] % 2);
    }

    // print each digit and count fraction digit 1 number
    int digitexist[52] = {0};
    printf("Sign: %d\n", sign);
    printf("Exponent:");
    for (int i = 0; i < 11; i++)
    {
        printf("%d", exponent[i]);
    }
    printf("\nFraction:");
    for (int i = 0; i < 52; i++)
    {
        if (fraction[i] == 1)
        {
            digitexist[i] = 1;
        }

        printf("%d", fraction[i]);
    }
    printf("\n");

    countExponent = 0;
    for (int i = 0; i < 11; i++)
    {
        countExponent += exponent[i] * pow(2, 10 - i);
    }

    // print the summary
    printf("%lf = ", input);
    printf("(-1)^%d ", sign);
    printf(" * (1");
    for (int i = 0; i < 52; i++)
    {
        if (digitexist[i] == 1)
        {
            printf(" + 2^-%d", i + 1);
        }
    }
    printf(") * 2^(%d - 1023)\n", countExponent);

    return 0;
}

void reverseArr(int arr[], int from, int to)
{
    for (int i = from, j = to;; i++)
    {
        if (i >= j)
        {
            break;
        }
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        j--;
    }
}
