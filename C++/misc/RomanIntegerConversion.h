#pragma once
#include "../header.h"

/*
https://leetcode.com/problems/roman-to-integer/description/?envType=study-plan-v2&envId=top-interview-150

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/
class RomanIntegerConversion {
   public:
    int romanToInt1(string s) {
        int val = 0;
        for (int i = 0; i < s.length(); i++) {
            if (i + 1 < s.length() && romanToVal[s[i + 1]] > romanToVal[s[i]]) {
                val -= romanToVal[s[i]];
            } else {
                val += romanToVal[s[i]];
            }
        }
        return val;
    }

   public:
    int romanToInt2(string s) {
        int val = 0;
        int prev = INT_MIN;
        for (auto& ch : s) {
            if (prev != INT_MIN && prev < romanToVal[ch]) {
                val += romanToVal[ch];
                val -= 2 * prev;
            } else {
                val += romanToVal[ch];
            }
            prev = romanToVal[ch];
        }
        return val;
    }

   public:
    string intToRoman1(int num) {
        string result;
        for (auto& keyValPair : intToRom | std::views::reverse) {
            while (num >= keyValPair.first) {
                result += keyValPair.second;
                num -= keyValPair.first;
            }
        }
        return result;
    }

   public:
    string intToRoman2(int num) {
        string result;
        for (auto& keyValPair : intToRom | std::views::reverse) {
            int cnt = num / keyValPair.first;
            num -= keyValPair.first * cnt;
            while (cnt--) result += keyValPair.second;
        }
        return result;
    }

   private:
    unordered_map<char, int> romanToVal = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}};

    map<int, string> intToRom = {
        {1, "I"},
        {4, "IV"},
        {5, "V"},
        {9, "IX"},
        {10, "X"},
        {40, "XL"},
        {50, "L"},
        {90, "XC"},
        {100, "C"},
        {400, "CD"},
        {500, "D"},
        {900, "CM"},
        {1000, "M"}};
};