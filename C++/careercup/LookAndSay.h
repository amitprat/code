#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=15519735

Implement LookAndSay function. For example, first, let user input a number, say 1.
Then, the function will generate the next 10 numbers which satisfy this condition:
    1, 11,21,1211,111221,312211...

    Explanation: first number 1, second number is one 1, so 11. Third number is two 1(previous number), so 21.
    next number one 2 one 1, so 1211 and so on...
*/

class LookAndSay {
   public:
    static string lookAndSay(long long n) {
        string s = to_string(n);
        int cnt = 0;

        stringstream ss;

        char prev = '$';
        for (auto& ch : s) {
            if (prev != ch) {
                if (cnt > 0) {
                    ss << cnt;
                    ss << prev;
                }

                prev = ch;
                cnt = 1;
            } else {
                cnt++;
            }
        }

        if (cnt > 0) {
            ss << cnt;
            ss << prev;
        }

        return ss.str();
    }

   public:
    static void test() {
        string first = "1";
        for (int i = 1; i < 10; i++) {
            first = lookAndSay(stoll(first));
            cout << first << endl;
        }
    }
};