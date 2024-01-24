#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=295694

Given an array of integers(both positive and negative) divide the array into two parts(sub-arrays) such that the difference between the sum of elements in each array is minimum????
*/
class DivideArrayInto2PartsWithMinimumDifference
{
public:
    static void test() {
        vector<int> arr = { 1, -2, 3, 4,5,6 };
        int sum = accumulate(arr.begin(), arr.end(), 0);
        
        vector<int> secondArrIndex;
        int diff = INT_MAX;
        balancedPartitionRecursion(arr, 0, arr.size(), 0, sum, {}, secondArrIndex, diff);

        for (int i = 0; i < secondArrIndex.size(); i++) cout << arr[secondArrIndex[i]] << " ";
        cout << endl;
        cout << "Min diff: " << diff << endl;

        int res = balancedPartitionDP(arr, sum);
        cout << "Min diff: " << res << endl;

        cout << "Min diff: " << findMinSumDiffRecursion(arr, 0, arr.size(), 0, sum) << endl;
    }

    static void balancedPartitionRecursion(vector<int>& arr, int index, int n, int curSum, int totalSum, vector<int> curResult, vector<int>& result, int& diff)
    {
        if (index == n) {
            int curDiff = totalSum - 2*curSum;
            if (abs(curDiff) < diff) {
                diff = abs(curDiff);
                result = curResult;
            }
            return;
        }
        if (index >= n) return;

        balancedPartitionRecursion(arr, index + 1, n, curSum, totalSum, curResult, result, diff);

        curResult.push_back(index);
        balancedPartitionRecursion(arr, index + 1, n, curSum + arr[index], totalSum, curResult, result, diff);
        curResult.pop_back();
    }

    static int findMinSumDiffRecursion(vector<int>& arr, int index, int n, int curSum, int totalSum)
    {
        if (index == n) return abs(totalSum - 2*curSum);
        if (index >= n) return INT_MAX;

        return min(findMinSumDiffRecursion(arr, index + 1, n, curSum, totalSum),
                   findMinSumDiffRecursion(arr, index + 1, n, curSum + arr[index], totalSum));
    }

    static int balancedPartitionDP(vector<int>& arr, int sum)
    {
        int n = arr.size();
        int mxSum = sum;

        // calculate mxsum for negative values
        for (auto u : arr) if (u < 0) mxSum = max(mxSum, sum - u);
        vector<vector<bool>> memo(mxSum + 1, vector<bool>(n + 1, false));

        for (int s = 0; s <= sum; s++) {
            for (int i = 0; i <= n; i++) {
                if (s == 0) memo[s][i] = true;
                else if (i == 0) memo[s][i] = false;
                else {
                    memo[s][i] = memo[s][i - 1];
                    if (arr[i - 1] <= s) memo[s][i] = memo[s][i] || memo[s - arr[i - 1]][i - 1];
                }
            }
        }

        for (int s = sum / 2; s >= 0; s--) {
            if (memo[s][n]) {
                return sum - 2 * s;
            }
        }

        return INT_MAX;
    }
};