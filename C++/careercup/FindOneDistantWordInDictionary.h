#pragma once
#include "../Header.h"

class FindOneDistantWordInDictionary {
public:
    static void test() {
        unordered_set<string> words = { "ab","aapplx","apple", "pineapple", "banana", "orange" };

        {
            string word = "a";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "ab";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "cb";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "ac";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "abc";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "apple";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "aple";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "pple";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "appl";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "aapple";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }

        {
            string word = "applex";

            auto res = findWord(words, word);
            cout << word << " : " << res << endl;
        }
    }

    // Another approach would be to change each character of target string from (a-z) and check if it exists in dictionary.
    // If present, then return true, else false
    // T = O(T * M), where T - length of character (256(entire ascii) or 26(a-z)) and M - length of target word
    // But this only works for case when words doesn't differ in length, only by one char

    // T = O(N*M) , N = number of words in dictionary, M - length of target word
    static string findWord(unordered_set<string>& words, string target) {
        for (auto word : words) {
            if (isOneDistant(word, target)) return word;
        }

        return "";
    }

    static bool isOneDistant(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        if (abs(n - m) > 1) return false;
        bool diff = false;

        for (int i = 0, j = 0; i < n || j < m; i++, j++) {
            if (i == n || j == m || word1[i] != word2[j]) {
                if (diff) return false;
                diff = true;
                if (n < m) i--;
                else if (n > m) j--;
            }
        }

        return diff;
    }
};