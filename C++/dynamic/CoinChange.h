#pragma once
#include "../header.h"

class CoinChange {
   public:
    static void test() {
        CoinChange obj;

        vector<pair<vector<int>, int>> v = {
            {{1, 2, 5, 10}, 3},
            {{1, 2, 5, 10}, 100},
            {{2, 5, 10}, 1},
            {{1, 2, 5, 10}, 0},
            {{1, 5, 6, 9}, 11},
            {{1, 2, 5}, 5},
            {{1, 2, 5, 10}, 6}};

        for (auto arr : v) {
            cout << "Coins: " << arr.first << ", amount: " << arr.second << endl;

            int minCoins1 = obj.minCoinChangeRecursive(arr.first, arr.first.size(), arr.second);
            // int minCoins2 = obj.minCoinChangeRecursive2(arr.first, arr.first.size(), arr.second);
            int minCoins3 = obj.minCoinChangeDP1(arr.first, arr.first.size(), arr.second);
            int minCoins4 = obj.minCoinChangeDP2(arr.first, arr.first.size(), arr.second);

            // greedy doesn't always give correct answer. for example: Coins: [1, 5, 6, 9], amount: 11
            // greedy gives [9, 1, 1] but correct answer is [5,6]
            int minCoins5 = obj.minCoinChangeGreedy(arr.first, arr.first.size(), arr.second);

            // assert(minCoins1 == minCoins2);
            assert(minCoins1 == minCoins3);
            assert(minCoins1 == minCoins4);
            // assert(minCoins1 == minCoins5);
            cout << "Minimum number of ways to make change = " << minCoins1 << endl;

            int numWays1 = obj.numWaysToMakeChangeRecursive(arr.first, arr.first.size(), arr.second);
            int numWays2 = obj.numWaysToMakeChangeRecursive2(arr.first, arr.first.size(), arr.second);
            int numWays3 = obj.numWaysRecursive3WithMemoization(arr.first, arr.first.size(), arr.second);
            int numWays4 = obj.numWaysToMakeChangeMemoization(arr.first, arr.first.size(), arr.second);
            int numWays5 = obj.numWaysToMakeChangeDP1DTable(arr.first, arr.first.size(), arr.second);
            int numWays6 = obj.numWaysToMakeChangeDP2DTable(arr.first, arr.first.size(), arr.second);

            assert(numWays1 == numWays2);
            assert(numWays1 == numWays3);
            assert(numWays1 == numWays4);
            assert(numWays1 == numWays5);
            assert(numWays1 == numWays6);
            cout << "Number of ways to make change = " << numWays1 << endl;

            cout << endl;
        }
    }

    // Minimum number of coins required to make change
   private:
    int minCoinChangeRecursive(vector<int> denom, int length, int amount) {
        if (amount == 0) return 0;
        if (amount < 0 || length <= 0) return INT_MAX;

        int including = minCoinChangeRecursive(denom, length, amount - denom[length - 1]);  // denom can be used multiple times.
        int excluding = minCoinChangeRecursive(denom, length - 1, amount);
        if (including != INT_MAX) including += 1;

        return min(including, excluding);
    }

   private:
    // this is taking too long
    int minCoinChangeRecursive2(vector<int>& denom, int length, int amount) {
        if (amount == 0) return 0;
        if (amount < 0 || length <= 0) return INT_MAX;

        // iteratve over each element of array recursively by including/excluding element and keep updating minimum coins.
        int mn = INT_MAX;
        for (int i = 0; i < length; i++) {
            int tmp = minCoinChangeRecursive2(denom, length, amount - denom[i]);
            if (tmp != INT_MAX && tmp + 1 < mn)
                mn = tmp + 1;
        }
        return mn;
    }

   private:
    int minCoinChangeDP1(vector<int> denom, int length, int amount) {
        int* table = new int[amount + 1];
        table[0] = 0;

        for (int am = 1; am <= amount; am++) {
            table[am] = INT_MAX;
            for (int d = 0; d < length; d++) {
                if (denom[d] <= am && table[am - denom[d]] != INT_MAX) {
                    table[am] = min(table[am], 1 + table[am - denom[d]]);
                }
            }
        }

        return table[amount];
    }

   private:
    int minCoinChangeDP2(vector<int> denom, int length, int amount) {
        vector<int> table(amount + 1, INT_MAX);
        table[0] = 0;  // we can always make 0 sum.

        for (auto& coin : denom) {
            for (int j = coin; j <= amount; j++) {
                table[j] = min(table[j], table[j - coin] == INT_MAX ? INT_MAX : 1 + table[j - coin]);
            }
        }

        return table[amount];
    }

   private:
    int minCoinChangeGreedy(vector<int> denom, int length, int amount) {
        if (amount == 0) return 0;

        int result = 0;
        vector<int> result_coins;  // this is just for printing purpose.

        // this is assuming that coins are in non-decreasing order.
        for (int i = length - 1; i >= 0;) {
            if (denom[i] <= amount) {
                amount -= denom[i];
                result_coins.push_back(denom[i]);
                result++;
            } else {
                i--;
            }
        }

        // for (auto coin : result_coins) cout << coin << " ";
        // cout << endl;

        return result == 0 ? INT_MAX : result;  // if there is no such combination possible, return INT_MAX
    }

    // Number of ways to make change
   private:
    int numWaysToMakeChangeRecursive(vector<int> denom, int length, int amount) {
        if (amount == 0) return 1;
        if (length == 0 || amount < 0) return 0;

        int including = numWaysToMakeChangeRecursive(denom, length, amount - denom[length - 1]);
        int excluding = numWaysToMakeChangeRecursive(denom, length - 1, amount);

        return including + excluding;
    }

   private:
    int numWaysToMakeChangeRecursive2(vector<int> denom, int length, int amount) {
        return numWaysToMakeChangeRecursive2(denom, 0, length, amount);
    }

    int numWaysToMakeChangeRecursive2(vector<int> denom, int pos, int length, int amount) {
        if (amount == 0) return 1;
        if (pos == length) return 0;

        // try including coin at position 'pos' (from 0 - x times where x is such that x*coins[pos] <= amount)
        int ways = 0;
        for (int i = 0; i * denom[pos] <= amount; i++) {
            ways += numWaysToMakeChangeRecursive2(denom, pos + 1, length, amount - i * denom[pos]);
        }

        return ways;
    }

   private:
    int numWaysRecursive3WithMemoization(vector<int> denom, int length, int amount) {
        vector<vector<int>> memo(amount + 1, vector<int>(length, 0));
        return numWaysRecursive3WithMemoization(denom, 0, length, amount, memo);
    }

    int numWaysRecursive3WithMemoization(vector<int> denom, int pos, int length, int amount, vector<vector<int>>& memo) {
        if (amount == 0) return 1;
        if (pos == length) return 0;

        if (memo[amount][pos]) return memo[amount][pos];

        int ways = 0;
        for (int i = 0; i * denom[pos] <= amount; i++) {
            ways += numWaysRecursive3WithMemoization(denom, pos + 1, length, amount - i * denom[pos], memo);
        }

        memo[amount][pos] = ways;

        return memo[amount][pos];
    }

   private:
    int numWaysToMakeChangeMemoization(vector<int> denom, int length, int amount) {
        vector<vector<int>> memo(amount + 1, vector<int>(length + 1, 0));

        return numWaysToMakeChangeMemoization(denom, length, amount, memo);
    }

    int numWaysToMakeChangeMemoization(vector<int> denom, int length, int amount, vector<vector<int>>& memo) {
        if (amount == 0) return 1;
        if (amount < 0 || length == 0) return 0;

        if (memo[amount][length]) return memo[amount][length];

        memo[amount][length] = numWaysToMakeChangeMemoization(denom, length - 1, amount, memo) + numWaysToMakeChangeMemoization(denom, length, amount - denom[length - 1], memo);

        return memo[amount][length];
    }

   private:
    int numWaysToMakeChangeDP1DTable(vector<int> denom, int length, int amount) {
        int* table = new int[amount + 1];
        for (int i = 1; i <= amount; i++) table[i] = 0;
        table[0] = 1;

        for (int i = 0; i < length; i++)
            for (int j = denom[i]; j <= amount; j++)
                table[j] += table[j - denom[i]];

        return table[amount];
    }

   private:
    int numWaysToMakeChangeDP2DTable(vector<int>& coins, int n, int amount) {
        vector<vector<int>> table(amount + 1, vector<int>(n + 1, 0));

        for (int i = 0; i <= amount; i++) table[i][0] = 0;  // if no coins, then 0 ways to make change
        for (int j = 0; j <= n; j++) table[0][j] = 1;       // if 0 amount, then always 1 way to make change

        for (int am = 1; am <= amount; am++) {
            for (int i = 1; i <= n; i++) {
                table[am][i] = table[am][i - 1];

                if (coins[i - 1] <= am) table[am][i] += table[am - coins[i - 1]][i];
            }
        }

        return table[amount][n];
    }
};