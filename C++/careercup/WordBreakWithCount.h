#pragma once
#include "../header.h"

/*
Problem: Word Break with Limited Word Usage Count
--------------------------------------------------
Given an input string and a dictionary where each word has a limited number of allowed uses,
determine whether the input string can be segmented into a space-separated sequence of dictionary words
that respects the usage counts.

Example:
  input = "abcababab"
  dictionary = {"abc":3, "ab":2, "abca":1}
  Output: true
--------------------------------------------------
*/

class WordBreakWithCount {
   public:
    static void test() {
        vector<pair<string, unordered_map<string, int>>> testCases = {
            {"abcababab", {{"abc", 3}, {"ab", 2}, {"abca", 1}}},  // true
            {"abcabcabcabc", {{"abc", 3}}},                       // false (limit exceeded)
            {"", {{"a", 1}}},                                     // true (empty string)
            {"xyz", {{"a", 1}, {"b", 1}}},                        // false (no match)
            {"ab", {{"ab", 0}}},                                  // false (count is zero)
            {"ab", {{"a", 1}, {"b", 1}}},                         // true
            {"abcabcabc", {{"abc", 3}}}                           // true
        };

        for (const auto& [input, dict] : testCases) {
            unordered_map<string, int> dictCopy1 = dict;
            unordered_map<string, int> dictCopy2 = dict;

            bool res1 = canWordBreakRec(dictCopy1, input);
            bool res2 = canWordBreak(dictCopy2, input);

            assert(res1 == res2);
            cout << "\nInput: " << input << "\nResult: " << boolalpha << res1 << endl;
        }
    }

    /**
     * Recursive backtracking method with usage count constraints.
     * Time: O(2^n), exponential in worst-case due to recursion
     * Space: O(n) recursion depth
     */
    static bool canWordBreakRec(unordered_map<string, int> dict, const string& input) {
        if (input.empty()) return true;
        int n = static_cast<int>(input.size());
        vector<bool> table(n + 1, false);
        table[0] = true;
        return canWordBreakHelper(dict, input, table);
    }

   private:
    /**
     * Recursive helper function with usage tracking.
     */
    static bool canWordBreakHelper(unordered_map<string, int>& dict, const string& input, vector<bool>& table) {
        if (input.empty()) return true;

        for (auto i = 1; i <= input.length(); ++i) {
            string prefix = input.substr(0, i);
            if (dict[prefix] > 0) {
                dict[prefix]--;
                if (canWordBreakHelper(dict, input.substr(i), table)) return true;
                dict[prefix]++;  // backtrack
            }
        }
        return false;
    }

   public:
    /**
     * Optimized DP-like approach with word count enforcement.
     * Time: O(n^2), Space: O(n)
     */
    static bool canWordBreak(unordered_map<string, int> dict, const string& input) {
        int n = static_cast<int>(input.size());
        vector<bool> table(n + 1, false);
        table[0] = true;

        for (int i = 1; i <= n; ++i) {
            string prefix = input.substr(0, i);
            if (dict[prefix] > 0) {
                dict[prefix]--;
                table[i] = true;
            }
            if (!table[i]) continue;

            for (int j = i + 1; j <= n; ++j) {
                string part = input.substr(i, j - i);
                if (dict[part] > 0) {
                    dict[part]--;
                    table[j] = true;
                }
            }
            if (table[n]) return true;
        }

        return table[n];
    }
};
