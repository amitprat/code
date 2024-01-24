#include "../Header.h"

/*
https://www.careercup.com/question?id=5145759489982464

Given an array of integers, sort the array into a wave like array, namely
a1 >= a2 <= a3 >= a4 <= a5.....
*/

/*
There are two O(n) solutions for this problem that does not require ordering.

1. You can find the median in O(n) and then rearrange the elements around the median

2. (Better Solution) If you notice the desired ordering, the even numbered elements are bigger (or equal) than the 
next element, and the odd numbered elements are less than (or equal) than the next element, of course I am assuming the 
array is 0 offset.

So, you can iterate the array and swap the elements that doesn't match this arrangements,e.g., swap A[i] and A[i+1], 
when i is even and A[i] < A[i + 1].
*/

#include <bits/stdc++.h>
using namespace std;

void sortInWave(int arr[], int n)
{
    for (int i = 0; i < n; i += 2)
    {
        if (i > 0 && arr[i] < arr[i - 1])
            swap(arr[i], arr[i - 1]);
        if (i < n - 1 && arr[i] < arr[i + 1])
            swap(arr[i], arr[i + 1]);
    }
}

int main()
{
    int arr[] = {10, 90, 49, 2, 1, 5, 23};
    int n = sizeof(arr) / sizeof(arr[0]);
    sortInWave(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}
