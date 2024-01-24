#pragma once
#include "../Header.h"

/*
Coin change problem with finite number of coins available
denominations of coins = {1,2,3}
count of coins = ={1,1,3}
find the number of ways for getting change for S=6
*/
class CountWays {
public:
    static void test() {

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