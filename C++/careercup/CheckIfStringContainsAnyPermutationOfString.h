#include "../header.h"

/*
https://careercup.com/question?id=15555796
Given a string, find whether it has any permutation of another string. For example, given "abcdefg" and "ba",
it shuold return true, because "abcdefg" has substring "ab", which is a permutation of "ba".
*/

class CheckIfStringContainsAnyPermutationOfString {
   public:
    static void test() {
        CheckIfStringContainsAnyPermutationOfString obj;

        vector<vector<string>> inputs = {
            {"abcddedffeeg", "fed"},
            {"eidbacoo", "abc"},
            {"cbahello", "abc"},
            {"defghij", "abc"},
            {"abcd", "abcd"},
            {"abcdef", ""},
            {"bababa", "aabb"},
            {"xyzdcba", "abcd"}};
        for (auto& input : inputs) {
            auto str = input[0];
            auto pat = input[1];

            auto res1 = obj.contains1(str, pat);
            auto res2 = obj.contains2(str, pat);
            auto res3 = obj.contains3(str, pat);
            assert(res1 == res2);
            assert(res1 == res3);

            cout << format("{} contains any permutation of {}, result: {}", str, pat, res1) << endl;
        }
    }

   private:
    bool contains1(string str, string pat) {
        vector<int> txtCnt(256, 0);
        vector<int> patCnt(256, 0);
        for (auto ch : pat) patCnt[ch]++;

        int s = 0;
        int cnt = 0;
        int n = str.length();
        int m = pat.length();
        for (int i = 0; i < n; i++) {
            // include current character
            char ch = str[i];
            txtCnt[ch]++;
            cnt++;

            // remove characters on left (including current) which aren't part of pattern
            while (s <= i && txtCnt[ch] > patCnt[ch]) {
                txtCnt[str[s]]--;
                s++;
                cnt--;
            }

            // if we still left with characters count matching with pattern, then we found the match
            if (cnt == m) return true;
        }

        return false;
    }

    bool contains2(string& str, string& pat) {
        vector<int> patCnt(256, 0), strCnt(256, 0);

        for (auto ch : pat) {
            patCnt[ch]++;
        }

        int cnt = 0;
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            strCnt[ch]++;
            if (strCnt[ch] <= patCnt[ch]) cnt++;

            if (cnt == pat.length()) return true;

            if (i >= pat.length()) {
                char old = str[i - pat.length()];
                if (strCnt[old] <= patCnt[old]) cnt--;
                strCnt[old]--;
            }
        }

        return false;
    }

    bool contains3(string& str, string& pat) {
        vector<int> strCnt(256, 0), patCnt(256, 0);

        for (int i = 0; i < pat.length(); i++) {
            strCnt[str[i]]++;
            patCnt[pat[i]]++;
        }

        if (strCnt == patCnt) return true;

        for (int i = pat.length(); i < str.length(); i++) {
            strCnt[str[i - pat.length()]]--;
            strCnt[str[i]]++;

            if (strCnt == patCnt) return true;
        }

        return false;
    }
};