#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=14948278

we will name a number "aggregated number" if this number has the following attribute:
just like the Fibonacci numbers
1,1,2,3,5,8,13.....

the digits in the number can divided into several parts, and the later part is the sum of the former parts.

like 112358, because 1+1=2, 1+2=3, 2+3=5, 3+5=8
122436, because 12+24=36
1299111210, because 12+99=111, 99+111=210
112112224, because 112+112=224
so can you provide a function to check whether this number is aggregated number or not?
*/
class CheckIfNumberIsAggregatedNumber {
   public:
    static void test() {
        CheckIfNumberIsAggregatedNumber obj;

        vector<string> inputs = {"134", "", "01124", "2324", "112358", "122436", "1299111210", "112112224"};
        for (auto input : inputs) {
            bool res = obj.isAggregated(input);
            cout << format("Is number={} aggregated number={}", input, res) << endl;
        }
    }

   private:
    bool isAggregated(string input) {
        int len = input.length();
        int half = len / 2;
        for (int i = 1; i <= half; i++) {
            for (int j = 1; j <= half; j++) {
                if (isMatch(input, i, j)) return true;
            }
        }

        return false;
    }

    bool isMatch(string input, int i, int j) {
        string first = input.substr(0, i);
        string second = input.substr(i, j);

        string buffer = first + second;

        while (buffer.length() < input.length()) {
            string third = to_string(stoi(first) + stoi(second));
            first = second;
            second = third;

            buffer += third;
        }

        return buffer == input;
    }
};