#pragma once
#include "../Header.h"

class BidirectionalWordLadder {
public:
    static void test() {
        BidirectionalWordLadder obj;
        vector<string> wordList;
        wordList.push_back("poon");
        wordList.push_back("plee");
        wordList.push_back("same");
        wordList.push_back("poie");
        wordList.push_back("plie");
        wordList.push_back("poin");
        wordList.push_back("plea");

        string start = "toon";
        string target = "plea";

        cout << obj.ladderLength(start, target, wordList);
    }

    int ladderLength(string start, string target, vector<string> wordList) {
        queue<pair<string, int>> fwdQueue, revQueue;
        fwdQueue.push({ start,1 });
        revQueue.push({ target,1 });

        unordered_map<string, int> visited1, visited2;

        while (!fwdQueue.empty() && !revQueue.empty()) {
            auto cur1 = fwdQueue.front(); fwdQueue.pop();
            if (cur1.first == target) return cur1.second;
            if (visited2.count(cur1.first)) {
                return cur1.second + visited2[cur1.first] - 1;
            }

            auto cur2 = revQueue.front(); revQueue.pop();
            if (cur2.first == start) return cur2.second;
            if (visited1.count(cur2.first)) {
                return cur2.second + visited1[cur2.first] - 1;
            }

            vector<string> neighbours = getNeighbours(cur1.first, wordList, visited1);
            for (auto& n : neighbours) {
                visited1[n] = cur1.second + 1;
                fwdQueue.push({ n,cur1.second + 1 });
            }

            neighbours = getNeighbours(cur2.first, wordList, visited2);
            for (auto& n : neighbours) {
                visited2[n] = cur2.second + 1;
                revQueue.push({ n,cur2.second + 1 });
            }
        }

        return 0;
    }

    vector<string> getNeighbours(string cur, vector<string>& wordList, unordered_map<string, int>& visited) {
        vector<string> result;

        for (auto& str : wordList) {
            if (!visited.count(str)) {
                int cnt = 0;
                for (int i = 0; i < min(str.length(), cur.length()); i++) {
                    if (str[i] != cur[i]) cnt++;
                }
                if (cnt == 1) result.push_back(str);
            }
        }

        return result;
    }
};