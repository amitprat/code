#pragma once
#include "../header.h"

/**
 * @class CompressString
 * @brief Implements string compression algorithms that replace consecutive repeating
 *        characters with the character followed by the count of repetitions.
 *
 * Example:
 *   Input:  "aaabbcccc"
 *   Output: "a3b2c4"
 *
 * Rules:
 *  - If a character appears only once, it is left unchanged.
 *  - Consecutive repeats are represented as `<char><count>`.
 *
 * Example Mappings:
 *  - "" → "" (empty string)
 *  - "a" → "a"
 *  - "aa" → "a2"
 *  - "abb" → "ab2"
 *  - "aaaaaababcccccccccccbabccccccbabcccccc"
 *    → "a6babc11babc6babc6"
 *
 * All three `compressX()` methods produce identical output but differ in implementation style.
 */
class CompressString {
   public:
    /**
     * @brief Test driver for all compression variants.
     *
     * Runs a set of sample test cases against all three compression implementations
     * (`compress1`, `compress2`, and `compress3`), verifies consistency using `assert`,
     * and prints results for quick validation.
     */
    static void test() {
        vector<pair<string, string>> tests{
            {"", ""},
            {"a", "a"},
            {"aa", "a2"},
            {"ab", "ab"},
            {"abb", "ab2"},
            {"aaaaa", "a5"},
            {"aaababcccccc", "a3babc6"},
            {"aaaaaababcccccccccccbabccccccbabcccccc", "a6babc11babc6babc6"}};

        for (auto& test : tests) {
            const string& input = test.first;
            const string& expected = test.second;

            string res1 = compress1(input);
            string res2 = compress2(input);
            string res3 = compress3(input);

            cout << "Input: \"" << input << "\""
                 << " → Compressed: \"" << res1 << "\"" << endl;

            assert(expected == res1);
            assert(expected == res2);
            assert(expected == res3);
        }

        cout << "\n✅ All test cases passed successfully!" << endl;
    }

    /**
     * @brief Compresses the string in-place using index manipulation.
     *
     * @param str Input string (modified in-place).
     * @return Compressed string.
     *
     * Implementation details:
     *  - Traverses the string character by character.
     *  - Maintains a write index (`j`) and current run count (`count`).
     *  - Rewrites the input string as compressed version and trims the excess.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1) (in-place)
     */
    static string compress1(string str) {
        if (str.empty()) return "";

        int count = 0;
        char prev = '\0';
        int j = 0;

        for (int i = 0; i <= static_cast<int>(str.length()); i++) {
            if (i == 0) {
                prev = str[i];
                count = 1;
            } else if (i < str.length() && str[i] == prev) {
                count++;
            } else {
                // Write the previous character and count if needed
                str[j++] = prev;
                if (count > 1) {
                    string countStr = to_string(count);
                    for (char ch : countStr) str[j++] = ch;
                }
                // Reset for next sequence
                if (i < str.length()) {
                    prev = str[i];
                    count = 1;
                }
            }
        }

        return str.substr(0, j);
    }

    /**
     * @brief Compresses the string using character iteration and a write index.
     *
     * @param str Input string (modified in-place).
     * @return Compressed string.
     *
     * This method demonstrates an alternative style where we maintain
     * a write index `i` and explicitly write the previous run when a change occurs.
     *
     * ⚠️ This version assumes run lengths are single-digit for simplicity.
     * If run lengths exceed 9, the result may be incorrect (e.g., "aaaaaaaaaaa" → "a:" instead of "a11").
     */
    static string compress2(string str) {
        if (str.empty()) return "";

        int i = -1;
        char prev = '\0';
        int count = 0;

        for (char ch : str) {
            if (prev != ch) {
                // Write previous run
                if (count > 0) {
                    str[++i] = prev;
                    if (count > 1) {
                        string cntStr = to_string(count);
                        for (char c : cntStr) str[++i] = c;
                    }
                }
                prev = ch;
                count = 0;
            }
            count++;
        }

        // Write last run
        if (count > 0) {
            str[++i] = prev;
            if (count > 1) {
                string cntStr = to_string(count);
                for (char c : cntStr) str[++i] = c;
            }
        }

        return str.substr(0, i + 1);
    }

    /**
     * @brief Clean and simple version using a separate output string.
     *
     * @param str Input string (read-only).
     * @return Compressed string.
     *
     * Implementation details:
     *  - Iterates once through the string.
     *  - Builds the output by appending the current character and count.
     *
     * This version is the easiest to read and extend.
     */
    static string compress3(const string& str) {
        if (str.empty()) return "";

        string output;
        int count = 1;

        for (size_t i = 1; i <= str.size(); i++) {
            if (i < str.size() && str[i] == str[i - 1]) {
                count++;
            } else {
                output += str[i - 1];
                if (count > 1) output += to_string(count);
                count = 1;
            }
        }

        return output;
    }
};