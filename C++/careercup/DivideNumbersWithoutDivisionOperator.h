#include "../Header.h"

int divide(int p, int q)
{
    int tmp = 1;
    while (q <= p)
    {
        tmp <<= 1;
        q <<= 1;
    }

    int result = 0;

    while (tmp > 1)
    {
        tmp >>= 1;
        q >>= 1;

        if (p >= q)
        {
            p -= q;
            result += tmp;
        }
    }

    return result;
}