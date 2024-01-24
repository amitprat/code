#pragma once
#include "../Header.h"

class LongestWordMadeOfOthers {
    struct Node {
        bool isEnd = false;
        unordered_map<char, Node*> children;
    };
    class Trie {
        Node* root = nullptr;
    public:
        void insert(string str) {
            root = insert(root, str);
        }

        vector<string> traverse(string str) {
            vector<string> result;
            traverse(root, str);
        }

    private:
        Node* insert(Node* root, string str, int index = 0) {
            if (!root) root = new Node();
            if (index == str.length()) { root->isEnd = true; return root; }
            root->children[str[index]] = insert(root->children[str[index]], str, index + 1);
            return root;
        }
    };
public:
    static void test() {
        LongestWordMadeOfOthers obj;
        vector<string> strs = { "rat", "cat", "abc", "xyz", "abcxyz", "ratcatabc", "xyzcatratabc" };

        vector<string> res;
        auto word = obj.findLongestWord(strs, res);

        cout << word << endl;
        cout << to_string(res) << endl;
    }

    string findLongestWordTrie(vector<string>& strs) {
        for (auto str : strs) {

        }
    }

    string findLongestWord(vector<string>& strs, vector<string>& res) {
        sort(strs.begin(), strs.end(), [](auto f, auto s) {return (f.size() > s.size()); });

        unordered_set<string> dict;
        for (auto& str : strs) dict.insert(str);

        for (auto& str : strs) {
            res.clear();
            if (isMadeOfOthers(str, res, dict)) {
                return str;
            }
        }

        return "";
    }

    bool isMadeOfOthers(string str, vector<string>& res, unordered_set<string> dict) {
        if (str.empty()) return true;
        for (int l = 1; l <= str.length(); l++) {
            auto cur = str.substr(0, l);
            auto rest = str.substr(l);
            res.push_back(cur);
            if (dict.find(cur) != dict.end() && isMadeOfOthers(rest, res, dict)) return true;
            res.pop_back();
        }
        return false;
    }
};