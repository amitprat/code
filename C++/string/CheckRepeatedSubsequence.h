#pragma once
#include "../header.h"

/**
 * @class CheckRepeatedSubsequence
 * @brief Provides utilities to check if a string contains a repeated subsequence or a repeated substring.
 *
 * This class demonstrates two related but distinct problems:
 * 1. Checking if a string has a repeated **subsequence** (characters may not be contiguous).
 * 2. Checking if a string is made by repeating a smaller **substring** pattern.
 *
 * Example:
 *  - For subsequences:
 *      Input: "abba" → true  (since "ab" appears twice as a subsequence)
 *  - For substrings:
 *      Input: "abab" → true  (since "ab" repeats twice)
 */
class CheckRepeatedSubsequence {
   public:
    /**
     * @brief Test driver for both repeated subsequence and repeated substring functions.
     *
     * Demonstrates example usage with sample inputs.
     *
     * Output:
     * ```
     * String: abba
     * Is repeated subsequence? true
     *
     * String: abab
     * Repeating pattern = ab
     * Is repeated substring? true
     * ```
     */
    static void test() {
        {
            string str = "abba";
            bool res = isRepeatedSubsequence(str);
            cout << "String: " << str << endl;
            cout << "Is repeated subsequence? " << boolalpha << res << endl
                 << endl;
        }

        {
            string str = "abab";
            bool res = isRepeatedSubstring(str);
            cout << "String: " << str << endl;
            cout << "Is repeated substring? " << boolalpha << res << endl
                 << endl;
        }
    }

    /**
     * @brief Checks if a string contains a repeated subsequence (not necessarily contiguous).
     *
     * Uses dynamic programming to find the Longest Repeated Subsequence (LRS).
     * The logic is similar to finding the Longest Common Subsequence (LCS)
     * of the string with itself, but disallowing matching the same index.
     *
     * @param str Input string.
     * @return true if a repeated subsequence of length > 1 exists, false otherwise.
     *
     * @example
     *  - "abba" → true  (subsequence "ab" repeats)
     *  - "abc"  → false
     */
    static bool isRepeatedSubsequence(const string& str) {
        int n = static_cast<int>(str.size());
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Build DP table for Longest Repeated Subsequence
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && str[i - 1] == str[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // If the longest repeated subsequence has length > 1
        return dp[n][n] > 1;
    }

    /**
     * @brief Checks if the string can be constructed by repeating a smaller substring.
     *
     * Iterates over all possible substring lengths that divide the full length,
     * and checks if repeating the substring reconstructs the full string.
     *
     * @param str Input string.
     * @return true if the string is composed of repeated substrings, false otherwise.
     *
     * @example
     *  - "abab" → true  (pattern "ab")
     *  - "abcabcabc" → true  (pattern "abc")
     *  - "abcd" → false
     */
    static bool isRepeatedSubstring(const string& str) {
        int n = static_cast<int>(str.size());

        // Check all possible substring lengths
        for (int i = 1; i <= n / 2; i++) {
            if (n % i != 0) continue;  // must divide evenly

            string pattern = str.substr(0, i);
            bool valid = true;

            // Check if pattern repeats across the entire string
            for (int j = i; j < n; j += i) {
                if (str.substr(j, i) != pattern) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                cout << "Repeating pattern = " << pattern << endl;
                return true;
            }
        }

        return false;
    }
};