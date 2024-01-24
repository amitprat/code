#include "../Header.h"

/*
5! = 5 * 4 * 3 * 2 * 1 = 120 (it contains 1 zero).
How many zeroes will be contained in 100! then.
Explain with logic.
*/

int countTrailingZerosOfFactorial(int n)
{
    int count = 0;
    for (int powerOfFive = 5; n / powerOfFive > 0; powerOfFive *= 5)
    {
        count += n / powerOfFive;
    }
    return count;
}