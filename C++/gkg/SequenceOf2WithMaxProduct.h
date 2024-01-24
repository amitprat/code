#pragma once
#include "../Header.h"
/*
Given a sequence of non-negative integers find a subsequence of length 3 having maximum product with the numbers of the subsequence being in ascending order.
Example:
Input: 6 7 8 1 2 3 9 10
Ouput: 8 9 10
*/

int leftLower(vector<int> v, int r)
{
    int p = v[r];
    int elem = 0;
    for (int i = r - 1; i >= 0; i--)
    {
        if (v[i] > elem && v[i] <= p)
            elem = v[i];
    }
    return elem;
}

int rightHigher(vector<int> v, int l)
{
    int p = v[l];
    int elem = 0;
    for (int i = l + 1; i < v.size(); i++)
    {
        if (v[i] > elem && v[i] >= p)
            elem = v[i];
    }
    return elem;
}

int findMaxProduct(vector<int> v)
{
    int mx = 0;
    for (int i = 1; i < v.size(); i++)
    {
        int left = leftLower(v, i);
        int right = rightHigher(v, i);
        mx = max(mx, left * v[i] * right);
    }
    return mx;
}
/*
public
static int[] findSubsequenceWithMaxProduct(int[] inputArray)
{
    int maxProduct = 0;
    int[] subsequenceWithLargestProduct = new int[3];
    for (int i = 1; i < inputArray.length - 1; i++)
    {
        int leftLowest = 0;
        int rightHighest = 0;
        // find lowest on the left.
        for (int j = 0; j < i; j++)
        {
            if (inputArray[j] < inputArray[i] && inputArray[j] > leftLowest)
            {
                leftLowest = inputArray[j];
            }
        }
        // find highest on right.
        for (int k = i + 1; k < inputArray.length; k++)
        {
            if (inputArray[k] > inputArray[i] && inputArray[k] > rightHighest)
            {
                rightHighest = inputArray[k];
            }
        }
        int currentProduct = inputArray[i] * leftLowest * rightHighest;
        if (currentProduct > maxProduct)
        {
            maxProduct = currentProduct;
            subsequenceWithLargestProduct = new int[]{leftLowest, inputArray[i], rightHighest};
        }
    }
    return subsequenceWithLargestProduct;
}
*/