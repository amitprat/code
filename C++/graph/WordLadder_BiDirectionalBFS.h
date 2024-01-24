#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <algorithm>
using namespace std;

class WordLadder
{
private:
    //MemoryEfficientTrie trie;

public:
    static void test() {
        WordLadder obj;
        string beginWord = "hit";
        string endWord = "hot";
        unordered_set<string> dict = { "hot", "dot", "dog", "lot", "log", "cog" };
        //unordered_set<string> dict = { "poon", "plee", "same", "poie", "plie", "poin", "plea" };

        auto result = obj.findShortestPath(beginWord, endWord, dict);
        print(result);
    }

    static void print(vector<string>& result) {
        for (auto& s : result) cout << s << " ";
        cout << endl;
    }

    //void preprocess(vector<string>& words) {
    //    for (auto& s : words) trie.insert(s);
    //}

    vector<string> findShortestPath(string& begin, string& end, unordered_set<string>& dict) {
        queue <pair<string, vector<string>>> q;
        q.push({ begin, {begin} });
        unordered_set<string> visited;
        vector<string> res;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto cur = q.front(); q.pop();
                if (cur.first == end) {
                    res = cur.second; break;
                }
                visited.insert(cur.first);

                auto neighbours = getOneDistantWords(cur.first, dict, visited);
                for (auto neighbour : neighbours) {
                    auto tmp = cur.second;
                    tmp.push_back(neighbour);
                    q.push({ neighbour,tmp });
                    visited.insert(neighbour);
                }
            }
        }
        cout << res.size() << endl;
        return res;
    }

    vector<string> getOneDistantWords(string begin, unordered_set<string>& dict, unordered_set<string>& visited) {
        vector<string> res;
        for (int i = 0; i < begin.length(); i++) {
            char tmp = begin[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (begin[i] != ch) {
                    begin[i] = ch;
                    if (dict.find(begin) != dict.end() && visited.find(begin) == visited.end()) res.push_back(begin);
                }
            }
            begin[i] = tmp;
        }

        return res;
    }
};