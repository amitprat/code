#pragma once
#include "../Header.h"

class WordDistance {
    struct Pair {
        string first, second;
        Pair(string first, string second) :first(first), second(second) {}
    };

private:
    unordered_map<string, vector<int>> wordMap;

public:
    static void test() {
        WordDistance obj;
        string s = "the quick the brown quick brown the frog";
        string w1 = "quick";
        string w2 = "frog";

        cout << "Distance = " << obj.getDistanceOnline(s, w1, w2) << endl;
        obj.init(s);
        cout << "Distance = " << obj.getDistanceOffline(w1, w2) << endl;
    }

    void init(string s) {
        vector<string> words = split(s);
        for (int i = 0; i < words.size(); i++) {
            wordMap[words[i]].push_back(i);
        }
    }

    int getDistanceOffline(string w1, string w2) {
        auto l1 = wordMap[w1];
        auto l2 = wordMap[w2];
        int i = 0, j = 0;
        int dist = INT_MAX;
        while (i < l1.size() && j < l2.size()) {
            dist = min(dist, abs(l1[i] - l2[j]));
            if (l1[i] < l2[j]) i++;
            else  j++;
        }
        return dist;
    }

    int getDistanceOnline(string s, string w1, string w2) {
        vector<string> words = split(s);
        int pos1 = -1, pos2 = -1;
        int dist = INT_MAX;
        for (int pos = 0; pos < words.size(); pos++) {
            if (words[pos] == w1) pos1 = pos;
            else if (words[pos] == w2) pos2 = pos;
            if (pos1 != -1 && pos2 != -1) {
                dist = min(dist, abs(pos1 - pos2));
            }
        }
        return dist;
    }

    vector<string> split(string s) {
        size_t pos = 0;
        vector<string> res;
        char delim = ' ';
        while (1) {
            auto cur = s.find(delim, pos);
            if (cur != string::npos) res.push_back(s.substr(pos, cur - pos));
            else {
                res.push_back(s.substr(pos));
                break;
            }
            pos = cur + 1;
        }
        return res;
    }
};