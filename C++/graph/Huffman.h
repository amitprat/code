#pragma once
#include "../header.h"
using namespace std;

class Node
{
public:
    char val;
    int freq;
    Node* left, * right;

    Node(int val, char freq, Node* left = nullptr, Node* right = nullptr) : val(val), freq(freq), left(left), right(right) {}
};

template <class T>
class Maxheap
{
private:
    vector<Node*> nodes;
    int sz = 0;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void upHeapify(int c)
    {
        int p = parent(c);
        while (c != 0 && nodes[p]->freq < nodes[c]->freq) {
            swap(nodes[p], nodes[c]);
            c = p;
            p = parent(c);
        }
    }

    void downHeapify(int i)
    {
        int largest = i;
        int l = left(i);
        if (l < sz && nodes[l]->freq > nodes[largest]->freq) largest = l;

        int r = right(i);
        if (r < sz && nodes[r]->freq > nodes[largest]->freq) largest = r;

        if (largest != i) {
            swap(nodes[i], nodes[largest]);
            downHeapify(largest);
        }
    }

public:
    void add(Node* n)
    {
        nodes.push_back(n);
        sz++;
        upHeapify(sz - 1);
    }

    Node* pop()
    {
        Node* top = nodes.front();
        nodes[0] = nodes[sz - 1];
        sz--;
        nodes.pop_back();
        downHeapify(0);

        return top;
    }

    int size() { return sz; }
};

template <class T>
class Minheap
{
private:
    vector<Node*> nodes;
    int sz = 0;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void upHeapify(int c)
    {
        int p = parent(c);
        while (c != 0 && nodes[p]->freq > nodes[c]->freq) {
            swap(nodes[p], nodes[c]);
            c = p;
            p = parent(c);
        }
    }

    void downHeapify(int i)
    {
        int smallest = i;
        int l = left(i);
        if (l < sz && nodes[l]->freq < nodes[smallest]->freq) smallest = l;

        int r = right(i);
        if (r < sz && nodes[r]->freq < nodes[smallest]->freq) smallest = r;

        if (smallest != i) {
            swap(nodes[i], nodes[smallest]);
            downHeapify(smallest);
        }
    }

public:
    void add(Node* n)
    {
        nodes.push_back(n);
        sz++;
        upHeapify(sz - 1);
    }

    Node* pop()
    {
        Node* top = nodes.front();
        nodes[0] = nodes[sz - 1];
        sz--;
        nodes.pop_back();
        downHeapify(0);

        return top;
    }

    int size() { return sz; }
};

class Huffman
{
public:
    void test()
    {
        vector<vector<pair<char, int>>> strs =
        {
            {{'a',5}, {'b',9},{'c',12},{'d',13},{'e',16},{'f',45}}
        };
        for (auto s : strs)
        {
            stringstream ss;
            ss << "Input: {";
            for (auto j : s) {
                ss << "(" << j.first << ", " << j.second << "), ";
            }
            ss.seekp(-2, ss.cur);
            ss << "}\n";
            //cout << ss.str();
            ss.clear();
            vector<pair<char, string>> codes = huffman(s);

            ss << "Codes: {";
            for (auto i : codes) {
                ss << "(" << i.first << ": " << i.second << "), ";
            }
            ss.seekp(-2, ss.cur);
            ss << "}\n";
            cout << ss.str();
        }
    }

    vector<pair<char, string>> huffman(vector<pair<char, int>> input)
    {
        Minheap<Node> heap;
        vector<pair<char, string>> result;
        for (auto i : input) heap.add(new Node(i.first, i.second));

        while (heap.size() >= 2)
        {
            Node* f = heap.pop();
            Node* s = heap.pop();
            Node* newNode = new Node('$', f->freq + s->freq, f, s);
            heap.add(newNode);
        }

        Node* root = heap.pop();
        traverse(root, result, string());

        return result;
    }

    void traverse(Node* root, vector<pair<char, string>>& result, string str)
    {
        if (root == nullptr) return;

        if (root->left) {
            traverse(root->left, result, str + "0");
        }

        if (root->right) {
            traverse(root->right, result, str + "1");
        }

        if (root->val != '$') {
            result.push_back({ root->val, str });
        }
    }
};