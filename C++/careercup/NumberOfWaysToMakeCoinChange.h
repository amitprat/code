#include "../header.h"

class NumberOfWaysToMakeCoinChange {
   public:
    static void test() {
        NumberOfWaysToMakeCoinChange obj;
        vector<int> coins = {1, 2, 5};
        auto amount = 5;
        auto res = obj.numWaysRecursive(coins, coins.size(), amount);
    }

   private:
    int numWaysRecursive(int coins[], int n, int amount) {
        if (amount == 0) return 1;
        if (n == 0) return 0;

        return numWaysRecursive(coins, n - 1, amount) + numWaysRecursive(coins, n, amount - coins[n - 1]);
    }

   private:
    int numWaysUsingMemo(int coins[], int n, int amount) {
        vector<vector<int>> memo(amount, vector<int>(n));
    }
    int numWaysUsingMemo(int coins[], int n, int amount, vector<vector<int>>& memo) {
        if (amount == 0) return 1;
        if (n == 0) return 0;
        if (memo[amount][n]) return memo[amount][n];
        memo[amount][n] = numWays1(coins, n - 1, amount) + numWays1(coins, n, amount - coins[n - 1]);

        return memo[amount][n];
    }

   private:
    int numWaysRecursive2(int coins[], int pos, int n, int amount) {
        if (amount == 0) return 1;
        if (pos == n) return 0;

        int ways = 0;
        for (int i = 0; i * coins[pos] <= amount; i++) {
            ways += numWaysRecursive2(coins, pos + 1, n, amount - i * coins[pos]);
        }

        return ways;
    }

   private:
    int numWays2Memo(int coins[], int pos, int n, int amount, vector<vector<int>>& memo) {
        vector<vector<int>> memo(amount, vector<int>(n, 0));
        return numWays2Memo(coins, 0, n, amount, memo);
    }
    int numWays2Memo(int coins[], int pos, int n, int amount, vector<vector<int>>& memo) {
        if (amount == 0) return 1;
        if (pos == n) return 0;
        if (memo[amount][pos]) return memo[amount][pos];

        int ways = 0;
        for (int i = 0; i * coins[pos] <= amount; i++) {
            ways += numWays2Memo(coins, pos + 1, n, amount - i * coins[pos]);
        }
        memo[amount][pos] = ways;
        return memo[amount][pos];
    }

   private:
    int numWaysDynamic2DMatrix(int coins[], int n, int amount) {
        vector<vector<int>> table(amount + 1, vector<int>(n, 0));
        for (int i = 0; i <= amount; i++) table[i][0] = 0;  // if no coins, then 0 ways to make change
        for (int j = 0; j < n; j++) table[0][j] = 1;        // if 0 amount, then always 1 way to make change

        for (int am = 1; am <= amount; am++) {
            for (int i = 0; i < n && coins[i] <= am; i++) {
                table[am][i] = table[am][i - 1] + table[am - coins[i]][i];
            }
        }

        return table[amount];
    }

   private:
    int numWaysDynamic1DArray(int coins[], int n, int amount) {
        vector<int> table(amount + 1, 0);
        table[0] = 1;  // always 1 way to make change for 0 amount

        for (int i = 0; i < n; i++) {  // consider each coin
            for (int am = couns[i]; am <= amount; i++) {
                table[am] += table[am - coins[i]];
            }
        }

        return table[amount];
    }
};