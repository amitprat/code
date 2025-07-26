#pragma once
#include "../header.h"
using namespace std;

/**
 * @class FindLongestSubstrWithSameCountLettersNumbers
 * @brief Finds the longest substring in a given string that has an equal number of digits and letters.
 *
 * ## Problem
 * Given a string containing digits and letters, find the longest substring such that
 * the count of digits equals the count of letters.
 *
 * ## Example
 * ```
 * Input:  "a11a"
 * Output: "a11a"   // 2 digits and 2 letters
 *
 * Input:  "1aa1"
 * Output: "1aa1"   // also balanced
 *
 * Input:  "asdasd12312131a"
 * Output: "asdasd12312131"   // longest balanced substring
 * ```
 *
 * ## Approaches Implemented
 * 1. **findLongestStr()** — Efficient O(N) approach using prefix difference map.
 * 2. **findBruteForce()** — Naive O(N²) approach for verification.
 */
class FindLongestSubstrWithSameCountLettersNumbers {
   public:
    /**
     * @brief Test function demonstrating multiple sample cases.
     */
    static void test() {
        FindLongestSubstrWithSameCountLettersNumbers obj;

        vector<string> strs = {
            "", "a", "1", "11", "aa", "1a1", "a11a", "1aa1", "a111a",
            "1asd1s", "asdasd12312131a", "1a1"};

        for (auto& str : strs) {
            auto fastRes = obj.findLongestStr(str);
            auto slowRes = obj.findBruteForce(str);
            cout << format("String='{}' → Longest balanced substring='{}'\n", str, fastRes);
            assert(fastRes == slowRes && "Mismatch between optimized and brute-force results!");
        }
    }

   public:
    /**
     * @brief Finds the longest substring with equal number of digits and letters using O(N) algorithm.
     *
     * This function uses a prefix difference map where:
     *   diff = (#digits so far) - (#letters so far)
     *
     * If the same `diff` value appears twice (say at indices i and j),
     * it means the substring between them (i+1 to j) has equal counts of digits and letters.
     *
     * @param str The input string containing alphanumeric characters.
     * @return The longest balanced substring (empty if none found).
     */
    string findLongestStr(const string& str) {
        unordered_map<int, int> firstIndexOfDiff;  // diff → first occurrence index
        int diff = 0;                              // diff = digits - letters
        pair<int, int> best = {0, 0};              // start, length of best substring

        firstIndexOfDiff[0] = -1;  // base case: diff=0 before any character

        for (int i = 0; i < (int)str.size(); i++) {
            if (isdigit(str[i])) diff++;
            else if (isalpha(str[i])) diff--;

            if (firstIndexOfDiff.find(diff) == firstIndexOfDiff.end()) {
                // first time we see this diff → record its index
                firstIndexOfDiff[diff] = i;
            } else {
                // seen before → balanced substring between firstIndexOfDiff[diff]+1 and i
                int start = firstIndexOfDiff[diff] + 1;
                int length = i - start + 1;
                if (length > best.second)
                    best = {start, length};
            }
        }

        if (best.second == 0) return "";  // no balanced substring found
        return str.substr(best.first, best.second);
    }

   public:
    /**
     * @brief Brute-force O(N²) method to verify results.
     *
     * Checks all substrings by counting digits and letters directly.
     *
     * @param str The input string.
     * @return The longest balanced substring (empty if none found).
     */
    string findBruteForce(const string& str) {
        int n = str.size();
        int maxLen = 0, startIdx = -1;

        for (int i = 0; i < n; i++) {
            int digitCount = 0, letterCount = 0;
            for (int j = i; j < n; j++) {
                if (isdigit(str[j])) digitCount++;
                else if (isalpha(str[j])) letterCount++;

                if (digitCount == letterCount && (j - i + 1) > maxLen) {
                    maxLen = j - i + 1;
                    startIdx = i;
                }
            }
        }

        if (maxLen == 0) return "";
        return str.substr(startIdx, maxLen);
    }

   public:
    int findLongestPrefixArray(const string& s) {
        int n = s.size();
        vector<int> digits(n + 1, 0), letters(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            digits[i] = digits[i - 1] + isdigit(s[i - 1]);
            letters[i] = letters[i - 1] + isalpha(s[i - 1]);
        }

        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (digits[j] - digits[i] == letters[j] - letters[i])
                    maxLen = max(maxLen, j - i);
            }
        }

        return maxLen;
    }

   public:
    /*
     * Find longest subarray using prefix match.
     */
    int findLongestBalancedSubarray(const string& s) {
        unordered_map<int, int> first;
        int prefix = 0, maxLen = 0;
        first[0] = -1;

        for (int i = 0; i < s.size(); i++) {
            prefix += (isdigit(s[i]) ? 1 : -1);

            if (!first.count(prefix))
                first[prefix] = i;
            else
                maxLen = max(maxLen, i - first[prefix]);
        }

        return maxLen;
    }
};