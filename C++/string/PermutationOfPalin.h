#pragma once
#include "../header.h"

class PermutationOfPalin {
public:
    static void test() {
        PermutationOfPalin obj;
        vector<string> tests = {
            "","a","ab","aa","aba","abba","baba","sfdsvs","sdxcv","bdfbdf"
        };
        for (auto& test : tests) {
            cout << setw(16) << test << " : " << obj.isPermOfPalin(test) << endl;
        }
    }

    bool isPermOfPalin(string& str) {
        int checker = 0;
        int oddCount = 0;
        for (auto ch : str) {
            if (toggle(checker, ch)) oddCount++;
            else oddCount--;
        }
        return oddCount <= 1;
    }

private:
    bool toggle(int& checker, char ch) {
        int mask = (1 << (ch - 'a'));
        if (isset(checker, mask)) {
            checker = reset(checker, mask); return false;
        }
        else {
            checker = set(checker, mask); return true;
        }
    }

    bool isset(int checker, int mask) { return checker & mask; }
    int set(int checker, int mask) { return checker | mask; }
    int reset(int checker, int mask) { return checker & ~mask; }
};