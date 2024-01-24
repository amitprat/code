#pragma once
#include "../header.h"

class CandyProblem {
public:
    static void test() {
        CandyProblem obj;
        int N = 7;
        vector<int> rating = { 2,1,5,6,2,3,2 };
        cout << obj.minCadies(N, rating) << endl;
    }

    int minCadies(int N, vector<int>& rating) {
        if (N == 0) return 0;
        vector<int> candies(rating.size());
        candies[0] = 1;
        for (int i = 1; i < N; i++) {
            if (rating[i] > rating[i - 1]) candies[i] = candies[i - 1] + 1;
            else candies[i] = 1;
        }
        int result = candies[N - 1];
        for (int i = N - 2; i >= 0; i--) {
            int cur = 1;
            if (rating[i] > rating[i + 1]) cur = candies[i + 1] + 1;
            result += max(cur, candies[i]);
            candies[i] = cur;
        }

        return result;
    }
};