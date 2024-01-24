#pragma once
#include "../header.h"

class CompressString {
public:
    static void test() {
        CompressString obj;
        vector<pair<string, string>> tests{
            {"",""},
            {"a","a"},
            {"aa","a2"},
            {"ab","ab"},
            {"abb","ab2"},
            {"aaaaa","a5"},
            {"aaababcccccc","a3babc6"},
            {"aaaaaababcccccccccccbabccccccbabcccccc","a6babc11babc6babc6"}
        };
        for (auto& test : tests) {
            string res = obj.compress(test.first);
            cout << test.first << " : " << res << endl;
            assert(test.second == res);
        }
    }

    string compress(string str) {
        int count = 0;
        char prev = '\0';
        int j = 0;
        for (int i = 0; i <= str.length(); i++) {
            if (prev == '\0') { prev = str[i]; count = 1; }
            else if (i < str.length() && prev == str[i]) { count++; }
            else {
                str[j++] = prev;
                if (count > 1) {
                    string countStr = std::to_string(count);
                    for (auto ch : countStr) str[j++] = ch;
                }
                if (i < str.length()) {
                    prev = str[i];
                    count = 1;
                }
            }
        }
        str = str.substr(0, j);
        return str;
    }
};