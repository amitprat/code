#include "../header.h"

class SubSetSum {
   public:
    static void test() {
        SubSetSum obj;
        vector<int> arr = {3, 34, 4, 12, 5, 2};
        int sum = 9;
        auto res = obj.isSubsetSum(arr, sum);
        if (res) cout << "Subset sum found" << endl;
    }

   private:
    bool isSubsetSum(vector<int>& arr, int sum) {
        return isSubsetSum(arr, sum, arr.size());
    }

    bool isSubsetSum(vector<int>& arr, int sum, int n) {
        if (sum == 0) return true;
        if (n <= 0) return false;

        return isSubsetSum(arr, sum - arr[n - 1], n - 1) || isSubsetSum(arr, sum, n - 1);
    }

   private:
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
        vector<vector<int>> memo(sum + 1, vector<int>(n + 1, -1));

        return isSubsetSum(arr, sum, arr.size(), memo);
    }

    bool isSubsetSum(vector<int>& arr, int sum, int n, vector<vector<bool>>& memo) {
        if (sum == 0) return true;
        if (n <= 0) return false;
        if (memo[sum][n] != -1) return memo[sum][n] ? true : false;

        memo[sum][n] = isSubsetSum(arr, sum - arr[n - 1], n - 1) || isSubsetSum(arr, sum, n - 1);

        return memo[sum][n];
    }

   private:
    bool isSubsetSumDP(vector<int>& arr, int sum) {
        int n = arr.size();
        vector<vector<int>> table(sum + 1, vector<int>(n + 1));
        table[0][0] = true;
        for (int j = 1; j <= n; j++) table[0][j] = true;
        for (int i = 1; i <= sum; i++) table[i][0] = false;

        for (int s = 1; s <= sum; s++) {
            for (int i = 1; i <= n; i++) {
                table[s][i] = table[s][i - 1];
                if (arr[i - 1] <= s) table[s][i] |= table[s - arr[i - 1]][i];
            }
        }

        return table[sum][n];
    }

   private:
    bool isSubsetSumDP1D(vector<int>& arr, int sum) {
        vector<bool> table(sum + 1, false);
        table[0] = true;

        for (int i = 0; i < arr.size(); i++) {
            for (int s = arr[i]; s <= sum; s++) {
                table[s] |= table[s - arr[i]];
            }
        }

        return table[sum];
    }
};