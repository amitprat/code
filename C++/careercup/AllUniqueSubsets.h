#pragma once
#include "../header.h"

class AllUniqueSubsets {
   public:
    static void test() {
        AllUniqueSubsets obj;

        vector<vector<int>> inputs = {
            {},
            {1},
            {1, 2},
            {1, 1},
            {1, 2, 1},
            {1, 2, 3}};

        for (auto& input : inputs) {
            auto res = obj.subsetsWithDuplicates(input);
            println("All subsets of [{}], are: [{}]", input, res);
        }
    }

   public:
    vector<vector<int>> subsets1(vector<int>& input) {
        vector<vector<int>> result;

        int n = input.size();
        int sz = 1 << n;

        for (int i = 0; i < sz; i++) {
            vector<int> cur;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) cur.push_back(input[j]);
            }
            result.push_back(cur);
        }

        return result;
    }

   public:
    vector<vector<int>> subsets2(vector<int>& input) {
        vector<vector<int>> result;

        int n = input.size();
        vector<int> cur;
        subsets2(input, 0, n, cur, result);

        return result;
    }

    void subsets2(vector<int>& input, int i, int n, vector<int>& cur, vector<vector<int>>& result) {
        if (i == n) {
            result.push_back(cur);
            return;
        }

        subsets2(input, i + 1, n, cur, result);
        cur.push_back(input[i]);
        subsets2(input, i + 1, n, cur, result);
        cur.pop_back();
    }

   public:
    vector<vector<int>> subsetsWithDuplicates(vector<int>& input) {
        vector<vector<int>> result;

        int n = input.size();
        vector<int> cur;
        sort(input.begin(), input.end());
        subsetsWithDuplicates(input, 0, n, cur, result);

        return result;
    }

    void subsetsWithDuplicates(vector<int>& input, int i, int n, vector<int>& cur, vector<vector<int>>& result) {
        result.push_back(cur);

        for (int j = i; j < n; j++) {
            if (j > i && input[j] == input[j - 1]) continue;

            cur.push_back(input[j]);
            subsetsWithDuplicates(input, j + 1, n, cur, result);
            cur.pop_back();
        }
    }
};