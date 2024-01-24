#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

class DllNode {
public:
    string val;
    DllNode* prev = nullptr, * next = nullptr;

    DllNode(string val) : val(val) {}
    DllNode(string val, DllNode* prev, DllNode* next) : val(val), prev(prev), next(next) {}
};
class Dll
{
private:
    DllNode* root = nullptr;
    DllNode* leaf = nullptr;
public:
    DllNode* front() { if (root) return root; else return nullptr; }
    DllNode* push_front(const char* str) {
        string s(str);
        DllNode* tmp = new DllNode(s, nullptr, root);
        if (root != nullptr) root->prev = tmp;
        root = tmp;
        if (leaf == nullptr) leaf = root;

        return tmp;
    }
    DllNode* push_back(const char* str) {
        string s(str);
        DllNode* tmp = new DllNode(s, leaf, nullptr);
        if (leaf != nullptr) leaf->next = tmp;
        if (root == nullptr) root = tmp;
        leaf = tmp;

        return tmp;
    }

    void erase(DllNode* node) {
        if (node) {
            DllNode* p = node->prev;
            DllNode* n = node->next;

            delete node;
            if (p == nullptr) root = n;
            else p->next = n;
            if (n == nullptr) leaf = p;
            else n->prev = p;
        }
    }
};

class TrieNode {
public:
    TrieNode* children[128] = { nullptr };
    bool end = false;
    bool duplicate = false;
    DllNode* node = nullptr;

    TrieNode() {
        for (int i = 0; i < 128; i++) children[i] = nullptr;
    }
};
class Trie
{
private:
    TrieNode* root = nullptr;
    Dll* dll = nullptr;

public:
    Trie(Dll* dll) {
        this->dll = dll;
        root = new TrieNode();
    }

    void insert(const char* str) {
        TrieNode* tmp = root;
        const char* org = str;
        if (*str == '\0') return;
        while (*(str + 1) != '\0') {
            if (tmp->children[*str] == nullptr) tmp->children[*str] = new TrieNode();
            tmp = tmp->children[*str];
            str++;
        }

        if (tmp->children[*str] != nullptr) {
            tmp = tmp->children[*str];
            tmp->end = true;
            tmp->duplicate = true;

            dll->erase(tmp->node);
            tmp->node = nullptr;
        }
        else {
            tmp->children[*str] = new TrieNode();
            tmp = tmp->children[*str];
            tmp->end = true;
            tmp->node = dll->push_back(org);
        }
    }
};

class UniqueUrlFinder
{
private:
    Trie* root = nullptr;
    Dll* dll = nullptr;

public:
    UniqueUrlFinder() {
        dll = new Dll();
        root = new Trie(dll);
    }
    void insert(string url) { root->insert(url.c_str()); }
    string get() { return dll->front()->val; }
};
void tester()
{
    UniqueUrlFinder urlFinder;
    list<string> l = {
        "http://www.geeksforgeeks.com",
        "http://www.google.com",
        "http://www.google.com",
        "http://www.yahoo.com",
        "http://www.geeksforgeeks.com",
        "http://www.google.com",
        "http://www.msn.com",
        "http://www.microsoft.com",
        "http://www.amazon.com",
        "http://www.yahoo.com",
        "http://www.amazon.com",
        "http://www.msn.com"
    };
    for (auto u : l) {
        //cout << "Inserting Url = " << u.c_str() << endl;
        urlFinder.insert(u);
        cout << "First Unique URL = " << urlFinder.get() << endl;
    }
}