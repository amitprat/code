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

        vector<string> words = {"car", "caw", "cauw"};
        string pat = "c*";
        for (auto& word : words) obj.insert(word);

        vector<string> res = obj.search(pat);
        cout << "Words with matching pattern are: " << to_string(res) << endl;
    }

    void insert(const string& word) {
        root = insert(root, word, 0, word.size());
    }

    vector<string> search(const string& pat) {
        vector<string> result;
        search(root, pat, 0, result, "");

        return result;
    }

   private:
    Node* insert(Node* node, const string& word, int idx, int n) {
        if (!node) node = new Node();
        if (idx == n) {
            node->end = true;
            return node;
        }

        node->children[word[idx]] = insert(node->children[word[idx]], word, idx + 1, n);

        return node;
    }

    void search(Node* node, const string& pat, int idx, vector<string>& result, string prefix) {
        if (!node) return;
        if (idx == pat.length()) {
            if (node->end) result.push_back(prefix);
            return;
        }

        if (pat[idx] == '*') {
            // by considering the current character
            for (auto& child : node->children) {
                search(child.second, pat, idx, result, prefix + child.first);
            }

            // by skipping the current character
            search(node, pat, idx + 1, result, prefix);
        } else if (pat[idx] == '.') {
            // matching the current character with any character
            for (auto& child : node->children) {
                search(child.second, pat, idx + 1, result, prefix + child.first);
            }
        } else {
            // by exact matching of character
            search(node->children[pat[idx]], pat, idx + 1, result, prefix + pat[idx]);
        }
    }
};