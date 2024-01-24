#pragma once
#include "../header.h"

class FindPeriod {
   public:
    static void test() {
        FindPeriod obj;
        vector<string> inputs = {"ababab", "xxxxxx"};
        for (auto str : inputs) {
            auto isP = obj.isPeriod(str);
            auto res = obj.findPeriod(str);

            cout << "Is Period = " << isP << endl;
            cout << "Result = " << res.first << ", " << res.second << endl;
        }
    }

    bool isPeriod(string str) {
        return (str.substr(1) + str.substr(0, str.length() - 1)).find(str) != string::npos;
    }
    pair<string, int> findPeriod(string str) {
        int n = str.length();
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                string period = str.substr(0, i);
                int j = i;
                while (j <= n) {
                    if (str.substr(j, i) != period) break;
                    j += i;
                    if (j == n) return {period, n / i};
                }
            }
        }
        return {"", -1};
    }
};