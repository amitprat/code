#pragma once
#include "../Header.h"

class RearrangeCharactersToFormPalindromIfPossible {
public:
    static void test() {
        vector<string> inputs = { "mdaam", "amisi", "missisipi", "abracadabra", "acsxc", "zxczca", "ababc" };

        for (auto& input : inputs) {
            string result = rearrangeCharactersToFormPalindromIfPossible(input);

            cout << format("Input={}, Output={}", input, result) << endl;
        }
    }

    static string rearrangeCharactersToFormPalindromIfPossible(string& str) {
        vector<int> freq(256, 0);
        for (auto ch : str) freq[ch]++;

        int oddCnt = 0;
        for (auto e : freq) {
            if (e & 1) oddCnt++;

            if (oddCnt > 1) return "not possible";
        }

        if (oddCnt == 1 && (str.length() & 1) == 0) return "not possible";
        if (oddCnt == 0 && (str.length() & 1) == 1) return "not possible";

        string firstHalf, secondHalf;
        char middle = '\0';

        for (int i = 0; i < 256; i++) {
            if (freq[i] == 0) continue;

            if (freq[i] & 1) middle = (char)i;
            else {
                int l = freq[i] / 2;
                firstHalf += string(l, (char)i);
                secondHalf = string(l, (char)i) + secondHalf;
            }
        }

        if (middle == '\0') return firstHalf + secondHalf;
        return firstHalf + middle + secondHalf;
    }
};