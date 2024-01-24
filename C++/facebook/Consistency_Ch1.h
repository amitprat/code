#pragma once
#include "../Header.h"

class Consistency_Ch1
{
public:
    int main() {
        Consistency_Ch1 obj;
        int tests;
        cin >> tests;
        vector<string> inputs;
        for (int i = 0; i < tests; i++) {
            string str;
            cin >> str;
            inputs.push_back(str);
        }

        for (int i = 0; i < tests; i++) {
            cout << "Case #" << i << ": " << obj.getMinTransformations(inputs[i]) << endl;
        }

        return 0;
    }

    int getMinTransformations(string str) {
        int freq[26] = { 0 };
        int vowels = 0;
        int consonants = 0;
        for (auto ch : str) {
            freq[ch - 'A']++;
        }

        char vowelWithHighestFreq;
        char consonantWithHighestFreq;
        int vowelMaxFreq = 0;
        int consonantMaxFreq = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                char ch = 'A' + i;
                if (isVowel(ch)) {
                    vowels += freq[i];
                    if (freq[i] > vowelMaxFreq) {
                        vowelMaxFreq = freq[i];
                        vowelWithHighestFreq = ch;
                    }
                }
                else {
                    consonants += freq[i];
                    if (freq[i] > consonantMaxFreq) {
                        consonantMaxFreq = freq[i];
                        consonantWithHighestFreq = ch;
                    }
                }
            }
        }
        char toChar;
        if (vowelMaxFreq == 0 && consonantMaxFreq == 0) {
            return 0;
        }
        else if (vowelMaxFreq == 0) {
            int costOfTraslatingToVowel = str.length();
            int costOfTranslatingToMaxConsonant = 2 * (str.length() - consonantMaxFreq);
            toChar = costOfTraslatingToVowel < costOfTranslatingToMaxConsonant ? 'I' : consonantWithHighestFreq;
        }
        else if (consonantMaxFreq == 0) {
            int costOfTraslatingToConsonant = str.length();
            int costOfTranslatingToMaxvowel = 2 * (str.length() - vowelMaxFreq);
            toChar = costOfTraslatingToConsonant < costOfTranslatingToMaxvowel ? 'X' : vowelWithHighestFreq;
        }
        else {
            int costOfTranslatingToMaxConsonant = vowels + 2 * (consonants - consonantMaxFreq);
            int costOfTranslatingToMaxvowel = consonants + 2 * (vowels - vowelMaxFreq);
            toChar = costOfTranslatingToMaxConsonant < costOfTranslatingToMaxvowel ? consonantWithHighestFreq : vowelWithHighestFreq;
        }

        int transformations = 0;
        cout << "ToChar: " << toChar << endl;
        for (auto ch : str) {
            if (ch != toChar) {
                if ((isVowel(toChar) && !isVowel(ch)) ||
                    (!isVowel(toChar) && isVowel(ch))) {
                    transformations++;
                }
                else {
                    transformations += 2;
                }
            }
        }

        return transformations;
    }

    bool isVowel(char ch) {
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') return true;
        return false;
    }
};