#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int SIZE = 26;

template <class T>
class Node
{
public:
    Node<T>* children[SIZE];
    bool end = false;

    Node()
    {
        end = false;
        for (int i = 0; i < SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie
{
private:
    int index(char ch) {
        return ch - 'a';
    }

    char getchar(int i) { return i + 'a'; }

    bool isleaf(Node<char>* node)
    {
        if (node == nullptr) return true;
        for (int i = 0; i < SIZE; i++) {
            if (node->children[i] != nullptr) return false;
        }

        return true;
    }
public:
    static void test()
    {
        Trie trie;
        Node<char>* root = nullptr;
        root = trie.insert(root, "helloworld");

        trie.traverse(root); cout << endl;

        cout << trie.search(root, "hello") << endl;
        cout << trie.search(root, "invalid") << endl;
        cout << trie.search(root, "helloworld") << endl;

        root = trie.insert(root, "hell");
        root = trie.insert(root, "hello");

        trie.printMatching(root, "he"); cout << endl;
        trie.longestPrefixMatching(root, "helloworldstart"); cout << endl;

        bool res = trie.deleteNode(root, "hell");
        if (res && trie.isleaf(root)) { delete root; root = nullptr; }

        trie.printMatching(root, "he"); cout << endl;

        res = trie.deleteNode(root, "helloworld");
        if (res && trie.isleaf(root)) { delete root; root = nullptr; }

        trie.printMatching(root, "he"); cout << endl;
    }

    Node<char>* insert(Node<char>* node, const char* word)
    {
        if (node == nullptr) node = new Node<char>();
        if (!*word) {
            node->end = true;
            return node;
        }

        node->children[index(*word)] = insert(node->children[index(*word)], word + 1);

        return node;
    }

    void traverse(Node<char>* node, string str = "")
    {
        if (node == nullptr) return;
        if (node->end) { cout << str << " "; }
        for (int i = 0; i < SIZE; i++) {
            traverse(node->children[i], str + getchar(i));
        }
    }

    bool search(Node<char>* node, const char* word)
    {
        if (node == nullptr) return false;
        if (!*word) return node->end;

        return search(node->children[index(*word)], word + 1);
    }

    void printMatching(Node<char>* node, const char* word, string str = "")
    {
        if (node == nullptr) return;
        if (node->end) { cout << str << " "; }
        if (*word) printMatching(node->children[index(*word)], word + 1, str + *word);
        else
        {
            for (int i = 0; i < SIZE; i++) {
                printMatching(node->children[i], word, str + getchar(i));
            }
        }
    }

    void longestPrefixMatching(Node<char>* node, const char* word, string str = "")
    {
        if (node == nullptr) return;
        if (node->end) cout << str << " ";
        if (!*word) return;

        longestPrefixMatching(node->children[index(*word)], word + 1, str + *word);
    }

    bool deleteNode(Node<char>* node, const char* word)
    {
        if (node == nullptr) return false;
        if (!*word) {
            node->end = false;
            return node->end && isleaf(node);
        }

        bool res = deleteNode(node->children[index(*word)], word + 1);
        if (res) {
            delete node->children[index(*word)];
            node->children[index(*word)] = nullptr;
        }
        return res && isleaf(node);
    }
};