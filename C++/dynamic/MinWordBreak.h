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
#include <tuple>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

class Node
{
public:
    bool isEnd;
    vector<Node*> children;

    Node(bool isEnd = false) {
        for (int i = 0; i < 256; i++) children.push_back(nullptr);
        this->isEnd = isEnd;
    }
};

class Trie
{
public:
    Node* root = nullptr;
    Trie() {
        root = new Node();
    }

    void add(string word) {
        Node* tmp = root;
        for (int i = 0; i < word.size(); i++) {
            if (tmp->children[word[i]] == nullptr)
                tmp->children[word[i]] = new Node();
            tmp = tmp->children[word[i]];
        }
        tmp->isEnd = true;
    }

    bool search(string word) {
        Node* tmp = root;
        for (int i = 0; i < word.size(); i++) {
            if (tmp->children[word[i]] == nullptr) return false;
            tmp = tmp->children[word[i]];
        }
        return tmp->isEnd;
    }

    vector<string> get(string prefix) {
        vector<string> result;
        getInternalPrefix(root, prefix, result, string());
        return result;
    }

    vector<string> get() {
        vector<string> result;
        getInternal(root, result, string());
        return result;
    }

private:
    void getInternal(Node* cur, vector<string>& result, string curWord) {
        if (cur == nullptr) return;
        if (cur->isEnd) { result.push_back(curWord); }

        for (int i = 0; i < 256; i++) {
            if (cur->children[i] != nullptr) {
                getInternal(cur->children[i], result, curWord + (char)i);
            }
        }
    }

    void getInternalPrefix(Node* cur, string prefix, vector<string>& result, string curWord) {
        if (cur == nullptr) return;
        if (prefix.empty()) {
            getInternal(cur, result, curWord);
            return;
        }

        for (int i = 0; i < prefix.length(); i++) {
            if (cur->children[prefix[i]]) {
                getInternalPrefix(cur->children[prefix[i]], prefix.substr(1), result, curWord + prefix[i]);
            }
        }
    }
};

class MinWordBreak
{
public:
    static void test()
    {
        MinWordBreak obj;
        string word = "CatMat";
        unordered_set<string> dictionary = { "Mat", "Ca","tM","at","C","Dog","og","Do", "Cat" };
        int mn = obj.findMin(word, dictionary);
        cout << "Min = " << mn << endl;

        mn = obj.findMinDP(word, dictionary);
        cout << "MinDP = " << mn << endl;

        cout << "Total = " << obj.findTotalCountDP(word, dictionary) << endl;

        obj.printAllWordDP(word, dictionary);
    }

    static int Count(Trie& trie, string const& s, vector<int>& memo, int idx = 0)
    {
        if (idx > s.size()) return 0;
        if (idx == s.size()) return 1;

        if (memo[idx] != -1) return memo[idx];

        int count = 0;
        Node* n = trie.root;
        for (int i = idx; i < s.size(); ++i) {
            n = n->children[s[i]];
            if (!n) {
                break;
            }
            if (n->isEnd) {
                count += Count(trie, s, memo, i + 1);
            }
        }

        memo[idx] = count;
        return memo[idx];
    }

    static void trietest()
    {
        Trie trie;
        trie.add("dog");
        trie.add("eat");
        trie.add("eats");
        trie.add("scare");
        trie.add("care");

        auto res = trie.get();
        for (auto i : res) cout << i << " ";
        cout << endl;

        string word = "dogeatscare";
        vector<int> memo;
        memo.resize(word.size());
        std::fill(memo.begin(), memo.end(), -1);
        cout << Count(trie, word, memo) << "\n";
    }

    int findMin(string word, unordered_set<string> dict)
    {
        if (word.empty()) return 0;
        if (dict.count(word)) return 0;
        int mn = INT_MAX;
        for (int i = 1; i <= word.length(); i++) {
            if (dict.count(word.substr(0, i))) {
                int curMin = findMin(word.substr(i), dict);
                if (curMin != INT_MAX) mn = min(mn, curMin + 1);
            }
        }
        return mn;
    }

    int findMinDP(string word, unordered_set<string> dict) {
        int* table = new int[word.length() + 1];
        table[0] = 0;
        for (int i = 1; i < word.length() + 1; i++) table[i] = INT_MAX;
        for (int i = 1; i <= word.length(); i++) {
            if (dict.count(word.substr(0, i))) {
                table[i] = 0;
            }
            if (table[i] != INT_MAX) {
                for (int j = i + 1; j <= word.length(); j++) {
                    if (dict.count(word.substr(i, j - i))) {
                        table[j] = min(table[j], 1 + table[i]);
                    }
                }
            }
        }

        //for (int i = 1; i <= word.length(); i++) {
        //    cout << table[i] << " ";
        //    cout << endl;
        //}

        return table[word.length()];
    }

    int findTotalCountDP(string word, unordered_set<string> dict) {
        int* table = new int[word.length() + 1];
        table[0] = 1;
        for (int i = 1; i < word.length() + 1; i++) table[i] = 0;
        for (int i = 1; i <= word.length(); i++) {
            if (dict.count(word.substr(0, i))) {
                table[i] += 1;
            }
            if (table[i] != 0) {
                for (int j = i + 1; j <= word.length(); j++) {
                    if (dict.count(word.substr(i, j - i))) {
                        table[j] += table[i];
                    }
                }
            }
        }

        //for (int i = 1; i <= word.length(); i++) {
        //    cout << table[i] << " ";
        //    cout << endl;
        //}

        return table[word.length()];
    }

    void printMinWordDP(string word, unordered_set<string> dict) {
        vector<unordered_set<string>> table;
        table.resize(word.length() + 1);
        for (int i = 1; i <= word.length(); i++) {
            if (dict.count(word.substr(0, i))) {
                table[i] = { word.substr(0,i) };
            }
            if (!table[i].empty()) {
                for (int j = i + 1; j <= word.length(); j++) {
                    if (dict.count(word.substr(i, j - i))) {
                        if (table[i].size() < table[j].size() - 1) {
                            table[j].insert(table[i].begin(), table[i].end());
                            table[j].insert(word.substr(i, j - i));
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= word.length(); i++) {
            for (auto j : table[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void printAllWordDP(string word, unordered_set<string> dict) {
        vector<vector<unordered_set<string>>> table;
        table.resize(word.length() + 1);
        for (int i = 1; i <= word.length(); i++) {
            if (dict.count(word.substr(0, i))) {
                table[i].push_back({ word.substr(0, i) });
            }
            if (!table[i].empty()) {
                for (int j = i + 1; j <= word.length(); j++) {
                    if (dict.count(word.substr(i, j - i))) {
                        vector<unordered_set<string>> thisPointWordSet = table[i];
                        for (auto& thisPointWord : thisPointWordSet) thisPointWord.insert(word.substr(i, j - i));
                        table[j].insert(table[j].end(), thisPointWordSet.begin(), thisPointWordSet.end());
                    }
                }
            }
        }

        for (int i = 1; i <= word.length(); i++) {
            for (auto j : table[i]) {
                for (auto k : j) {
                    cout << k << " ";
                }
                cout << "; ";
            }
            cout << endl;
        }
    }
};