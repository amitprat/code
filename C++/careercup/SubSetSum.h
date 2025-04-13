#include "../header.h"

class SubsetSum {
   public:
    static void test() {
        SubsetSum obj;
        vector<int> arr = {3, 34, 4, 12, 5, 2};

        int sum = 9;
        auto res = obj.isSubsetSumDP1DArray(arr, sum);
        if (res) cout << "Subset sum found" << endl;
    }

   private:
    bool isSubsetSumRecursive(vector<int>& arr, int sum) {
        return isSubsetSumRecursive(arr, sum, arr.size());
    }

    bool isSubsetSumRecursive(vector<int>& arr, int sum, int n) {
        if (sum == 0) return true;
        if (n <= 0) return false;

        return isSubsetSumRecursive(arr, sum - arr[n - 1], n - 1) || isSubsetSumRecursive(arr, sum, n - 1);
    }

   private:
    vector<vector<int>> findSubsetSumRecursive(vector<int> arr, int sum) {
        vector<vector<int>> subsets;
        bool res = findSubsetSumRecursive(arr, arr.size(), sum, subsets, {});
        cout << "Subset with sum " << sum << " = " << res << endl;

        return subsets;
    }

    bool findSubsetSumRecursive(vector<int> arr, int n, int sum, vector<vector<int>>& subsets, vector<int> curset) {
        if (sum == 0) {
            subsets.push_back(curset);
            return true;
        }
        if (n <= 0 || sum < 0) return false;

        bool cur1 = findSubsetSumRecursive(arr, n - 1, sum, subsets, curset);
        curset.push_back(arr[n - 1]);
        bool cur2 = findSubsetSumRecursive(arr, n - 1, sum - arr[n - 1], subsets, curset);
        curset.pop_back();

        return cur1 || cur2;
    }

   private:
    bool isSubsetSumMemoization(vector<int>& arr, int sum) {
        int n = arr.size();
        vector<vector<bool>> memo(sum + 1, vector<bool>(n + 1, -1));

        return isSubsetSumMemoization(arr, sum, arr.size(), memo);
    }

    bool isSubsetSumMemoization(vector<int>& arr, int sum, int n, vector<vector<bool>>& memo) {
        if (sum == 0) return true;
        if (n <= 0) return false;
        if (memo[sum][n] != -1) return memo[sum][n];

        memo[sum][n] = isSubsetSumMemoization(arr, sum - arr[n - 1], n - 1, memo) || isSubsetSumMemoization(arr, sum, n - 1, memo);

        return memo[sum][n];
    }

   private:
    bool isSubsetSumDP2DArray(vector<int>& arr, int sum) {
        int n = arr.size();
        vector<vector<int>> table(sum + 1, vector<int>(n + 1));
        table[0][0] = true;

        // if sum is zero
        for (int j = 1; j <= n; j++) table[0][j] = true;

        // if number is not zero but number of elements are zero.
        for (int i = 1; i <= sum; i++) table[i][0] = false;

        for (int s = 1; s <= sum; s++) {
            for (int i = 1; i <= n; i++) {
                table[s][i] = table[s][i - 1];                                 // by exluding the current element.
                if (arr[i - 1] <= s) table[s][i] |= table[s - arr[i - 1]][i-1];  // by including current element
            }
        }

        return table[sum][n];
    }

   private:
    bool isSubsetSumDP2DArray2(vector<int> arr, int sum) {
        int n = arr.size();
        vector<vector<bool>> memo(sum + 1, vector<bool>(n + 1));

        for (int s = 0; s <= sum; s++) {
            for (int i = 0; i <= n; i++) {
                if (s == 0)
                    memo[s][i] = true;
                else if (i == 0)
                    memo[s][i] = false;
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

   private:
    bool isSubsetSumDP1DArray(vector<int>& arr, int sum) {
        vector<bool> table(sum + 1, false);
        table[0] = true;  // sum is zero

        for (int i = 0; i < arr.size(); i++) {
            for (int s = arr[i]; s <= sum; s++) {
                table[s] = table[s] || table[s - arr[i]];
            }
        }

        return table[sum];
    }

   private:
    bool isSubsetSumDP1DArray(vector<int> arr, int sum) {
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
    bool isSubsetSumDP1DArray2(vector<int> arr, int sum) {
        int n = arr.size();
        vector<bool> memo(sum + 1, false);
        memo[0] = true;

        for (int s = sum; s > 0; s--) {
            for (int i = 0; i < arr.size(); i++) {
                if (s >= arr[i]) memo[s] = memo[s] || memo[s - arr[i]];
            }
        }

        return memo[sum];
    }
};