#include "../header.h"

class NumberOfWaysToReachNthStair {
   public:
    static void test() {
        NumberOfWaysToReachNthStair obj;

        for (int n = 0; n <= 10; n++) {
            int steps1 = obj.getNumWaysUsingRecursion(n);
            int steps2 = obj.getNumWaysUsingMemoization(n);
            int steps3 = obj.getNumWaysUsingMemoization1(n);
            int steps4 = obj.getNumWaysUsingConstantMemoization(n);

            assert(steps1 == steps2);
            assert(steps1 == steps3);
            assert(steps1 == steps4);

            cout << format("Number of ways to reach {}th stairs are {}.", n, steps1) << endl;
        }
    }

   private:
    int getNumWaysUsingRecursion(int n) {
        if (n < 0) return 0;
        if (n == 0) return 1;

        return getNumWaysUsingRecursion(n - 1) + getNumWaysUsingRecursion(n - 2) + getNumWaysUsingRecursion(n - 3);
    }

    int getNumWaysUsingMemoization(int n) {
        vector<int> memo(n + 1, 0);

        return getNumWaysUsingMemoization(n, memo);
    }

    int getNumWaysUsingMemoization(int n, vector<int>& memo) {
        if (n < 0) return 0;
        if (n == 0) return 1;
        if (memo[n] > 0) return memo[n];

        memo[n] = getNumWaysUsingMemoization(n - 1, memo) + getNumWaysUsingMemoization(n - 2, memo) + getNumWaysUsingMemoization(n - 3, memo);

        return memo[n];
    }

    int getNumWaysUsingMemoization1(int n) {
        if (n == 0 || n == 1) return 1;
        if (n == 2) return 2;

        vector<int> memo(n + 1, 0);
        memo[0] = 1;
        memo[1] = 1;
        memo[2] = 2;

        for (int i = 3; i <= n; i++) {
            memo[i] = memo[i - 1] + memo[i - 2] + memo[i - 3];
        }

        return memo[n];
    }

    int getNumWaysUsingConstantMemoization(int n) {
        int a = 1, b = 1, c = 2;
        if (n < 0) return 0;
        if (n == 0 || n == 1) return 1;
        if (n == 2) return 2;

        for (int i = 3; i <= n; i++) {
            int d = a + b + c;
            a = b;
            b = c;
            c = d;
        }

        return c;
    }
};