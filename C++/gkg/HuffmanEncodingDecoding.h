#pragma once
#include "../Header.h"

class HuffmanEncodingDecoding {
    class Node {
    public:
        char ch;
        int freq;
        Node* left = nullptr;
        Node* right = nullptr;
        Node() {}
        Node(char ch, int freq) :ch(ch), freq(freq), left(nullptr), right(nullptr) {}
    };

    class Minheap {
    public:
        vector<Node*> nodes;

        void insert(char ch, int freq) {
            Node* newnode = new Node(ch, freq);
            nodes.push_back(newnode);

            upHeapify(nodes.size() - 1);
        }

        void insert(Node* node) {
            nodes.push_back(node);
            upHeapify(nodes.size() - 1);
        }

        void upHeapify(int pos) {
            int p = parent(pos);
            while (pos != 0 && nodes[pos]->freq < nodes[p]->freq) {
                swap(nodes[p], nodes[pos]);
                pos = p;
                p = parent(pos);
            }
        }

        Node* pop() {
            if (empty()) return nullptr;
            Node* top = nodes[0];
            nodes[0] = nodes[nodes.size() - 1];
            nodes.pop_back();

            downHeapify(0);

            return top;
        }

        void downHeapify(int pos) {
            int mn = pos;
            int l = left(pos);
            if (l < nodes.size() && nodes[l]->freq < nodes[mn]->freq) mn = l;

            int r = right(pos);
            if (r < nodes.size() && nodes[r]->freq < nodes[mn]->freq) mn = r;

            if (pos != mn) {
                swap(nodes[pos], nodes[mn]);

                downHeapify(mn);
            }
        }

        int size() {
            return nodes.size();
        }

        bool empty() {
            return nodes.empty();
        }

        int left(int pos) {
            return 2 * pos + 1;
        }

        int right(int pos) {
            return 2 * pos + 2;
        }

        int parent(int pos) {
            return pos / 2;
        }
    };
public:
    static void test() {
        HuffmanEncodingDecoding obj;
        string str = "Huffman coding is a data compression algorithm.";

        auto codes = obj.getCodes(str);
        cout << "\nCodes : " << to_string(codes) << endl;

        auto endocoded = obj.encode(str, codes);
        cout << "\nEncoded string: " << endocoded << endl;

        auto decoded = obj.decode(endocoded, codes);
        cout << "\nDecoded string: " << decoded << endl;
    }

    unordered_map<char, string> getCodes(string largeText) {
        unordered_map<char, int> freqMap;
        for (auto ch : largeText) {
            freqMap[ch]++;
        }

        for (auto e : freqMap) {
            cout << e.first << ":" << e.second << endl;
        }

        Minheap mh;
        for (auto e : freqMap) {
            mh.insert(e.first, e.second);
        }

        while (mh.size() != 1) {
            auto* f = mh.pop();
            auto* s = mh.pop();

            Node* newnode = new Node('$', f->freq + s->freq);
            newnode->left = f;
            newnode->right = s;

            mh.insert(newnode);
        }

        unordered_map<char, string> codes;
        traverse(mh.pop(), codes, "");

        return codes;
    }

    void traverse(Node* root, unordered_map<char, string>& codes, string cur) {
        if (!root) return;
        if (root->left == nullptr && root->right == nullptr) {
            codes.insert({ root->ch, cur });
            return;
        }

        traverse(root->left, codes, cur + "0");
        traverse(root->right, codes, cur + "1");
    }

    string encode(string str, unordered_map<char, string>& codes) {
        string result;

        for (auto ch : str) {
            result += codes[ch];
        }

        return result;
    }

    string decode(string encodedStr, unordered_map<char, string>& codes) {
        unordered_map<string, char> revMap;
        for (auto e : codes) revMap[e.second] = e.first;

        string cur;
        string result;
        for (auto ch : encodedStr) {
            cur += ch;
            if (revMap.find(cur) != revMap.end()) {
                result += revMap[cur];
                cur = "";
            }
        }

        return result;
    }
};