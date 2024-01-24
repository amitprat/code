#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5104572540387328

Given a sorted array of integers, write a function that will return the number with the biggest number of repetitions.
(Asked to refine the solution to be more efficient)
*/
class FindMaxRepeatingElement
{
public:
    static void test()
    {
        FindMaxRepeatingElement obj;

        int a[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5 };
        auto res = obj.maxRepeatingElementBinarySearch(a, sizeof(a) / sizeof(int));
        cout << "Max repeating element: " << res.first << ", " << res.second << endl;
    }

    int findMaximumRepeatingElement(int* a, int n)
    {
        int count = 1, maxcount = 1, maxelement = a[0];
        int element = a[0];
        int i = 1;
        while (i < n)
        {
            if (a[i] == element)
            {
                count++;
                if (count > maxcount)
                {
                    maxcount = count;
                    maxelement = a[i];
                }
            }
            else
            {
                element = a[i];
                count = 1;

            }
            i++;
        }
        return maxelement;
    }

    pair<int, int> maxRepeatingElementBinarySearch(int arr[], int n)
    {
        int s = 0;
        int mxElem = INT_MIN;
        int mxCnt = 0;

        while (s < n)
        {
            int end = maxRepeatingElementBinarySearch(arr, s, n - 1, arr[s]);
            if (end - s + 1 > mxCnt)
            {
                mxCnt = end - s + 1;
                mxElem = arr[s];
            }
            s = end + 1;
        }

        return { mxElem,mxCnt };
    }

    int maxRepeatingElementBinarySearch(int arr[], int s, int e, int k)
    {
        if (s == e) return arr[s] == k ? s : -1;
        if (s > e) return -1;
        int m = (s + e + 1) / 2;
        if (k < arr[m]) return maxRepeatingElementBinarySearch(arr, s, m - 1, k);
        return maxRepeatingElementBinarySearch(arr, m, e, k);
    }
};