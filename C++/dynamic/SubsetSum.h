#pragma once
#include "../Header.h"

class SubsetSum
{
public:
    static void test()
    {
        SubsetSum obj;
        vector<int> arr = { 6, 2, 5 };

        for (int sum = 1; sum <= 15; sum++) {
            cout << "Find sumbset with sum = " << sum << endl;
            cout << "--------------------------------------" << endl;
            auto res = obj.findSubsetSum(arr, sum);
            cout << "Subset with given sum " << sum << " = " << to_string(res) << endl;

            auto res1 = obj.findSubsetSumDP(arr, sum);
            cout << "Subset with sum " << sum << " = " << res1 << endl;

            auto res2 = obj.findSubsetSumDPMemoryOptimized(arr, sum);
            cout << "Subset with sum " << sum << " = " << res2 << endl;

            cout << "\n-----\n";
        }
    }

    vector<vector<int>> findSubsetSum(vector<int> arr, int sum)
    {
        vector<vector<int>> subsets;
        bool res = findSubsetSum(arr, arr.size(), sum, subsets, {});
        cout << "Subset with sum " << sum << " = " << res << endl;

        return subsets;
    }

    bool findSubsetSumDP(vector<int> arr, int sum)
    {
        int n = arr.size();
        vector<vector<bool>> memo(sum + 1, vector<bool>(n + 1));

        for (int s = 0; s <= sum; s++) {
            for (int i = 0; i <= n; i++) {
                if (s == 0) memo[s][i] = true;
                else if (i == 0) memo[s][i] = false;
                else {
                    memo[s][i] = memo[s][i - 1];
                    if (arr[i - 1] <= s) {
                        memo[s][i] = memo[s][i] || memo[s - arr[i - 1]][i - 1];
                    }
                }
            }
        }

        return memo[sum][n];
    }

    bool findSubsetSumDPMemoryOptimized(vector<int> arr, int sum)
    {
        int n = arr.size();
        vector<bool> memo(sum + 1, false);
        memo[0] = true;

        for (int i = 0; i < n; i++) {
            for (int s = sum; s >= arr[i]; s--) {
                memo[s] = memo[s] || memo[s - arr[i]];
            }
        }

        return memo[sum];
    }

private:
    bool findSubsetSum(vector<int> arr, int n, int sum, vector<vector<int>>& subsets, vector<int> curset)
    {
        if (sum == 0) {
            subsets.push_back(curset);
            return true;
        }
        if (n <= 0 || sum < 0) return false;

        bool cur1 = findSubsetSum(arr, n - 1, sum, subsets, curset);
        curset.push_back(arr[n - 1]);
        bool cur2 = findSubsetSum(arr, n - 1, sum - arr[n - 1], subsets, curset);
        curset.pop_back();

        return cur1 || cur2;
    }
};