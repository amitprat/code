#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5768136489959424

write a function that has an int as input and return the equivalent String as an output
12 -> 'twelve'
4345 -> 'four thousand three hundred and forty-five'
7654567643 -> 'seven billion six hundred and fifty-four million five hundred and sixty-seven thousand six hundred and forty-three'
*/

class ConvertNumberToWords {
    map<unsigned long long, string> numMap = {
        {1, "one" },{2, "two" },{3, "three" },{4, "four" },{5, "five" },{6, "six" },{7, "seven" },{8, "eight" },{9, "nine" },
        {10, "ten" },{11, "eleven" },{12, "twelve" },{13, "thirteen" },{14, "fourteen" },{15, "fifteen" },{16, "sixteen" },{17, "seventeen" },{18, "eighteen" },{19, "ninteen" },
        {20, "twenty" },{30, "thirty" },{40, "forty" },{50, "fifty" },{60, "sixty" },{70, "seventy" },{80, "eighty" },{90, "ninty" },
        {100, "hundrend" },
        {1000, "thousand" },
        {1000000, "million" },
        {1000000000, "billion" }
    };

public:
    static void test() {
        unsigned long long num = 7654567643;

        ConvertNumberToWords obj;
        string res = obj.convertToWords(num);

        cout << format("num={}, in words={}", num, res) << endl;

        num = 12;
        res = obj.convertToWords(num);
        cout << format("num={}, in words={}", num, res) << endl;

        num = 4345;
        res = obj.convertToWords(num);
        cout << format("num={}, in words={}", num, res) << endl;

        srand(time(nullptr));
        for (int i = 1; i < 798; i += rand() % 10) {
            res = obj.convertToWords(i);
            cout << format("num={}, in words={}", i, res) << endl;
        }
    }

    string convertToWords(unsigned long long num) {
        if (num == 0) return "zero";
        string result;

        for (auto it = numMap.rbegin(); it != numMap.rend(); it++) {
            if (num >= it->first) {
                if (num < 100) {
                    result += it->second + " ";
                    num -= it->first;
                }
                else {
                    unsigned long long div = num / it->first;
                    num = num - (div * it->first);
                    result += convertToWords(div) + " " + it->second + " ";
                }
            }
        }
        if (!result.empty()) result.pop_back();
        return result;
    }
};