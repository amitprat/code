#include "../header.h"

class MaximumSumSubsequence {
   public:
    static void test() {
        MaximumSumSubsequence obj;
        vector<int> arr = {1, 2, 3, 4, 5, 6, 12, 3, 1, 7, 12, 3, 23, 1, 23, 12, 4, 21, 2, 23, 4, 21, 4, 21, 1, 4, 1, 21, 2};
        cout << "Max sum: " << obj.maxSumSubsequence(arr) << endl;
        cout << "Max sum: " << obj.maxSumSubsequenceRecursive(arr) << endl;
    }

   private:
    int maxSumSubsequence(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> table(n);
        table[0] = nums[0];
        table[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            table[i] = max(table[i - 1], nums[i] + table[i - 2]);
        }

        return table[n - 1];
    }

   private:
    int maxSumSubsequenceRecursive(vector<int>& nums) {
        return maxSumSubsequenceRecursive(nums, 0, nums.size(), 0);
    }

    int maxSumSubsequenceRecursive(vector<int>& nums, int idx, int sz, int cur) {
        if (idx == sz) return 0;
        if (idx == sz - 1) return nums[idx];
        if (idx == sz - 2) return max(nums[idx], nums[idx + 1]);

        return max(maxSumSubsequenceRecursive(nums, idx + 1, sz, cur),
                   nums[idx] + maxSumSubsequenceRecursive(nums, idx + 2, sz, cur));
    }
};