#pragma once
#include "../header.h"

/**
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/?envType=study-plan-v2&envId=top-interview-150
 *
 * Given a string s, find the length of the longest substring without duplicate characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * @class LongestSubstrWithoutRepeatingChars
 * @brief Finds the longest substring without repeating characters in a string.
 *
 * Example:
 *   Input: "geeksforgeeks"
 *   Output: "eksforg"
 */
class LongestSubstrWithoutRepeatingChars {
   public:
    static void test() {
        string s = "geeksforgeeks";
        cout << "Input String: " << s << endl;

        string longest1 = longestUniqueSubstr(s);
        string longest2 = longestUniqueSubstr2(s);
        int length3 = longestUniqueSubstr3(s);

        cout << "Longest substring (method1): " << longest1 << endl;
        cout << "Longest substring (method2): " << longest2 << endl;
        cout << "Length of longest substring (method3): " << length3 << endl;
    }

    // https://leetcode.com/problems/longest-substring-without-repeating-characters/description/?envType=problem-list-v2&envId=oizxjoit
    static int lengthOfLongestSubstring(string str) {
        int longest = 0;
        vector<int> lastPos(256, -1);
        for (int s = 0, e = 0; e < str.length(); e++) {
            auto ch = str[e];
            if (lastPos[ch] != -1) s = max(s, lastPos[ch] + 1);
            longest = max(longest, e - s + 1);
            lastPos[ch] = e;
        }
        return longest;
    }

    /**
     * Method 1: Works only for lowercase 'a'-'z'
     */
    static string longestUniqueSubstr(const string& str) {
        vector<int> lastPos(26, -1);  // last index of each character
        int s = 0;                    // start of current window
        string longest = "";

        for (int e = 0; e < str.size(); e++) {
            int index = str[e] - 'a';

            // lastPos[index] >= s => this check is required to nullify the effct of all values from <= s
            //  in a normal bool array case, we set them false expiclitely. Here, we are smartly ignoring them.
            if (lastPos[index] != -1 && lastPos[index] >= s) {
                // update longest substring before moving start
                if (e - s > longest.size()) longest = str.substr(s, e - s);
                s = lastPos[index] + 1;  // move start after previous occurrence
            }
            lastPos[index] = e;
        }

        // check the last window
        if (str.size() - s > longest.size()) longest = str.substr(s);

        return longest;
    }

    /**
     * Method 2: Works for all ASCII characters
     */
    static string longestUniqueSubstr2(const string& str) {
        vector<int> lastPos(256, -1);  // last index of each ASCII char
        int start = 0;
        pair<int, int> maxPos = {0, -1};  // start and end index of max substring

        for (int end = 0; end < str.size(); end++) {
            start = max(start, lastPos[str[end]] + 1);

            if (end - start > maxPos.second - maxPos.first)
                maxPos = {start, end};

            lastPos[str[end]] = end;
        }

        return str.substr(maxPos.first, maxPos.second - maxPos.first + 1);
    }

    /**
     * Method 3: Returns length only, works for all characters
     */
    static int longestUniqueSubstr3(const string& str) {
        unordered_map<char, int> lastPos;
        int maxLen = 0;
        int start = 0;

        for (int end = 0; end < str.size(); end++) {
            if (lastPos.find(str[end]) != lastPos.end() && lastPos[str[end]] >= start) {
                start = lastPos[str[end]] + 1;  // move start after previous occurrence
            }
            lastPos[str[end]] = end;
            maxLen = max(maxLen, end - start + 1);
        }

        return maxLen;
    }

   public:
    static int lengthOfLongestSubstring4(string str) {
        unordered_map<char, int> lastPos;
        int longest = 0;

        for (int i = 0, j = 0; j < str.length(); j++) {
            auto ch = str[j];
            if (lastPos.contains(ch)) {
                auto prevPos = lastPos[ch];
                while (i <= prevPos) lastPos.erase(str[i++]);
            }
            lastPos[ch] = j;
            longest = max(longest, j - i + 1);
        }

        return longest;
    }

   public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> lastPos;
        int mxLen = 0;
        for (int i = 0, j = 0; j < s.length(); j++) {
            auto ch = s[j];
            if (lastPos.contains(s[j])) {
                i = max(i, lastPos[s[j]] + 1);
            }
            lastPos[ch] = j;

            mxLen = max(mxLen, j - i + 1);
        }
        return mxLen;
    }

   public:
    int characterReplacement(string s, int k) {
        int mx = 0, res = 0;
        unordered_map<char, int> freq;

        for (int l = 0, r = 0; r < s.length(); r++) {
            freq[s[r]]++;
            mx = max(mx, freq[s[r]]);
            while (r - l + 1 - mx > k) {
                freq[s[l]]--;
                l++;
            }
            res = max(res, r - l + 1);
        }

        return res;
    }
};