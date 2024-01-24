#include "../header.h"

class PermuteWords {
    void permute(vector<string>& words, int wordPos, string cur) {
        if (wordPos == words.size()) {
            cout << cur << endl;
            return;
        }

        for (auto& ch : words[wordPos]) {
            permute(words, wordPos + 1, cur + ch);
        }
    }
};