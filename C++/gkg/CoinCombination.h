#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=5729312817807360
https://www.careercup.com/question?id=5638939143045120

Given many coins of 3 different face values, print the combination sums of the coins up to 1000. Must be printed in order.
eg: coins(10, 15, 55)
print:
10
15
20
25
.
.
1000
*/

class CoinCombination {
   public:
    static void test() {
        CoinCombination obj;

        vector<int> amounts = {0, 10, 15, 17, 20, 50, 100, 1000};
        vector<int> coins = {10, 15, 20};
        for (auto amount : amounts) {
            auto res1 = generate_combination_sum_1(coins, amount);
            auto res3 = generate_combination_sum_recursive(coins, amount);

            assert(areEqual(res1, res3));

            cout << "Coins upto amount: " << amount << " are " << res1 << endl;
        }
    }

   private:
    static void printSums(int c1, int c2, int c3) {
        unordered_set<int> sums;
        sums.insert(0);

        for (int sum = 1; sum <= 1000; sum++) {
            if (sums.find(sum - c1) != sums.end() ||
                sums.find(sum - c2) != sums.end() ||
                sums.find(sum - c3) != sums.end()) {
                cout << sum << " ";
                sums.insert(sum);
            }
        }
    }

   private:
    static vector<int> generate_combination_sum_1(vector<int>& arr, int sum) {
        vector<int> result;

        unordered_set<int> set;
        set.insert(0);

        for (int s = 1; s <= sum; s++) {
            for (int i = 0; i < arr.size(); i++) {
                if (set.find(s - arr[i]) != set.end()) {
                    result.push_back(s);

                    set.insert(s);

                    break;
                }
            }
        }

        return result;
    }

   private:
    // This print multiples like ugly numbers
    static vector<int> generate_combination_sum_2(vector<int>& arr, int sum) {
        vector<int> result;
        result.push_back(1);
        int c1 = 0, c2 = 0, c3 = 0, mn = 1;

        while (mn < sum) {
            mn = min(result[c1] * arr[0], min(result[c2] * arr[1], result[c3] * arr[2]));
            if (mn <= sum) result.push_back(mn);

            if (mn == result[c1] * arr[0]) c1++;
            if (mn == result[c2] * arr[1]) c2++;
            if (mn == result[c3] * arr[2]) c3++;
        }

        result.erase(result.begin());  // remove 1

        return result;
    }

   private:
    static vector<int> generate_combination_sum_recursive(vector<int>& arr, int sum) {
        vector<int> result;
        for (int s = 1; s <= sum; s++) {
            if (generate_combination_sum_can_make_to_sum(arr, s)) {
                result.push_back(s);
            }
        }

        return result;
    }

    static bool generate_combination_sum_can_make_to_sum(vector<int>& arr, int sum) {
        if (sum < 0) return false;
        if (sum == 0) return true;

        for (auto coin : arr) {
            if (generate_combination_sum_can_make_to_sum(arr, sum - coin)) return true;
        }

        return false;
    }
};