#include "../header.h"

class TugOfWar {
   public:
    static void test() {
        TugOfWar solver;

        vector<vector<int>> testCases = {
            {23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4},  // odd length, one more in one group
            {1, 2, 3, 4},                                  // simple case
            {10, 20, 15, 5, 25, 30},                       // even length
            {100, -100, 50, -50, 0, 1, -1},                // balanced but needs care
            {7, 3, 2, 1, 5, 6},                            // close sum candidates
        };

        for (const auto& arr : testCases) {
            solver.solve(arr);
            cout << "\n";
        }
    }

   private:
    void solve(const vector<int>& arr) {
        const int n = arr.size();
        const int totalSum = accumulate(arr.begin(), arr.end(), 0);
        const int groupSize = n / 2;

        vector<int> bestA, bestB;
        vector<int> groupA, groupB;
        int minDiff = INT_MAX;

        dfs(arr, 0, 0, groupSize, totalSum, groupA, groupB, bestA, bestB, minDiff);

        cout << "Input: " << arr << "\n";
        cout << "Group A: " << bestA << "\n";
        cout << "Group B: " << bestB << "\n";
        cout << "Min sum diff: " << abs(accumulate(bestA.begin(), bestA.end(), 0) - accumulate(bestB.begin(), bestB.end(), 0)) << "\n";
    }

    void dfs(const vector<int>& arr, int index, int sumA, int maxA,
             int totalSum,
             vector<int>& groupA, vector<int>& groupB,
             vector<int>& bestA, vector<int>& bestB,
             int& minDiff) {
        if (index == arr.size()) {
            if (groupA.size() == maxA) {
                int diff = abs(totalSum - 2 * sumA);
                if (diff < minDiff) {
                    minDiff = diff;
                    bestA = groupA;
                    bestB = groupB;
                }
            }
            return;
        }

        if (groupA.size() < maxA) {
            groupA.push_back(arr[index]);
            dfs(arr, index + 1, sumA + arr[index], maxA, totalSum, groupA, groupB, bestA, bestB, minDiff);
            groupA.pop_back();
        }

        groupB.push_back(arr[index]);
        dfs(arr, index + 1, sumA, maxA, totalSum, groupA, groupB, bestA, bestB, minDiff);
        groupB.pop_back();
    }
};