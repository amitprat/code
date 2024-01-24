#include "../Header.h"

/*
You have two numbers decomposed in binary representation, write a function that sums them and returns the result.

Input: 100011, 100100
Output: 1000111

Theory

sum = a xor b xor c
carry = ab + bc+ ac

*/

int addBinary(int a1[], int a2[], int result[])
{
    int i, c = 0;
    for (i = 0; i < 8; i++)
    {
        result[i] = ((a1[i] ^ a2[i]) ^ c);                 //a xor b xor c
        c = ((a1[i] & a2[i]) | (a1[i] & c)) | (a2[i] & c); //ab+bc+ca
    }
    result[i] = c;
    return c;
}