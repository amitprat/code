#pragma once
#include "../header.h"

/**
 * @class KMP
 * @brief Implements the Knuth-Morris-Pratt (KMP) algorithm for substring search.
 *
 * The KMP algorithm efficiently finds all occurrences of a pattern `pat` in a text `txt`
 * in linear time, O(n + m), where:
 * - n = length of text
 * - m = length of pattern
 *
 * Example:
 *   Input: txt = "abcde", pat = "bcd"
 *   Output: indices = {1}, count = 1
 */
class KMP {
   public:
    /**
     * @brief Runs example test cases.
     */
    static void test() {
        KMP obj;
        vector<pair<string, string>> cases = {
            {"abcde", "bcd"},
            {"aaaaaa", "aa"},
            {"abcdefghcde", "cde"},
            {"ababababa", "aba"},
            {"mississippi", "issi"},
            {"abc", ""},  // empty pattern
            {"", "abc"}   // empty text
        };

        for (const auto& [txt, pat] : cases) {
            auto [indices, count] = obj.substringSearch(txt, pat);
            cout << format("Text='{}', Pattern='{}' => Count={}, Indices={{", txt, pat, count);
            for (size_t i = 0; i < indices.size(); i++) {
                cout << indices[i] << (i + 1 < indices.size() ? ", " : "");
            }
            cout << "}}\n";
        }
    }

   public:
    /**
     * @brief Finds all occurrences of `pat` in `txt` using KMP algorithm.
     * @param txt The text string.
     * @param pat The pattern to search for.
     * @return A pair {vector of starting indices, total count}.
     */
    pair<vector<int>, int> substringSearch(const string& txt, const string& pat) {
        int n = txt.size();
        int m = pat.size();

        if (m == 0 || n == 0 || m > n) return {{}, 0};

        vector<int> lps = computeLPS(pat);
        vector<int> indices;
        int count = 0;

        int i = 0;  // index for txt
        int j = 0;  // index for pat

        while (i < n) {
            if (txt[i] == pat[j]) {
                i++;
                j++;
            }

            if (j == m) {
                indices.push_back(i - j);
                count++;
                j = lps[j - 1];  // continue search for next match
            } else if (i < n && txt[i] != pat[j]) {
                if (j != 0) j = lps[j - 1];
                else i++;
            }
        }

        return {indices, count};
    }

   private:
    /**
     * @brief Computes the Longest Prefix Suffix (LPS) array.
     *
     * LPS[i] = length of the longest proper prefix of `pat[0..i]`
     * that is also a suffix of this substring.
     *
     * Example: For pattern "ababaca", LPS = [0, 0, 1, 2, 3, 0, 1]
     */
    vector<int> computeLPS(const string& pat) {
        int m = pat.size();
        vector<int> lps(m, 0);
        int len = 0;  // length of previous longest prefix suffix
        int i = 1;

        while (i < m) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) len = lps[len - 1];
                else lps[i++] = 0;
            }
        }
        return lps;
    }
};