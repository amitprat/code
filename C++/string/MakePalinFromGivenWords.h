#pragma once
#include "../Header.h"

class MakePalinFromGivenWords {
    struct Node {
        unordered_map<char, Node*> children;
        bool isEnd = false;
    };
    class Trie {
        Node* root = nullptr;
    public:
        Trie() {
            root = new Node();
        }
        void insert(string str) {
            root = insert(root, str, 0);
        }
        bool find(string str) {
            return find(root, str, 0);
        }
    private:
        Node* insert(Node* node, string str, int index) {
            if (node == nullptr) node = new Node();
            if (index == str.length()) {
                node->isEnd = true;
                return node;
            }
            node->children[str[index]] = insert(node->children[str[index]], str, index + 1);

            return node;
        }
        bool find(Node* root, string str, int index) {
            if (!root) return false;
            if (index == str.length()) return root->isEnd;

            return find(root->children[str[index]], str, index + 1);
        }
    };
public:
    static void test() {
        MakePalinFromGivenWords obj;
        vector<string> words = { "bat","cat","tab","rat" };
        auto res = obj.findWords(words);
        cout << res << endl;
    }

    string findWords(vector<string>& words) {
        Trie trie;
        for (auto& word : words) {
            if (!trie.find(word)) {
                auto tmp = word;
                reverse(tmp.begin(), tmp.end());
                trie.insert(tmp);
            }
            else {
                return word;
            }
        }
        return string();
    }
};