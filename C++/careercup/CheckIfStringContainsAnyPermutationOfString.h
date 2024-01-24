#include "../header.h"

/*
https://careercup.com/question?id=15555796
Given a string, find whether it has any permutation of another string. For example, given "abcdefg" and "ba", it shuold return true, because "abcdefg" has substring "ab", which is a permutation of "ba".
*/
class CheckIfStringContainsAnyPermutationOfString {
   public:
    static void test() {
        CheckIfStringContainsAnyPermutationOfString obj;
        string str = "abcddedffeeg";
        string txt = "fed";
        auto res = obj.contains(str, txt);
        cout << format("{} contains any permutation of {}, result: {}", str, txt, res) << endl;
    }

   private:
    bool contains(string str, string pat) {
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

            // if we still left with characters count matching with patter, then we found the match
            if (cnt == m) return true;
        }

        return false;
    }
};