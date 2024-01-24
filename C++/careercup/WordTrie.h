#pragma once
#include "../Header.h"

class WordTrie {
    struct Node {
        bool isStar;
        unordered_map<string, Node*> children;
        Node(bool isStar = false) :isStar(isStar) {}
    };
    Node* root = nullptr;
public:
    static void test() {
        WordTrie obj;
        vector<string> words = {
            "c.name","c.age","c.location.*","c.dept"
        };
        vector<string> inputs = {
            "c.name","c.location.home","c.location.work","d.name","c.hello","c.department",
            "c.location.home.city","c.location.home.pincode"
        };
        obj.init(words);
        for (auto input : inputs) {
            cout << input << " match ? " << obj.isMatch(input) << endl;
        }
    }

    WordTrie() {
        root = new Node();
    }

    void init(vector<string> words) {
        for (auto word : words) {
            auto parts = split(word, '.');
            root = insert(root, parts, 0);
        }
    }

    bool isMatch(string input) {
        auto parts = split(input, '.');
        return isMatch(root, parts, 0);
    }

private:
    Node* insert(Node* cur, vector<string> parts, int pos) {
        if (pos == parts.size()) return nullptr;
        if (cur->children.find(parts[pos]) == cur->children.end()) {
            cur->children.insert({ parts[pos], new Node() });
            if (parts[pos] == "*") cur->isStar = true;
        }
        cur->children[parts[pos]] = insert(cur->children[parts[pos]], parts, pos + 1);
        return cur;
    }
    bool isMatch(Node* cur, vector<string> parts, int pos) {
        if (pos == parts.size()) return true;
        if (cur->children.find(parts[pos]) == cur->children.end()) {
            if (cur->isStar) return isMatch(cur, parts, pos + 1);
            return false;
        }
        return isMatch(cur->children[parts[pos]], parts, pos + 1);
    }
    vector<string> split(string word, char delim) {
        vector<string> result;
        size_t pos = 0;
        do {
            auto cur = word.find(delim, pos);
            if (cur == string::npos) {
                result.push_back(word.substr(pos)); break;
            }
            else result.push_back(word.substr(pos, cur - pos));
            pos = cur + 1;
        } while (pos != string::npos);
        return result;
    }
};