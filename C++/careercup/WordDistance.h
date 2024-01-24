#pragma once
#include "../Header.h"

class WordDistance {
public:
    static void test() {
        WordDistance obj;

        {
            string  s = "geeks for geeks contribute practice";
            string w1 = "geeks";
            string w2 = "practice";
            cout << "Distance = " << obj.distance(s, w1, w2) << endl;
        }
        {
            string s = "the quick the brown quick brown the frog";
            string w1 = "quick";
            string w2 = "frog";
            cout << "Distance = " << obj.distance(s, w1, w2) << endl;
        }
    }

    int distance(string s, string w1, string w2) {
        vector<string> parts = split(s);
        
        pair<int, int> mnDist = { -999, 999 };
        pair<int, int> cur = { -1, -1 };
        
        int index = 0;
        for (auto& word : parts) {
            if (word == w1) cur.first = index;
            if (word == w2) cur.second = index;
            if (cur.first != -1 && cur.second != -1 && abs(cur.second - cur.first) < abs(mnDist.second - mnDist.first)) {
                mnDist = cur;
            }
            index++;
        }

        cout << "Path = ";
        for (auto i = mnDist.first; i <= mnDist.second; i++) cout << parts[i] << " ";
        cout << endl;

        return abs(mnDist.second - mnDist.first);
    }

    vector<string> split(string s) {
        string delimiter = " ";
        vector<string> result;

        size_t pos = string::npos;
        while ((pos=s.find(delimiter)) != string::npos) {
            result.push_back(s.substr(0, pos));
            s = s.substr(pos + 1);
        }
        if (!s.empty()) result.push_back(s);

        return result;
    }
};