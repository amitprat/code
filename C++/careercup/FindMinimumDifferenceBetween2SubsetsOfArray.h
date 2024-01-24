#include "../header.h"

class FindMinimumDifferenceBetween2SubsetsOfArray {
   public:
    static void test() {
        FindMinimumDifferenceBetween2SubsetsOfArray obj;
        vector<int> arr = {1, 6, 11, 5};
        auto diff1 = obj.minDiff(arr);
        auto diff2 = obj.minDiffUsingDP(arr);

        assert(diff1 == diff2);

        cout << "Min diff: " << diff1 << endl;
    }

   private:
    int minDiff(vector<int>& arr) {
        int n = arr.size();
        int sum = accumulate(arr.begin(), arr.end(), 0);
        int targetSum = sum / 2;

        int mnDiff = INT_MAX;
        minDiff(arr, n, targetSum, mnDiff);

        return max(mnDiff, sum - 2 * targetSum);
    }

    void minDiff(vector<int>& arr, int n, int curDiff, int& mnDiff) {
        if (n < 0 || curDiff < 0) return;
        mnDiff = min(mnDiff, curDiff);

        minDiff(arr, n - 1, curDiff, mnDiff);
        minDiff(arr, n - 1, curDiff - arr[n - 1], mnDiff);
    }

   private:
    int minDiffUsingDP(vector<int>& arr) {
        int n = arr.size();
        int sum = accumulate(arr.begin(), arr.end(), 0);

        int targetSum = sum / 2;

        vector<bool> table(targetSum + 1);
        table[0] = true;

        for (int i = 0; i < n; i++) {
            for (int s = targetSum; s >= arr[i]; s--) {
                table[s] = table[s] || table[s - arr[i]];
            }
        }

        for (int s = targetSum; s >= 0; s--) {
            if (table[s]) return max(targetSum - s, sum - 2 * targetSum);
        }

        return INT_MAX;
    }
};