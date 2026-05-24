#pragma once
#include "../header.h"

class StringMultiplication {
   public:
    static void test() {
        StringMultiplication obj;

        string num1 = "123";
        string num2 = "456";
        auto res = obj.multiply(num1, num2);
        println("num1={0} num2={1} res={2}", num1, num2, res);
    }

    string multiply(string num1, string num2) {
        if (num1.empty() || num2.empty()) return "0";
        if (num1 == "0" || num2 == "0") return "0";

        int m = num1.size(), n = num2.size();
        vector<int> result(m + n, 0);

        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + result[i + j];

                result[i + j] = sum % 10;
                result[i + j + 1] += sum / 10;
            }
        }

        bool leadingZero = true;
        string res;
        for (int k = result.size() - 1; k >= 0; k--) {
            if (result[k] == 0 && leadingZero) continue;
            leadingZero = false;
            res.push_back(result[k] + '0');
        }

        return res.empty() ? "0" : res;
    }
};