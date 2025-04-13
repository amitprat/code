#include "../header.h"
/*
Coins: Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents), and
pennies (1 cent), write code to calculate the number of ways of representing n cents.
*/

class MakeChange {
    static void test() {
        vector<int> coins = {25, 10, 5, 1};
        int amount = 100;
        MakeChange obj;
        obj.numWaysToMakeChange(coins, amount);
    }

   public:
    int numWaysToMakeChange(vector<int>& coins, int amount) {
        return numWaysToMakeChange(coins, 0, amount);
    }

    int numWaysToMakeChange(vector<int>& coins, int idx, int amount) {
        if (amount == 0) return 1;
        if (idx >= coins.size()) return 0;

        int ways = 0;
        for (int i = 0; i * coins[idx] <= amount; i++) {
            ways += numWaysToMakeChange(coins, idx + 1, amount - i * coins[idx]);
        }

        return ways;
    }

   public:
    int numWaysToMakeChange2(vector<int>& coins, int amount) {
        return numWaysToMakeChange2(coins, amount, 0);
    }

    int numWaysToMakeChange2(vector<int>& coins, int amount, int idx) {
        if (amount == 0) return 1;
        if (idx >= coins.size()) return 0;

        return numWaysToMakeChange2(coins, amount, idx + 1) +
               numWaysToMakeChange2(coins, amount - coins[idx], idx);
    }
};