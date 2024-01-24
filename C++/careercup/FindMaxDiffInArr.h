#include "../Header.h"

/*
Given an array of integers. Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of two sub-array is maximum.
* The sub-arrays should not overlap.

eg- [2 -1 -2 1 -4 2 8] ans - (-1 -2 1 -4) (2 8), diff = 16

I gave him o(n^2) algorithm but he was not satisfied.
*/

/*
An O(n) solution is possible.

We consider all "split points", i.e. points such that one subarray lies to the left of it, and one to the right, and compute the best for each possible split point.

Dynamic programming works.

Given Array A[1,...n]

Using the standard dynamic programming algorithm, we can compute for a given i, the maximum and minimum sum subarrays in A[1...i] and A[i+1 ... n]. Note that the point between i and i+1 is a split point.

This can be done by making two passes once from 1 to n, and other from n to 1 and give us four arrays with the max and min sub-array sums.

Now given the above four arrays, for split point between i and i+1, we can take the max and min combinations (max from right, min from left and max from left, min from left), and get the combination which gives the better result.

Once we have the max for each split point, we get the global optimum.

O(n) time, O(n) space.
*/
int maxDiff(vector<int> v)
{
    int mnL[v.size()];
    int mxR[v.size()];
    int mxL[v.size()];
    int mnR[v.size()];

    int mxDiff = 0;
    for (int i = 0; i < v.size(); i++)
    {
        mnL[i] = mxL[i] = v[i];
        if (i > 0)
        {
            if (mnL[i - 1] + v[i] < v[i])
                mnL[i] = mnL[i - 1] + v[i];
            if (mxL[i - 1] + v[i] > v[i])
                mxL[i] = mxL[i - 1] + v[i];
        }
    }
    mnR[v.size() - 1] = 999;
    mxR[v.size() - 1] = -999;
    for (int i = v.size() - 2; i >= 0; i--)
    {
        mnR[i] = mxR[i] = v[i + 1];
        if (mnR[i + 1] + v[i + 1] < v[i + 1])
            mnR[i] = mnR[i + 1] + v[i + 1];
        if (mxR[i + 1] + v[i + 1] > v[i + 1])
            mxR[i] = mxR[i + 1] + v[i + 1];
    }

    /* Debug Only
    cout << "mnL = ";
    for (int i = 0; i < v.size(); i++)
        cout << setw(4) << mnL[i] << " ";
    cout << endl;

    cout << "mxR = ";
    for (int i = 0; i < v.size(); i++)
        cout << setw(4) << mxR[i] << " ";
    cout << endl;

    cout << "mxL = ";
    for (int i = 0; i < v.size(); i++)
        cout << setw(4) << mxL[i] << " ";
    cout << endl;

    cout << "mnR = ";
    for (int i = 0; i < v.size(); i++)
        cout << setw(4) << mnR[i] << " ";
    cout << endl;
    */

    // For finding maxDiff and left and right subarray
    int index = -1;
    bool mnLeft = false;
    for (int i = 0; i < v.size() - 1; i++)
    {
        if (mxR[i] - mnL[i] > mxDiff)
        {
            mnLeft = true;
            index = i;
            mxDiff = mxR[i] - mnL[i];
        }
        if (mxL[i] - mnR[i] > mxDiff)
        {
            mnLeft = false;
            index = i;
            mxDiff = mxL[i] - mnR[i];
        }
    }
    vector<int> left, right;
    int mnLeftVal = 999, mxRight = -999;
    int cur = 0;
    int lstart = index;
    int rend = index + 1;
    for (int i = index; i >= 0; i--)
    {
        cur += v[i];
        if (cur < mnLeftVal)
        {
            mnLeftVal = cur;
            lstart = i;
        }
    }
    for (int i = index + 1; i < v.size(); i++)
    {
        cur += v[i];
        if (cur > mxRight)
        {
            mxRight = cur;
            rend = i;
        }
    }
    for (int i = lstart; i <= index; i++)
        left.push_back(v[i]);
    for (int i = index + 1; i <= rend; i++)
        right.push_back(v[i]);

    cout << "Left = ";
    for (auto i : left)
        cout << i << " ";
    cout << endl;

    cout << "Right = ";
    for (auto i : right)
        cout << i << " ";
    cout << endl;

    return mxDiff;
}

int main()
{
    vector<int> a = {2, -1, -2, 1, -4, 2, 8};
    cout << "Max Diff = " << maxDiff(a) << endl;
    return 0;
}
