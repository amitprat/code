#include "../header.h"

/*
https://careercup.com/question?id=19286747

Given an array of integers. Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of two sub-array is maximum.
* The sub-arrays should not overlap.

eg- [2 -1 -2 1 -4 2 8] ans - (-1 -2 1 -4) (2 8), diff = 16

I gave him o(n^2) algorithm but he was not satisfied.
*/
class SplitSubArraysWithMaxDiffOfSum
{
public:
    static void test()
    {
        SplitSubArraysWithMaxDiffOfSum obj;
        vector<int> arr = {2, -1, -2, 1, -4, 2, 8};
        pair<vector<int>, vector<int>> result = obj.splitPartitalSubArray(arr);

        cout << "Input: " << arr << endl;
        int sum1 = std::accumulate(result.first.begin(), result.first.end(), 0);
        int sum2 = std::accumulate(result.second.begin(), result.second.end(), 0);
        cout << "First Array: " << result.first << ", " << sum1 << endl;
        cout << "Second Array: " << result.second << ", " << sum2 << endl;

        cout << "Max Diff: " << obj.diffPartitalSubArrayUsingDP(arr) << endl;
    }

private:
    // O(n) approach but it takes entire array on left and right
    pair<vector<int>, vector<int>> split(const vector<int> &arr)
    {
        pair<vector<int>, vector<int>> result;

        int firstArrSum = 0;
        int secondArrSum = std::accumulate(arr.begin(), arr.end(), 0);
        int curDiff = secondArrSum - firstArrSum;
        int breakPoint = -1;
        for (int i = 0; i < arr.size(); i++)
        {
            firstArrSum += arr[i];
            secondArrSum -= arr[i];

            if (secondArrSum - firstArrSum > curDiff)
            {
                curDiff = secondArrSum - firstArrSum;
                breakPoint = i;
            }
        }

        if (breakPoint == -1)
            result.second.insert(result.second.begin(), arr.begin(), arr.end());
        else
        {
            result.first.insert(result.first.begin(), arr.begin(), arr.begin() + breakPoint + 1);
            result.second.insert(result.second.begin(), arr.begin() + breakPoint + 1, arr.end());
        }

        return result;
    }

private:
    // consider partial subarray O(n2)
    pair<vector<int>, vector<int>> splitPartitalSubArray(const vector<int> &arr)
    {
        pair<vector<int>, vector<int>> result;

        pair<pair<int, int>, pair<int, int>> points;
        points.first = {-1, -1};
        points.second = {0, arr.size()};
        int rightSum = std::accumulate(arr.begin(), arr.end(), 0);
        int leftSum = 0;
        int mxDiff = rightSum - leftSum;
        for (int i = 0; i < arr.size(); i++)
        {
            pair<int, int> smallestSubArrayOnLeft = findSmallestSubArray(arr, 0, i, leftSum);
            pair<int, int> largestSubArrayOnRight = findLargestSubArray(arr, i + 1, arr.size(), rightSum);
            if (rightSum - leftSum > mxDiff)
            {
                mxDiff = rightSum - leftSum;

                points = {smallestSubArrayOnLeft, largestSubArrayOnRight};
            }
        }

        result.first = {arr.begin() + points.first.first, arr.begin() + points.first.second + 1};
        result.second = {arr.begin() + points.second.first, arr.begin() + points.second.second + 1};

        return result;
    }

    pair<int, int> findSmallestSubArray(const vector<int> &arr, int s, int e, int &leftSum)
    {
        leftSum = 0;
        int curStart = s;
        int curEnd = s;
        for (int i = s; i <= e; i++)
        {
            leftSum += arr[i];
            curEnd = i;
            if (leftSum > 0)
            {
                leftSum = 0;
                curStart = i + 1;
            }
        }

        if (curStart > curEnd)
            curStart = curEnd = -1;
        return {curStart, curEnd};
    }

    pair<int, int> findLargestSubArray(const vector<int> &arr, int s, int e, int &rightSum)
    {
        rightSum = 0;
        int curStart = s;
        int curEnd = s;
        for (int i = s; i < e; i++)
        {
            rightSum += arr[i];
            curEnd = i;
            if (rightSum < 0)
            {
                rightSum = 0;
                curStart = i + 1;
            }
        }

        if (curStart > curEnd)
            curStart = curEnd = -1;
        return {curStart, curEnd};
    }

private:
    // consider partial subarray O(n2)
    int diffPartitalSubArrayUsingDP(const vector<int> &arr)
    {
        pair<vector<int>, vector<int>> result;

        vector<int> smallestArrSumFromLeft, smallestArrSumFromRight;
        vector<int> largestArrSumFromLeft, largestArrSumFromRight;

        // smallest from left using kadane O(n)
        int curSum = 0;
        int s = 0, e = -1;
        for (int i = 0; i < arr.size(); i++)
        {
            curSum += arr[i];
            e = i;
            if (curSum > 0)
            {
                curSum = 0;
                s = i + 1;
            }
            smallestArrSumFromLeft.push_back(curSum);
        }

        // smallest from right using kadane O(n)
        smallestArrSumFromRight.resize(arr.size());
        curSum = 0;
        s = arr.size(), e = arr.size() - 1;
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            curSum += arr[i];
            s = i;
            if (curSum > 0)
            {
                curSum = 0;
                e = i - 1;
            }
            smallestArrSumFromRight[i] = curSum;
        }

        // largest from left using kadane O(n)
        curSum = 0;
        s = 0, e = -1;
        for (int i = 0; i < arr.size(); i++)
        {
            curSum += arr[i];
            e = i;
            if (curSum < 0)
            {
                curSum = 0;
                s = i + 1;
            }
            largestArrSumFromLeft.push_back(curSum);
        }

        // smallest from right using kadane O(n)
        curSum = 0;
        s = arr.size(), e = arr.size() - 1;
        largestArrSumFromRight.resize(arr.size());
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            curSum += arr[i];
            s = i;
            if (curSum < 0)
            {
                curSum = 0;
                e = i - 1;
            }
            largestArrSumFromRight[i] = curSum;
        }

        int mxDiff = 0;
        mxDiff = largestArrSumFromRight[0];
        for (int i = 1; i < arr.size(); i++)
        {
            mxDiff = max(mxDiff, largestArrSumFromRight[i] - smallestArrSumFromLeft[i - 1]);
        }

        mxDiff = max(mxDiff, largestArrSumFromLeft[arr.size() - 1]);
        for (int i = arr.size() - 2; i >= 0; i--)
        {
            mxDiff = max(mxDiff, largestArrSumFromLeft[i] - smallestArrSumFromRight[i + 1]);
        }

        return mxDiff;
    }
};