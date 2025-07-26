#pragma once
#include "../header.h"

/*
 *  Text Justification
 * https://leetcode.com/problems/text-justification/description/?envType=study-plan-v2&envId=top-interview-150
 * Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
 */
class TextJustification {
   public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;

        for (int s = 0; s < words.size();) {
            int curWidth = 0;
            int e = s;
            for (; e < words.size() && curWidth + words[e].length() + 1 <= maxWidth; e++) {
                curWidth += words[e].length();
                curWidth += 1;  // for space
            }
            e--;

            int gaps = e - s;
            string cur;
            if (e == words.size() || gaps == 0) {
                for (auto& j = s; j <= e; j++) cur += words[j] + (j != e ? "_" : "");
                cur += string(maxWidth - curWidth, '_');
            } else {
                int space = (maxWidth - curWidth) / gaps;
                int remaining = maxWidth - curWidth - (space * gaps);

                for (auto& j = s; j <= e; j++) cur += words[j] + (j != e ? string(space + 1, '_') : "");
                cur += string(remaining, '_');
            }

            result.push_back(cur);
            s = e + 1;
        }

        return result;
    }

   public:
    static void test() {
        vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
        int maxWidth = 16;

        TextJustification obj;
        auto result = obj.fullJustify(words, maxWidth);
        for (auto& str : result) cout << setw(16) << str << endl;
    }
};