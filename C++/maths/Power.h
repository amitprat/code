#pragma once
#include "../header.h"

class Power {
   public:
    static void test() {
        int a = 2;
        for (int b = -10; b < 0; b++)
            cout << "fpow( " << a << ", " << b << ") = " << fpow(a, b) << endl;

        for (int b = 0; b <= 10; b++)
            cout << "pow( " << a << ", " << b << ") = " << pow(a, b) << " , " << pow_improved(a, b) << endl;
    }

   private:
    // O(n) time
    int pow(int a, int b) {
        if (b == 0) return 1;

        if (b % 2) return a * pow(a, b / 2) * pow(a, b / 2);

        return pow(a, b / 2) * pow(a, b / 2);
    }

   private:
    // O(lgn) time
    int pow_improved(int a, int b) {
        if (b == 0) return 1;

        int tmp = pow(a, b / 2);  // replace two recursive calls with single call

        if (b % 2) return a * tmp * tmp;

        return tmp * tmp;
    }

   private:
    // O(lgn) time with caching
    int pow_improved2(int a, int b) {
        unordered_map<string, int> memo;

        return pow_improved2(a, b, memo);
    }
    int pow_improved2(int a, int b, unordered_map<string, int>& memo) {
        if (b == 0) return 1;

        string key = format("{}^{}", a, b);
        if (memo.find(key) != memo.end()) return memo[key];

        int tmp = pow(a, b / 2);  // replace two recursive calls with single call
        int val = (b & 1) ? a * tmp * tmp : tmp * tmp;
        memo[key] = val;

        return memo[key];
    }

   private:
    float fpow(int a, int b) {
        if (b >= 0) return pow(a, b);

        return (float)1 / (float)pow(a, -b);
    }

   private:
    // power without using multiply operator.
    // use mul fuction to perform multiply using +/- operator.
    // 5*2 = 5 + 5
    // 5*-2 = -(5*2) = -(5+5) = 10
    int mul(int a, int b) {
        if (b < 0) return -(mul(a, -b));

        if (b == 0) return 0;

        return a + mul(a, b - 1);
    }

    int pow_without_mul_oper(int a, int b) {
        if (b == 0) return 1;

        int tmp = pow(a, b / 2);

        if (b & 1) return mul(a, mul(tmp, tmp));

        return mul(tmp, tmp);
    }
};