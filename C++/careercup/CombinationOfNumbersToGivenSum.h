#include "../header.h"

/*
https://careercup.com/question?id=6321181669982208

Given a number N, write a program that returns all possible combinations of numbers that add up to N, as lists. (Exclude the N+0=N)

For example, if N=4 return {{1,1,1,1},{1,1,2},{2,2},{1,3}}

*/
class CombinationOfNumbersToGivenSum {
   public:
    static void test() {
        CombinationOfNumbersToGivenSum obj;
        auto res = obj.allCombinations2(4);
        for (auto& arr : res) cout << arr << endl;
    }

   private:
    vector<vector<int>> allCombinations(int N) {
        vector<vector<int>> result;
        allCombinations(N, {}, result);

        return result;
    }
    void allCombinations(int N, vector<int> cur, vector<vector<int>>& result) {
        if (N < 0) return;
        if (N == 0) {
            result.push_back(cur);
            return;
        }

        for (int i = 1; i <= N; i++) {
            cur.push_back(i);
            allCombinations(N - i, cur, result);
            cur.pop_back();
        }
    }

   private:
    vector<vector<int>> allCombinations2(int N) {
        vector<vector<int>> result;
        allCombinations2(N, 1, {}, result);

        return result;
    }

    void allCombinations2(int N, int i, vector<int> cur, vector<vector<int>>& result) {
        if (N == 0) {
            result.push_back(cur);
            return;
        }
        if (i >= N) return;

        allCombinations2(N, i + 1, cur, result);
        cur.push_back(i);
        allCombinations2(N - i, i, cur, result);
    }
};