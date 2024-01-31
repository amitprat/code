#include "../header.h"

/*
https://www.careercup.com/question?id=5164935710507008

Given a list of coin values, and quantity of each type of coin. Write a
program to return the set of all possible sums which can be made using those
coins.
ex. coins = [10, 50, 100, 500]
quantity = [5, 3, 2, 2]
sum could be 400 , 300 ,200 , 100
*/
class CoinsToGivenSum {
    static void test() {
        CoinsToGivenSum obj;
        vector<int> coins = {10, 50, 100, 500};
        vector<int> quantity = {5, 3, 2, 2};
        int sum = 400;

        vector<vector<string>> sums;
        obj.possibleSums(coins, quantity, coins.size(), sum, sums, {});
        cout << sum << endl;
    }

   public:
    void possibleSums(vector<int>& coins, vector<int>& quantity, int n, int sum, vector<vector<string>>& sums, vector<string> cur) {
        if (sum == 0) {
            sums.push_back(cur);
            return;
        }
        if (n == 0) return;

        for (int q = 0; q < quantity[n - 1]; q++) {
            int cur_val = coins[n - 1] * q;
            stringstream ss;
            ss << "[";
            ss << coins[n - 1];
            ss << "*";
            ss << q;
            ss << "]";
            cur.push_back(ss.str());
            possibleSums(coins, quantity, n - 1, sum - cur_val, sums, cur);
        }
    }
};