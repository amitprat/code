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
#include <cassert>
#include <algorithm>
using namespace std;

template <class T>
class Node
{
public:
    unordered_map<char, Node<T>*> children;
    bool end = false;

    Node()
    {
        end = false;
    }
};

class MemoryEfficientTrie
{
private:
    Node<char>* root = nullptr;

    int index(char ch) {
        return ch - 'a';
    }

    char getchar(int i) { return i + 'a'; }

    bool isleaf(Node<char>* node)
    {
        if (node == nullptr) return true;
        return node->children.empty();
    }

    static string TO_BOOL(int result) {
        return result == 0 ? "False" : "True";
    }
public:
    static void test()
    {
        MemoryEfficientTrie trie;

        string word = "helloworld";
        cout << "Insert => Word: " << word << endl;
        trie.insert(word);

        cout << "Traverse => ";
        auto result = trie.traverse();
        for (auto& str : result) cout << str << " ";
        cout << endl;
        auto expected = { "helloworld" };
        assert(equal(result.begin(), result.end(), expected.begin()));

        word = "hello";
        cout << "Search => Word: '" << word << "' exists in trie: " << TO_BOOL(trie.search(word)) << endl;
        assert(trie.search(word) == 0);

        word = "invalid";
        cout << "Search => Word: '" << word << "' exists in trie: " << TO_BOOL(trie.search(word)) << endl;
        assert(trie.search(word) == 0);

        word = "helloworld";
        cout << "Search => Word: '" << word << "' exists in trie: " << TO_BOOL(trie.search(word)) << endl;
        assert(trie.search(word) == 1);

        word = "hell";
        cout << "Insert => Word: " << word << endl;
        trie.insert(word);

        word = "hello";
        cout << "Insert => Word: " << word << endl;
        trie.insert(word);

        word = "he";
        cout << "StartsWith => all words starting with word: '" << word << "': ";
        result = trie.startsWith(word);
        for (auto& str : result) cout << str << " ";
        cout << endl;
        expected = { "hell", "hello", "helloworld" };
        assert(equal(result.begin(), result.end(), expected.begin()));

        word = "helloworldstart";
        cout << "LongestPrefix => word starting with word: '" << word << "': ";
        result = trie.longestPrefix(word);
        for (auto& str : result) cout << str << " ";
        cout << endl;
        expected = { "hell", "hello", "helloworld" };
        assert(equal(result.begin(), result.end(), expected.begin()));

        word = "hell";
        cout << "Delete => Word: " << word << endl;
        bool res = trie.deleteWord(word);

        word = "he";
        cout << "StartsWith => all words starting with word: '" << word << "': ";
        result = trie.startsWith(word);
        for (auto& str : result) cout << str << " ";
        cout << endl;
        expected = { "hello", "helloworld" };
        assert(equal(result.begin(), result.end(), expected.begin()));

        word = "helloworld";
        cout << "Delete => Word: " << word << endl;
        res = trie.deleteWord(word);

        word = "he";
        cout << "StartsWith => all words starting with word: '" << word << "': ";
        result = trie.startsWith(word);
        for (auto& str : result) cout << str << " ";
        cout << endl;
        expected = { "hello" };
        assert(equal(result.begin(), result.end(), expected.begin()));
    }

    /*
    Insert given word in trie
    */
    void insert(string word)
    {
        root = insert(root, word.c_str());
    }

    /*
    Return all words in trie
    */
    vector<string> traverse()
    {
        vector<string> result;
        traverse(root, result, "");
        return result;
    }

    /*
    Check for given word in trie
    */
    bool search(string word)
    {
        if (root == nullptr) return false;
        if (word.empty()) return root->end;

        const char* charArr = word.c_str();
        return search(root->children[index(*charArr)], charArr + 1);
    }

    /*
    Delete given word from trie
    */
    bool deleteWord(string word)
    {
        auto res = deleteWord(root, word.c_str());
        if (res && isleaf(root)) { delete root; root = nullptr; }
        return res;
    }

    /*
    Return all words starting with given word
    */
    vector<string> startsWith(string start)
    {
        vector<string> result;
        startsWith(root, start.c_str(), result, "");
        return result;
    }

    /*
    Get all words within the given word
    */
    vector<string> longestPrefix(string word) {
        vector<string> result;
        longestPrefixMatching(root, word.c_str(), result, "");
        return result;
    }

private:
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

    bool search(Node<char>* node, const char* word)
    {
        if (node == nullptr) return false;
        if (!*word) return node->end;

        return search(node->children[index(*word)], word + 1);
    }

    void traverse(Node<char>* node, vector<string>& result, string str)
    {
        if (node == nullptr) return;
        if (node->end) { result.push_back(str); }
        for (auto& child : node->children) {
            traverse(child.second, result, str + getchar(child.first));
        }
    }

    void startsWith(Node<char>* node, const char* word, vector<string>& result, string str)
    {
        if (node == nullptr) return;
        if (node->end) { result.push_back(str); }
        if (*word) startsWith(node->children[index(*word)], word + 1, result, str + *word);
        else
        {
            for (auto& child : node->children) {
                startsWith(child.second, word, result, str + getchar(child.first));
            }
        }
    }

    void longestPrefixMatching(Node<char>* node, const char* word, vector<string>& result, string str)
    {
        if (node == nullptr) return;
        if (node->end) result.push_back(str);
        if (!*word) return;

        longestPrefixMatching(node->children[index(*word)], word + 1, result, str + *word);
    }

    bool deleteWord(Node<char>* node, const char* word)
    {
        if (node == nullptr) return false;
        if (!*word) {
            node->end = false;
            return node->end && isleaf(node);
        }

        bool res = deleteWord(node->children[index(*word)], word + 1);
        if (res) {
            delete node->children[index(*word)];
            node->children[index(*word)] = nullptr;
        }
        return res && isleaf(node);
    }
};