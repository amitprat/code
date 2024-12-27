#pragma once
#include "../header.h"

/*
Coin change problem with finite number of coins available
denominations of coins = {1,2,3}
count of coins = ={1,1,3}
find the number of ways for getting change for S=6
*/
class CountWays {
   public:
    static void test() {
        vector<int> coins = {1, 2, 3};
        vector<int> count = {1, 1, 3};

        CountWays obj;

        for (int amount = 1; amount <= 10; amount++) {
            int ways1 = obj.countWays(coins, count, amount);
            int ways2 = obj.countWaysDP(coins, count, amount);
            assert(ways1 == ways2);
            println("Number of ways={0} to make change={1}", ways1, amount);
        }
    }

    int countWays(vector<int>& coins, vector<int>& count, int amount) {
        return countWays(coins, count, 0, amount);
    }

    int countWays(vector<int>& coins, vector<int>& count, int pos, int amount) {
        if (amount == 0) return 1;
        if (pos >= coins.size() || count[pos] < 0) return 0;

        int cnt = countWays(coins, count, pos + 1, amount);
        count[pos] -= 1;
        cnt += countWays(coins, count, pos, amount - coins[pos]);
        count[pos] += 1;

        return cnt;
    }

   private:
    int countWaysDP(vector<int>& coins, vector<int>& count, int amount) {
        int n = coins.size();
        vector<vector<int>> table(amount + 1, vector<int>(n + 1, 0));
        table[0][0] = 1;

        for (int s = 1; s <= amount; s++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= count[j - 1]; k++) {
                    table[s][j] = table[s][j - 1];
                    if (s >= k * coins[j - 1]) {
                        table[s][j] += table[s - k * coins[j - 1]][j - 1];
                    }
                }
            }
        }

        int total = 0;
        for (int i = 0; i < n; i++) total += table[amount][i];

        return total;
    }
};

/*
public static void main(String[] args) throws java.lang.Exception {
    int[] coins = { 1, 2, 3 };
    int[] count = { 1, 1, 3 };
    int sum = 9;
    int n = countWays(coins, count, sum);
    System.out.println(n);
}

public static int countWays(int[] coins, int[] count, int sum) {
    int n = coins.length;
    int[][] dp = new int[sum + 1][n + 1];

    int ret = 0;
    for (int i = 1; i <= sum; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= count[j - 1]; k++) {
                if (i > coins[j - 1] * k)
                    dp[i][j] += dp[i - coins[j - 1] * k][j - 1];

                if (i == coins[j - 1] * k)
                    dp[i][j] += 1;

            }
        }
    }
    for (int i = 0; i <= n; i++) {
        ret += dp[sum][i];
    }
    return ret;
}
*/