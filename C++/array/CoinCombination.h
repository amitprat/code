#pragma once
#include "../Header.h"

class CoinCombination {
   public:
    static void test() {
        int arr[] = {10, 15, 20};
        int sum = 1000;

        auto res1 = generate1(arr, sum, 3);
        auto res2 = generate2(arr, sum, 3);

        // assert(isEqual(res1, res2));

        cout << res1 << endl;
    }

    static vector<int> generate1(int arr[], int sum, int n) {
        vector<int> ugly;
        unordered_set<int> s;
        s.insert(0);
        for (int i = 1; i <= sum; i++) {
            for (int j = 0; j < n; j++) {
                if (s.find(i - arr[j]) != s.end()) {
                    ugly.push_back(i);
                    s.insert(i);
                    break;
                }
            }
        }

        return ugly;
    }

    // mn=10
    static vector<int> generate2(int arr[], int sum, int n) {
        vector<int> ugly;
        ugly.push_back(1);
        int c1 = 0, c2 = 0, c3 = 0, mn = 1;

        while (mn < sum) {
            mn = min(ugly[c1] * arr[0], min(ugly[c2] * arr[1], ugly[c3] * arr[2]));
            ugly.push_back(mn);
            if (mn == ugly[c1] * arr[0]) c1++;
            if (mn == ugly[c2] * arr[1]) c2++;
            if (mn == ugly[c3] * arr[2]) c3++;
        }
        ugly.erase(ugly.begin());

        return ugly;
    }
};