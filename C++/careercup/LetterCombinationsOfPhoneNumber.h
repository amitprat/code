#include "../header.h"

/*
* https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
* Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
* A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
*/

class LetterCombinationsOfPhoneNumber {
   public:
    vector<string> letterCombinations(string digits) {
        unordered_map<char, vector<char>> mappings = {
            {'1', {}},
            {'2', {'a', 'b', 'c'}},
            {'3', {'d', 'e', 'f'}},
            {'4', {'g', 'h', 'i'}},
            {'5', {'j', 'k', 'l'}},
            {'6', {'m', 'n', 'o'}},
            {'7', {'p', 'q', 'r', 's'}},
            {'8', {'t', 'u', 'v'}},
            {'9', {'w', 'x', 'y', 'z'}}};

        vector<string> result;
        letterCombinations(digits, 0, digits.size(), mappings, "", result);

        return result;
    }

    void letterCombinations(string digits, int idx, int n,
                            unordered_map<char, vector<char>>& mappings,
                            string cur, vector<string>& result) {
        if (idx == n) {
            if (!cur.empty()) result.push_back(cur);
            return;
        }

        if (idx > n) return;
        auto ch = digits[idx];
        if (mappings[ch].empty()) return;

        for (auto& alpha : mappings[ch]) {
            letterCombinations(digits, idx + 1, n, mappings, cur + alpha, result);
        }
    }
};