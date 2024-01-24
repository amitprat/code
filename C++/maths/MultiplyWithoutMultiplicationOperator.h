#pragma once
#include "../Header.h"

/*
* Write a method that multiplies two integers without using multiply operator
*/

int Mul(int a, int b)
{
    int ans = 0;
    int sign = ((a ^ b) >> 31);
    a = abs(a);
    b = abs(b);
    while (b)
    {
        if (b & 0x01) ans += a;
        b >>= 1;
        a <<= 1;
    }
    return sign ? (~ans + 1) : ans;
}