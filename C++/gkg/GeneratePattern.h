#pragma once
#include "../Header.h"

class GeneratePattern {
public:
    static void test() {
        GeneratePattern obj;
        for (auto i = 0; i <= 5; i++) {
            cout << i << " = " << obj.generate(i) << endl;
        }
    }

    string generate(int n) {
        string str = "1";
        for (int i = 1; i <= n; i++) {
            string cur;
            int cnt = 1;
            char prev = str[0];
            for (int j = 1; j <= str.length(); j++) {
                if (j == str.length() || str[j] != prev) {
                    cur += to_string(cnt) + prev;
                    cnt = 0;
                }
                if (j < str.length()) {
                    prev = str[j];
                    cnt++;
                }
            }

            str = cur;
        }

        return str;
    }
};