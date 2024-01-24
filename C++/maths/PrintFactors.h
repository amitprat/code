#pragma once
#include "../header.h"

class PrintFactors {
public:
    static void test() {
        PrintFactors obj;
        //cout << to_string(obj.factors(12)) << endl;

        auto executor = [](int a) {cout << a << " "; };
        vector<int> arr = { 1,2,3,4 };
        doTest(executor, arr);
    }

    static void doTest(std::function<void(int)> func, vector<int> arr) {
        cout << func.target_type << endl;
        for (auto i : arr) {
            func(i);
        }
    }

    vector<int> factors(int num) {
        vector<int> res;
        return res;
    }
};