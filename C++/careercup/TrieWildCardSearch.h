#pragma once
#include "../Header.h"

class TrieWildCardSearch {
    struct Node {
        bool end = false;
        unordered_map<char, Node*> children;
    };
    Node* root = new Node();
public:
    static void test() {
        TrieWildCardSearch obj;
        vector<string> words = { "car","caw","cauw" };
        string pat = "c*";
        for (auto& word : words) obj.insert(word);
        vector<string> res = obj.search(words, pat);
        cout << to_string(res) << endl;
    }

    void insert(string word) {
        root = insert(root, word, 0, word.size());
    }
    vector<string> search(vector<string>& words, string& pat) {
        vector<string> result;
        search(root, pat, 0, result, "");

        return result;
    }

private:
    Node* insert(Node* node, string word, int idx, int n) {
        if (!node) node = new Node();
        if (idx == n) { node->end = true; return node; }

        node->children[word[idx]] = insert(node->children[word[idx]], word, idx + 1, n);

        return node;
    }

    void search(Node* node, string pat, int idx, vector<string>& result, string prefix) {
        if (!node) return;
        if (idx == pat.length()) {
            if (node->end) result.push_back(prefix);
            return;
        }

        if (pat[idx] == '*') {
            for (auto& child : node->children) {
                search(child.second, pat, idx, result, prefix + child.first);
            }
            search(node, pat, idx + 1, result, prefix);
        }
        else if (pat[idx] == '.') {
            for (auto& child : node->children) {
                search(child.second, pat, idx + 1, result, prefix + child.first);
            }
        }
        else {
            search(node->children[pat[idx]], pat, idx + 1, result, prefix + pat[idx]);
        }
    }
};