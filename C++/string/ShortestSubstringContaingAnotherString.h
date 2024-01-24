#pragma once
#include "../Header.h"
using namespace std;

class ShortestSubstringContaingAnotherString
{
public:
    static void test()
    {
        ShortestSubstringContaingAnotherString obj;
        vector<pair<string, string>> inputs = {
            {"xyz", "afdgzeyfxksldfmyzx"}
        };
        for (auto& input : inputs) {
            cout << "Shortest string = " << obj.findShortestString(input.first, input.second) << endl;
        }
    }

    string findShortestString(string pat, string txt)
    {
        int patCnt[128] = { 0 };
        int txtCnt[128] = { 0 };
        int n = txt.size(), m = pat.size();

        for (auto ch : pat) patCnt[ch]++;

        int i = 0;
        int cnt = 0;
        string shortest;
        for (int j = 0; j < n; j++) {
            txtCnt[txt[j]]++;
            if (txtCnt[txt[j]] <= patCnt[txt[j]]) cnt++;

            if (cnt == m) {
                while (txtCnt[txt[i]] > patCnt[txt[i]]) {
                    txtCnt[txt[i]]--;
                    i++;
                }
            }
            if (cnt == m) {
                string cur = txt.substr(i, j - i + 1);
                if (shortest.empty() || cur.length() < shortest.length()) shortest = cur;
            }
        }

        return shortest;
    }
};