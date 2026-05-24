#pragma once
#include "../header.h"

class CombinationSum {
   public:
    static void test() {
        using Input = pair<vector<int>, int>;
        vector<Input> inputs = {
            {{2, 5, 6, 9}, 3},
            {{2, 5, 6, 9}, 6},
            {{2, 5, 6, 9}, 7},
            {{2, 5, 6, 9}, 8},
            {{2, 5, 6, 9}, 9},
            {{2, 5, 6, 9}, 11},
            {{2, 5, 6, 9}, 13},
            {{2, 5, 6, 9}, 17},
            {{3, 4, 5}, 16}};

        CombinationSum obj;
        for (auto& [input, target] : inputs) {
            auto res = obj.combinationSum(input, target);
            println("Target sum for input:[{}], target:[{}], combinations are:[{}]", input, target, res);
        }
    }

   public:
    // we can use the same element multiple times, so we don't move to next index after including current element
    vector<vector<int>> combinationSum(vector<int>& input, int target) {
        vector<vector<int>> result;

        int n = input.size();

        vector<int> cur;
        combinationSum(input, 0, n, target, cur, result);

        return result;
    }

    void combinationSum(vector<int>& input, int index, int n, int target, vector<int>& cur, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(cur);
            return;
        }
        if (index == n || target < 0) return;

        combinationSum(input, index + 1, n, target, cur, result);
        cur.push_back(input[index]);
        combinationSum(input, index, n, target - input[index], cur, result);
        cur.pop_back();
    }

   public:
    // similar to above but we can use the same element only once, so we move to next index after including current element
    // we can also sort the input and skip duplicates to avoid duplicate combinations in result
    vector<vector<int>> combinationSum2(vector<int>& input, int target) {
        int n = input.size();
        sort(input.begin(), input.end());

        vector<vector<int>> result;
        vector<int> cur;
        combinationSum2(input, 0, n, target, cur, result);
        return result;
    }

    void combinationSum2(vector<int>& input, int index, int n, int target, vector<int>& cur, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(cur);
            return;
        }
        if (index == n || target < 0) return;

        for (int i = index; i < n; i++) {
            if (i > index && input[i] == input[index]) continue;  // skip duplicates

            cur.push_back(input[i]);
            combinationSum2(input, i + 1, n, target - input[i], cur, result);
            cur.pop_back();
        }
    }
};