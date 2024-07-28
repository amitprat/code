#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=6282862240202752

Given an integer array. Perform circular right shift by n.
Give the best solution.

void reverse(int A[], int start, int end)
{
    while(start < end)
        swap(A[start++], A[end--]);
}

//shift A[0…sz-1] by n (n>0)
void shiftArray(int A[], int sz, int n)
{
    n = n%sz;
    reverse(A, 0, sz-1);
    reverse(A, 0, n-1);
    reverse(A, n, sz-1);
    return;
}
*/

class CircularShift {
};