#pragma once
#include "../header.h"
using namespace std;

/**
 * @class LongestCommonPrefix
 * @brief Finds the longest common prefix (LCP) among a set of strings.
 *
 * Example:
 *   Input: {"geeksforgeeks", "geeks", "geek", "geezer"}
 *   Output: "gee"
 */
class LongestCommonPrefix {
   public:
    /**
     * @brief Test function with sample input.
     */
    static void test() {
        LongestCommonPrefix obj;
        vector<string> input = {"geeksforgeeks", "geeks", "geek", "geezer"};
        cout << "Longest Common Prefix: " << obj.longestPrefixHorizontalScanning(input) << endl;

        vector<string> input2 = {"flower", "flow", "flight"};
        cout << "Longest Common Prefix: " << obj.longestPrefix(input2) << endl;

        vector<string> input3 = {"dog", "racecar", "car"};
        cout << "Longest Common Prefix: " << obj.longestPrefix(input3) << endl;

        vector<string> input4 = {};
        cout << "Longest Common Prefix: " << obj.longestPrefix(input4) << endl;
    }

    /**
     * @brief Computes the longest common prefix (LCP) among all strings.
     * @param strs Vector of input strings.
     * @return The longest common prefix. Returns empty string if no common prefix.
     */
    string longestPrefixHorizontalScanning(const vector<string>& strs) {
        if (strs.empty()) return "";

        // Take the first string as reference
        string prefix = strs[0];

        for (size_t i = 1; i < strs.size(); i++) {
            int j = 0;
            // Compare characters of prefix and current string
            while (j < prefix.size() && j < strs[i].size() && prefix[j] == strs[i][j]) {
                j++;
            }
            // Shrink prefix to match common part
            prefix = prefix.substr(0, j);

            // If prefix becomes empty, no common prefix exists
            if (prefix.empty()) break;
        }

        return prefix;
    }

   public:
    string longestPrefixVerticalScanning(const vector<string>& strs) {
        if (strs.empty()) return "";

        string result = "";
        for (int j = 0; j < strs[0].size(); j++) {   // vertical scan
            for (int i = 1; i < strs.size(); i++) {  // iterate over all strings
                if (j >= strs[i].size() || strs[i][j] != strs[0][j]) {
                    // mismatch found → return result up to j
                    return result;
                }
            }
            // current character matches all strings → append it
            result += strs[0][j];
        }

        return result;
    }

   public:
    string longestPrefixSorting(vector<string> strs) {
        if (strs.empty()) return "";

        sort(strs.begin(), strs.end());
        string first = strs.front();
        string last = strs.back();

        int i = 0;
        while (i < first.size() && i < last.size() && first[i] == last[i]) {
            i++;
        }

        return first.substr(0, i);
    }
};