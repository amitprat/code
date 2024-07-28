#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5725584103571456

Given a number "n", find the least number of perfect square numbers sum needed to get "n"

Example:
n=12, return 3 (4 + 4 + 4) = (2^2 + 2^2 + 2^2) NOT (3^2 + 1 + 1 + 1)
n = 6, return 3 (4 + 1 + 1) = (2^2 + 1^2 + 1^2)
*/

class LeastNumberOfPerfectSquaresToReachN {
    struct PerfectSquare {
        int cnt = 0;
        vector<vector<int>> perfSquares;

        PerfectSquare() {}
        PerfectSquare(int cnt, int elem) : cnt(cnt) {
            perfSquares.push_back({});
            for (int i = 0; i < cnt; i++) perfSquares.back().push_back(elem);
        }

        bool operator<=(const PerfectSquare& other) {
            return this->cnt <= other.cnt;
        }

        void update(int cnt, vector<vector<int>> perfSq, int newPerfSq) {
            this->cnt = cnt;
            for (auto old : perfSq) {
                old.push_back(newPerfSq);
                old.push_back(newPerfSq);

                perfSquares.push_back(old);
            }
        }

        string to_string() {
            stringstream ss;
            ss << "Cnt: " << cnt << endl;
            for (auto e : perfSquares) {
                for (auto i : e) ss << i << " ";
                ss << endl;
            }

            return ss.str();
        }
    };

   public:
    static void test() {
        for (int i = 0; i <= 20; i++) {
            int res1 = leastNumberOfPerfectSquares1(i);
            int res2 = leastNumberOfPerfectSquares2(i);
            int res3 = leastNumberOfPerfectSquares3(i);
            int res4 = leastNumberOfPerfectSquaresRecursive(i);
            PerfectSquare res5 = leastNumberOfPerfectSquaresWithValues(i);
            assert(res1 == res2);
            assert(res1 == res3);
            assert(res1 == res4);
            assert(res1 == res5.cnt);

            cout << format("Least of perfect squares={} to reach to {}", res1, i) << endl;
            cout << res5.to_string() << endl;
        }
    }

   private:
    static int leastNumberOfPerfectSquaresRecursive(int n) {
        vector<int> memo(n + 1, -1);
        return leastNumberOfPerfectSquaresRecursive(n, memo);
    }

    static int leastNumberOfPerfectSquaresRecursive(int n, vector<int>& dp) {
        if (n < 0) return INT_MAX;
        if (n == 0) return 0;
        if (dp[n] != -1) return dp[n];

        int i = 1;
        int cur = INT_MAX;
        while (i * i <= n) {
            int val = leastNumberOfPerfectSquaresRecursive(n - i * i, dp);
            if (val != INT_MAX) cur = min(cur, val + 1);
            i++;
        }

        dp[n] = cur;

        return dp[n];
    }

   private:
    static int leastNumberOfPerfectSquares1(int n) {
        int* table = new int[n + 1];
        memset(table, 0, (n + 1) * sizeof(int));
        // for k = 1
        for (int i = 0; i <= n; i++) table[i] = i;

        // for k >= 2
        for (int k = 2; k * k <= n; k++) {
            int p = pow(k, 2);

            for (int j = p; j <= n; j++) {
                table[j] = min(table[j], table[j - p] + 1);
            }
        }

        return table[n];
    }

    static int leastNumberOfPerfectSquares2(int n) {
        int* table = new int[n + 1];
        int max = floor(sqrt(n));
        int squared;

        for (int i = 0; i <= n; i++) {
            table[i] = i;
        }
        for (int i = 2; i <= max; i++) {
            for (int j = 0; j <= n; j++) {
                squared = pow(i, 2);
                if (squared <= j)
                    table[j] = min(table[j], table[j - squared] + 1);
            }
        }
        return table[n];
    }

    static int leastNumberOfPerfectSquares3(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }

        return dp[n];
    }

   private:
    static PerfectSquare leastNumberOfPerfectSquaresWithValues(int n) {
        vector<PerfectSquare> perfectSquares(n + 1);

        // for k = 1
        for (int i = 0; i <= n; i++) perfectSquares[i] = PerfectSquare(i, 1);

        // for k >= 2
        for (int k = 2; k * k <= n; k++) {
            int p = pow(k, 2);

            for (int j = p; j <= n; j++) {
                if (perfectSquares[j - p].cnt + 1 < perfectSquares[j].cnt) {
                    perfectSquares[j].update(perfectSquares[j - p].cnt + 1, perfectSquares[j - p].perfSquares, k);
                }
            }
        }

        return perfectSquares[n];
    }
};