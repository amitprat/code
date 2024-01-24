#pragma once
#include "../header.h"

class HuffmanEncoding {
private:
    class Node {
    public:
        char data;
        int freq;
        Node* left, * right;
        Node(char data, int freq) :data(data), freq(freq), left(nullptr), right(nullptr) {}
    };
    class Compare {
    public:
        bool operator()(Node* first, Node* second) {
            return first->freq > second->freq;
        }
    };
    Node* root = nullptr;

public:
    static void test() {
        HuffmanEncoding obj;
        string str = "geeksforgeeks";

        cout << "Encodings: " << endl;
        auto codes = obj.encode(str);
        for (auto i : codes) cout << i.first << ":" << i.second << endl;

        string encodedStr;
        for (auto ch : str) {
            encodedStr += codes[ch];
        }
        cout << "Encoded string: " << encodedStr << endl;

        auto decodedStr = obj.decode(encodedStr);
        cout << "Decoded string: " << decodedStr << endl;
    }

    unordered_map<char, string> encode(string str) {
        priority_queue<Node*, vector<Node*>, Compare> pq;
        unordered_map<char, int> freq;
        for (auto& ch : str) {
            freq[ch]++;
        }
        for (auto f : freq) {
            pq.push(new Node(f.first, f.second));
        }

        root = generateTree(pq);

        unordered_map<char, string> out;
        getCodes(root, out);

        return out;
    }

    string decode(string str) {
        string res;
        auto* node = root;
        for (auto ch : str) {
            if (ch == '0') node = node->left;
            else node = node->right;
            if (isLeaf(node)) {
                res += node->data;
                node = root;
            }
        }
        return res;
    }

private:
    void getCodes(Node* root, unordered_map<char, string>& out, string cur = "") {
        if (isLeaf(root)) {
            out.insert({ root->data, cur });
            return;
        }
        if (root->left) getCodes(root->left, out, cur + "0");
        if (root->right) getCodes(root->right, out, cur + "1");
    }

    Node* generateTree(priority_queue<Node*, vector<Node*>, Compare> pq) {
        while (pq.size() != 1) {
            auto* left = pq.top(); pq.pop();
            auto* right = pq.top(); pq.pop();
            auto* node = new Node('$', left->freq + right->freq);
            node->left = left;
            node->right = right;
            pq.push(node);
        }
        return pq.top();
    }

    bool isLeaf(Node* root) {
        return root->left == nullptr && root->right == nullptr;
    }
};