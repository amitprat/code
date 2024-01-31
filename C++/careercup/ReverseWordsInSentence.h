#pragma once
#include "../header.h"

/*
Write a code to reverse the words in a sentence.
*/
class ReverseWordsInSentence {
   public:
    static void test() {
        ReverseWordsInSentence obj;
        string str = "this is a sentence";
        string out = obj.reverse(str);
        cout << "Revered string: " << out << endl;
    }

   private:
    string reverse(const string &input) {
        string result = input;

        int s = 0;
        int e = 0;
        for (e = 0; e <= input.size(); e++) {
            if (e == input.size() || isspace(input[e])) {
                reverse(result, s, e - 1);
                s = e + 1;
            }
        }

        return result;
    }

    void reverse(string &input, int s, int e) {
        while (s < e) {
            swap(input[s++], input[e--]);
        }
    }
};