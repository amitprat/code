#pragma once
#include "../Header.h"

class OptimalStrategyForGame {
public:
    static void test() {
        {
            vector<int> arr = { 8, 15, 3, 7 };
            auto res = optimalStrategyOfGame(arr);
            cout << format("Max coins earned={}", res) << endl;
        }

        {
            vector<int> arr = { 2, 2, 2, 2 };
            auto res = optimalStrategyOfGame(arr);
            cout << format("Max coins earned={}", res) << endl;
        }

        {
            vector<int> arr = { 20, 30, 2, 2, 2, 10 };
            auto res = optimalStrategyOfGame(arr);
            cout << format("Max coins earned={}", res) << endl;
        }
    }

    static int optimalStrategyOfGame(vector<int>& arr) {
        return optimalStrategyOfGameRec(arr);
    }

    static int optimalStrategyOfGameRec(vector<int>& arr) {
        int sum = 0;
        sum = accumulate(arr.begin(), arr.end(), sum);
        return optimalStrategyOfGameRec(arr, 0, arr.size() - 1, sum);
    }

    static int optimalStrategyOfGameRec(vector<int>& arr, int l, int r, int sum) {
        if (r == l + 1)
            return max(arr[l], arr[r]);

        return max((sum - optimalStrategyOfGameRec(arr, l + 1, r, sum - arr[l])),
            (sum - optimalStrategyOfGameRec(arr, l, r - 1, sum - arr[r])));
    }

    static int optimalStrategyOfGameMemo(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        int sum = accumulate(arr.begin(), arr.end(), 0);

        return optimalStrategyOfGameMemo(arr, 0, n - 1, sum, memo);
    }

    static int optimalStrategyOfGameMemo(vector<int>& arr, int l, int r, int sum, vector<vector<int>>& memo) {
        if (l + 1 == r) return max(arr[l], arr[r]);
        if (memo[l][r] != -1) return memo[l][r];

        memo[l][r] = max(
            (sum - optimalStrategyOfGameMemo(arr, l + 1, r, sum - arr[l], memo)),
            (sum - optimalStrategyOfGameMemo(arr, l, r - 1, sum - arr[r], memo))
        );

        return memo[l][r];
    }
};