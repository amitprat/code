#pragma once
#include "../Header.h"
using namespace std;

class MakeSmallestStringByRemovingDuplicateCharacters
{
public:
    static void test()
    {
        MakeSmallestStringByRemovingDuplicateCharacters obj;
        vector<string> inputs = { "bcsbc", "cbacdcbc" };
        for (auto& input : inputs) {
            string res = obj.findSmallest(input);

            cout << format("Smallest lexographic string for input={} is {}", input, res) << endl;
        }
    }

    string findSmallest(string str)
    {
        int len = str.length();
        vector<int> next(len);

        int lastPos[26];
        for (int i = 0; i < 26; i++) lastPos[i] = -1;

        for (int i = len - 1; i >= 0; i--) {
            char cur = str[i] - 'a';
            next[i] = lastPos[cur];
            lastPos[cur] = i;
        }

        vector<bool> visited(26, false);
        string res;

        for (int i = 0; i < len; i++) {
            int cur = str[i] - 'a';
            if (visited[cur]) continue;

            // if this is the last character of this type
            if (next[i] == -1) {
                res += str[i];
                visited[cur] = true;
            }
            else
            {
                // find the next smallest possible character
                int j = i + 1;
                char nextSmall = str[i];
                while (j < len) {
                    if (!visited[str[j] - 'a']) {
                        nextSmall = min(nextSmall, str[j]);
                        if (next[j] == -1) break;
                    }
                    j++;
                }

                if (str[i] <= nextSmall) {
                    res += str[i];
                    visited[cur] = true;
                }
            }
        }

        return res;
    }
};