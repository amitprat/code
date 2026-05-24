#pragma once
#include "../header.h"

// You are given a string s and an array of strings words. All the strings of words are of the same length.

// A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

// For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
// Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.

// Example 1:

// Input: s = "barfoothefoobarman", words = ["foo","bar"]

// Output: [0,9]

vector<int> findSubstring(string s, vector<string>& words) {
    if (s.empty() || words.empty()) return {};

    int n = s.size();
    int wordLen = words[0].size();
    int wordCount = words.size();
    int totalLen = wordLen * wordCount;

    unordered_map<string_view, int> target;
    target.reserve(words.size());

    for (auto& w : words) {
        target[w]++;
    }

    vector<int> result;

    for (int offset = 0; offset < wordLen; offset++) {
        unordered_map<string_view, int> window;
        window.reserve(words.size());

        int left = offset;
        int count = 0;

        for (int right = offset; right + wordLen <= n; right += wordLen) {
            string_view cur(s.data() + right, wordLen);

            if (!target.count(cur)) {
                window.clear();
                count = 0;
                left = right + wordLen;
                continue;
            }

            window[cur]++;
            count++;

            // shrink window if too many
            while (window[cur] > target[cur]) {
                string_view leftWord(s.data() + left, wordLen);
                window[leftWord]--;
                left += wordLen;
                count--;
            }

            // valid match
            if (count == wordCount) {
                result.push_back(left);

                // slide forward
                string_view leftWord(s.data() + left, wordLen);
                window[leftWord]--;
                left += wordLen;
                count--;
            }
        }
    }

    return result;
}