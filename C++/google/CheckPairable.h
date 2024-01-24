#include "../Header.h"

/*
https://www.careercup.com/question?id=14820665

Write a program to determine whether n/2 distintinctve pairs can be formed from given n integers where n is even and 
each pair's sum is divisible by given k. Numbers cannot be repeated in the pairs, that means only you can form total n/2 pairs.
*/

bool checkPairable(List<int> nums, uint k)
{
    if (k == 0)
        throw... uint counts[k];
    for (int i = 0; i < k; i++)
    {
        counts[k] = 0;
    }

    foreach (int num in nums)
    {
        counts[num % k]++;
    }
    if (counts[0] % 2 != 0)
        return false;
    if (k % 2 == 0)
    {
        if (counts[k / 2] % 2 != 0)
            return false;
    }
    for (int i = 0; i <= k / 2; i++)
    {
        if (counts[i] != counts[k - i])
            return false;
    }
    return true;
}