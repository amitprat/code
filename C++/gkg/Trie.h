#pragma once
#include "../Header.h"

class TrieTest {
    class Trie {
        struct Node {
            unordered_map<char, Node*> children;
            bool end = false;
        };

        Node* root = new Node();
    public:
        void add(string str) {
            root = add(root, str, 0, str.size());
        }

        bool search(string str) {
            return search(root, str, 0, str.size());
        }

        void traverse() {
            traverse(root, "");
        }

        string longestPrefix(string str) {
            string mx;
            longestPrefix(root, str, 0, str.length(), "", mx);

            return mx;
        }

        void remove(string str) {
            root = remove(root, str, 0, str.size());
        }
    private:
        Node* add(Node* node, string str, int cur, int sz) {
            if (!node) node = new Node();
            if (cur == sz) {
                node->end = true;
                return node;
            }

            char ch = str[cur];
            node->children[ch] = add(node->children[ch], str, cur + 1, sz);

            return node;
        }

        Node* remove(Node* node, string str, int cur, int sz) {
            if (!node) return nullptr;
            if (cur == sz) {
                node->end = false;
                if (node->children.empty()) delete node;
                return nullptr;
            }

            char ch = str[cur];
            node->children[ch] = remove(node->children[ch], str, cur + 1, sz);
            if (node->children.empty() && !node->children.empty()) {
                delete node;
                node = nullptr;
            }

            return node;
        }

        bool search(Node* node, string str, int cur, int sz) {
            if (!node) return false;
            if (cur == sz) {
                return node->end;
            }

            char ch = str[cur];
            if (node->children.count(ch) == 0) return false;

            return search(node->children[ch], str, cur + 1, sz);
        }

        void traverse(Node* node, string str) {
            if (!node) return;
            if (node->end) {
                cout << str << " ";
                return;
            }

            for (auto child : node->children) {
                traverse(node, str + child.first);
            }
        }

        void longestPrefix(Node* node, string str, int cur, int sz, string res, string& mx) {
            if (!node) return;
            if (node->end) {
                if (res.length() > mx.length()) mx = res;
            }
            if (cur == sz) return;

            char ch = str[cur];
            if (node->children.count(ch) == 0) return;

            longestPrefix(node->children[ch], str, cur + 1, sz, res + ch, mx);
        }
    };
public:
    static void test() {
        Trie dict;
        dict.add("are");
        dict.add("area");
        dict.add("base");
        dict.add("cat");
        dict.add("cater");
        dict.add("basement");

        string input = "caterer";
        cout << "Longest prefix for " << input << " = " << dict.longestPrefix(input) << endl;

        dict.remove("cater");

        input = "caterer";
        cout << "Longest prefix for " << input << " = " << dict.longestPrefix(input) << endl;

        input = "basement";
        cout << "Longest prefix for " << input << " = " << dict.longestPrefix(input) << endl;

        input = "are";
        cout << "Longest prefix for " << input << " = " << dict.longestPrefix(input) << endl;

        input = "arex";
        cout << "Longest prefix for " << input << " = " << dict.longestPrefix(input) << endl;

        input = "basemexz";
        cout << "Longest prefix for " << input << " = " << dict.longestPrefix(input) << endl;

        input = "xyz";
        cout << "Longest prefix for " << input << " = " << dict.longestPrefix(input) << endl;

        cout << "Search word " << "base: " << to_string(dict.search("base")) << endl;
        cout << "Search word " << "bas: " << to_string(dict.search("bas")) << endl;
        cout << "Search word " << "cat: " << to_string(dict.search("cat")) << endl;
        cout << "Search word " << "cats: " << to_string(dict.search("cats")) << endl;
    }
};