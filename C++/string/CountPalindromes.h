#pragma once
#include "../header.h"

/**
 * @class CountPalindromes
 * @brief Counts the number of palindromic substrings in a given string.
 *
 * A palindrome is a string that reads the same forward and backward.
 *
 * Example:
 *   Input: "abba"
 *   Palindromic substrings:
 *     "a", "b", "b", "a", "bb", "abba"
 *   Total = 6
 *
 * This implementation uses Dynamic Programming (DP)
 * where `dp[i][j]` indicates whether substring `str[i..j]` is a palindrome.
 */
class CountPalindromes {
   public:
    /**
     * @brief Test driver for palindrome counting function.
     *
     * Demonstrates example usage with printed results.
     *
     * Example Output:
     * ```
     * String: abba
     * Palindromic substrings = 6
     * ```
     */
    static void test() {
        string str = "abba";

        int res = countPalindromes(str);
        cout << "String: " << str << endl;
        cout << "Palindromic substrings = " << res << endl;
    }

    /**
     * @brief Counts all palindromic substrings using dynamic programming.
     *
     * @param str Input string.
     * @return Number of palindromic substrings.
     *
     * ### Algorithm:
     * 1. Initialize a DP table `dp[n][n]` where `dp[i][j] = true`
     *    if substring `str[i..j]` is a palindrome.
     * 2. Every single character is a palindrome.
     * 3. A pair of identical characters forms a palindrome.
     * 4. For substrings of length > 2, check if the outer characters match
     *    and the inner substring is also a palindrome.
     *
     * ### Time Complexity:
     * O(n²)
     *
     * ### Space Complexity:
     * O(n²)
     *
     * ### Examples:
     *  - Input: "abba" → Output: 6
     *  - Input: "aaa"  → Output: 6 ("a","a","a","aa","aa","aaa")
     *  - Input: "abc"  → Output: 3 ("a","b","c")
     */
    static int countPalindromes(const string& str) {
        int n = static_cast<int>(str.length());
        if (n == 0) return 0;

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int count = 0;

        // Step 1: Single characters are palindromes
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
            count++;
        }

        // Step 2: Check substrings of length >= 2
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;

                if (str[i] == str[j]) {
                    if (len == 2 || dp[i + 1][j - 1]) {
                        dp[i][j] = true;
                        count++;
                    }
                }
            }
        }

        return count;
    }
};