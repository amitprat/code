#pragma once
#include "../header.h"

class WordPatternMatch {
   public:
    bool wordPattern(string pattern, string s) {
        auto words = split(s);
        if (pattern.size() != words.size()) return false;

        unordered_map<string, char> wordToChar;
        unordered_map<char, string> charToWord;

        for (int i = 0; i < pattern.size(); i++) {
            char ch = pattern[i];
            string word = words[i];
            cout << ch << " " << word << endl;

            if (charToWord.contains(ch) && charToWord[ch] != word) return false;
            if (wordToChar.contains(word) && wordToChar[word] != ch) return false;
            charToWord[ch] = word;
            wordToChar[word] = ch;
        }

        return true;
    }

    vector<string> split(string& s) {
        vector<string> result;
        int start = 0;
        auto pos = s.find(' ', start);
        while (pos != string::npos) {
            result.push_back(s.substr(start, pos - start));
            start = pos + 1;
            pos = s.find(' ', start);
        }
        result.push_back(s.substr(start));
        return result;
    }
};