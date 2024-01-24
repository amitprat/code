#include "../Header.h"

/*
Given an array arr[], find the maximum j – i such that arr[j] > arr[i]

  Input: {34, 8, 10, 3, 2, 80, 30, 33, 1}
  Output: 6  (j = 7, i = 1)

  Input: {9, 2, 3, 4, 5, 6, 7, 8, 18, 0}
  Output: 8 ( j = 8, i = 0)

  Input:  {1, 2, 3, 4, 5, 6}
  Output: 5  (j = 5, i = 0)

  Input:  {6, 5, 4, 3, 2, 1}
  Output: -1 
*/

/*
int maxIndexDiff(int arr[], int n)
{
    int maxDiff;
    int i, j;
 
    int* LMin = new int[(sizeof(int) * n)];
    int* RMax = new int[(sizeof(int) * n)];

    LMin[0] = arr[0];
    for (i = 1; i < n; ++i)
        LMin[i] = min(arr[i], LMin[i - 1]);
 
    RMax[n - 1] = arr[n - 1];
    for (j = n - 2; j >= 0; --j)
        RMax[j] = max(arr[j], RMax[j + 1]);
 
    i = 0, j = 0, maxDiff = -1;
    while (j < n && i < n) {
        if (LMin[i] < RMax[j]) {
            maxDiff = max(maxDiff, j - i);
            j = j + 1;
        }
        else
            i = i + 1;
    }
 
    return maxDiff;
}
*/