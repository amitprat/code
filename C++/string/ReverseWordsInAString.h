#pragma once

#include "../header.h"

class ReverseWordsInSentence {
public:
    static void test() {
        ReverseWordsInSentence obj;
        string str = "I am a human being";
        cout << "Input: " << str << endl;
        obj.replace(str);
        cout << "Output: " << str << endl;
    }

    // Total = O(2n) ~ O(n)
    // O(n) calls here for looking for space or end
    void reverseInPlace(string& str) {
        for (int i = 0, j = 0; j <= str.length(); j++) {
            if (j == str.length() || str[j] == ' ') {
                if (j > i + 1) {
                    reverseWords(str, i, j - 1);
                }
                i = j + 1;
            }
        }
    }

    void replaceWithStdReplace(string& str) {
        string word;
        for (int i = 0, j = 0; j <= str.length(); j++) {
            if (j == str.length() || str[j] == ' ') {
                if (j > i + 1) {
                    str.replace(i, j - i, word);
                }
                word.clear();
                i = j + 1;
            }
            else {
                word = str[j] + word;
            }
        }
    }

    void replace(string& str) {
        string word;
        string output;
        for (int i = 0, j = 0; j <= str.length(); j++) {
            if (j == str.length() || str[j] == ' ') {
                output += word;
                output += ' ';
                word.clear();
                i = j + 1;
            }
            else {
                word = str[j] + word;
            }
        }
        str = output;
    }

private:
    // O(n/2) calls here for reverse word part
    void reverseWords(string& str, int s, int e) {
        while (s < e) {
            swap(str[s++], str[e--]);
        }
    }
};