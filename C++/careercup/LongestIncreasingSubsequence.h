#include "../header.h"

class LongestIncreasingSubsequence {
   public:
    static void test() {
        LongestIncreasingSubsequence obj;

        vector<vector<int>> arrs = {
            {10, 22, 9, 33, 21, 50, 41, 60},
            {22, 9, 33, 21, 50, 41, 60},
            {9, 33, 21, 50, 41, 60},
            {33, 21, 50, 41, 60},
            {21, 50, 41, 60},
            {50, 41, 60},
            {41, 60},
            {60}};
        for (auto& arr : arrs) {
            int res1 = obj.longestUsingRecursion(arr);
            int res2 = obj.longestUsingDP(arr);

            assert(res1 == res2);
            cout << "Longest increasing subsequence: " << res1 << endl;
        }
    }

   private:
    int longestUsingRecursion(vector<int>& arr) {
        return longestUsingRecursion(arr, INT_MIN, 0, arr.size());
    }

    int longestUsingRecursion(vector<int>& arr, int mn, int l, int n) {
        if (l == n) return 0;

        int l1 = 0;
        if (arr[l] > mn) l1 = 1 + longestUsingRecursion(arr, arr[l], l + 1, n);
        int l2 = longestUsingRecursion(arr, mn, l + 1, n);

        return max(l1, l2);
    }

   private:
    int longestUsingDP(vector<int>& arr) {
        int n = arr.size();
        vector<int> table(n, 0);
        table[0] = 1;

        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (arr[i] > arr[j])
                    table[i] = max(table[i], table[j] + 1);
                else
                    table[i] = 1;
            }
        }

        return table[n - 1];
    }
};