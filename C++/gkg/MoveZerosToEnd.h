#include "../Header.h"

/*
Given an array of integers.

Move all non-zero elements to the left of all zero elements.
*/

static void moveNonZeroToLeft(int array[], int n)
{
    int w = 0;
    for (int r = 0; r < n; r++)
    {
        if (array[r] != 0)
        {
            array[w++] = array[r];
        }
    }
    for (; w < n; w++)
    {
        array[w] = 0;
    }
}