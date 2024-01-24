#pragma once
#include "../header.h"

class LongestCommonPrefix {
public:
    static void test() {
        LongestCommonPrefix obj;
        vector<string> input = { "geeksforgeeks", "geeks", "geek", "geezer" };
        cout << obj.longestPrfix(input) << endl;
    }

    string longestPrfix(vector<string>& input) {
        int i = 0;
        bool done = false;
        while (!done) {
            for (int j = 0; j < input.size(); j++) {
                if (i != 0 && input[i] != input[i - 1]) {
                    done = true;  break;
                }
            }
            i++;
        }

        return i == 0 ? string() : input[0].substr(0, i + 1);
    }
};