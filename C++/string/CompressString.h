#pragma once
#include "../header.h"

class CompressString {
   public:
    static void test() {
        vector<pair<string, string>> tests{
            {"", ""},
            {"a", "a"},
            {"aa", "a2"},
            {"ab", "ab"},
            {"abb", "ab2"},
            {"aaaaa", "a5"},
            {"aaababcccccc", "a3babc6"},
            {"aaaaaababcccccccccccbabccccccbabcccccc", "a6babc11babc6babc6"}};

        for (auto& test : tests) {
            string res1 = compress1(test.first);
            string res2 = compress2(test.first);
            string res3 = compress3(test.first);

            cout << test.first << " : " << res1 << endl;
            assert(test.second == res1);
            assert(test.second == res2);
            assert(test.second == res3);
        }
    }

   public:
    static string compress1(string str) {
        int count = 0;
        char prev = '\0';
        int j = 0;

        for (int i = 0; i <= str.length(); i++) {
            if (prev == '\0') {
                prev = str[i];
                count = 1;
            } else if (i < str.length() && prev == str[i]) {
                count++;
            } else {
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

   public:
    static string compress2(string str) {
        int i = -1;
        char prev = '\0';
        int cnt = 0;
        for (auto ch : str) {
            if (prev != ch) {
                if (cnt > 0) {
                    str[++i] = prev;
                    if (cnt > 1) str[++i] = cnt + '0';
                }
                prev = ch;
                cnt = 0;
            }
            cnt++;
        }
        if (cnt > 0) {
            str[++i] = prev;
            if (cnt > 1) str[++i] = cnt + '0';
        }

        return str.substr(0, i + 1);
    }

   public:
    static string compress3(const string& str) {
        string output;
        int cnt = 0;
        for (int i = 0; i < str.length(); i++) {
            cnt++;
            if (i == str.length() || str[i] != str[i + 1]) {
                output += str[i];
                if (cnt > 1) output += to_string(cnt);
                cnt = 0;
            }
        }

        return output;
    }
};