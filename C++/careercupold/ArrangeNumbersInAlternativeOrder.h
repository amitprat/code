#include "../Header.h"
/*
https://www.careercup.com/question?id=5684901156225024

Arrange the numbers in an array in alternating order.
For example if the array is [a1, a2, a3, a4.. ]arrange the array such that b1<=b2>=b3<=b4 and so on.
Sampe Input: 3 5 7 8 4 9
Sample Output: 3 < 5 > 4 < 8 >7 < 9
*/

void arrangeList(int A[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (i % 2 && A[i] < A[i - 1])
            swap(A[i], A[i - 1]);
        if (i % 2 == 0 && A[i] > A[i - 1])
            swap(A[i], A[i - 1]);
    }
    return;
}