#pragma once
#include "../Header.h"

class HuffmanEncodingDecoding {
    struct Node {
        char ch;
        Node* left = nullptr, * right = nullptr;
        Node(char ch) :ch(ch) {}
    };
public:
    static void test() {
        string str = "geeksforgeeks";

        unordered_map<char, string> codes;
        string encodedString = encode(str, codes);

        cout << "codes = " << to_string(codes) << endl;
        cout << "Encoded string = " << encodedString << endl;

        string res = decode(codes, encodedString);
        cout << "Decoded string = " << res << endl;
    }

    static string encode(string str, unordered_map<char, string>& codes)
    {
        unordered_map<char, int> freqMap;
        for (auto ch : str) freqMap[ch]++;

        // use minheap, character with smallest freq gets extract first and result in longest path to leaf node
        // this gives smallest code for most repeated char and vice-versa
        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> pq;
        for (auto e : freqMap) pq.push({ e.second, new Node(e.first) });

        while (pq.size() > 1) {
            // order doesn't matter (any node can be left or right as long as it is consistent i.e. the node with high freq is either always left or right)
            auto right = pq.top(); pq.pop();
            auto left = pq.top(); pq.pop();

            // insert an internal node (char is always on leaf node, $ are leaf nodes)
            auto* parent = new Node('$');
            parent->left = left.second;
            parent->right = right.second;

            pq.push({ left.first + right.first, parent });
        }

        auto* root = pq.top().second;

        // populate codes for each character
        traverseTree(root, "", codes);

        // encode string using assigned code for each character
        string encodedStr;
        for (auto ch : str) {
            encodedStr += codes[ch];
        }

        return encodedStr;
    }

    static void traverseTree(Node* root, string str, unordered_map<char, string>& codes) {
        if (!root) return;
        if (root->ch != '$') {
            codes[root->ch] = str;
            return;
        }

        traverseTree(root->left, str + "0", codes);
        traverseTree(root->right, str + "1", codes);
    }

    static string decode(unordered_map<char, string> codes, string encodedStr) {
        string result;
        string cur;

        unordered_map<string, char> revCodeMap;
        for (auto e : codes) revCodeMap[e.second] = e.first;

        for (char ch : encodedStr) {
            cur += ch;
            if (revCodeMap.find(cur) != revCodeMap.end()) {
                result += revCodeMap[cur];
                cur = "";
            }
        }

        return result;
    }
};