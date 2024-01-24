#pragma once
#include "../header.h"

class MaxValueOfExpr {
private:
    vector<char> ops = { '+','-','*','/' };
public:
    static void test() {
        MaxValueOfExpr obj;
        vector<double> arr = { 1,1,1,5 };
        cout << "max value of " << to_string(arr) << " = " << obj.maxValue(arr) << endl;
    }

    double maxValue(vector<double> arr) {
        unordered_map<string, double> memo;
        return maxValue(arr, 0, arr.size() - 1, memo);
    }

private:
    double maxValue(vector<double> arr, int s, int e, unordered_map<string, double>& memo) {
        if (s > e) return 0;
        if (s == e) return arr[s];
        if (memo.find(key(s, e)) != memo.end()) return memo[key(s, e)];
        double mxVal = 0;

        for (int k = s; k < e; k++) {
            double left = maxValue(arr, s, k, memo);
            double right = maxValue(arr, k + 1, e, memo);

            for (auto& op : ops) {
                mxVal = max(mxVal, apply(left, right, op));
            }
        }
        memo[key(s, e)] = mxVal;

        return mxVal;
    }

    string key(int s, int e) {
        return "Max(" + std::to_string(s) + "," + std::to_string(e) + ")";
    }

    double apply(double a, double b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
        }
        return 0;
    }
};