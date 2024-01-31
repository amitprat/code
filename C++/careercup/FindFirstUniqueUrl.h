#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=11856466
Given a very long list of URLs, find the first URL which is unique ( occurred exactly once ).
I gave a O(n) extra space and O(2n) time solution, but he was expecting O(n) time, one traversal.

you can solve this in O(n) using a combination of trie and linked list. The leaf node of a trie maintains a flag to record
duplicate urls and pointer to a node in a link list. If you encounter a new url, add a node to the head of the linked list
and set the pointer in the trie. Whenever you encounter a url that is already in the trie, if the flag is not set, then set
the flag, delete the node from the linked list and set pointer to null. If the flag is already set, then ignore and read the
next url.
After processing all the urls, the link list should only contain the unique urls and the node at the tail is the first unique
url from the list. For n urls, inserting urls into the trie in O(n) and link list operations are all constant time. The node
could just keep the index of the url in the list so that we don't have to store urls in the link list as well.
*/

class FindFirstUniqueUrl {
    class DllNode {
       public:
        string val;
        DllNode *prev = nullptr, *next = nullptr;

        DllNode(string val) : val(val) {}
        DllNode(string val, DllNode* prev, DllNode* next) : val(val), prev(prev), next(next) {}
    };
    class Dll {
       private:
        DllNode* root = nullptr;
        DllNode* leaf = nullptr;

       public:
        DllNode* front() {
            if (root)
                return root;
            else
                return nullptr;
        }
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

                if (p == nullptr)
                    root = n;
                else
                    p->next = n;

                if (n == nullptr)
                    leaf = p;
                else
                    n->prev = p;
            }
        }
    };

    class TrieNode {
       public:
        TrieNode* children[128] = {nullptr};
        bool end = false;
        bool duplicate = false;
        DllNode* node = nullptr;

        TrieNode() {
            for (int i = 0; i < 128; i++) children[i] = nullptr;
        }
    };
    class Trie {
       private:
        TrieNode* root = nullptr;
        Dll* dll = nullptr;

       public:
        Trie(Dll* dll) {
            this->dll = dll;
            root = new TrieNode();
        }

        void insert(const char* str) {
            if (*str == '\0') return;

            TrieNode* tmp = root;

            const char* org = str;
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
            } else {
                tmp->children[*str] = new TrieNode();
                tmp = tmp->children[*str];
                tmp->end = true;
                tmp->node = dll->push_back(org);
            }
        }
    };

   public:
    static void test() {
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
            "http://www.msn.com"};
        for (auto u : l) {
            cout << "Inserting Url = " << u.c_str() << endl;
            urlFinder.insert(u);
            cout << "First Unique URL = " << urlFinder.get() << endl;
            cout << endl;
        }
    }

   private:
    // main worker function
    class UniqueUrlFinder {
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
};

// Second method
class UniqueUrlFinderWithSTL {
    list<string> dll;
    unordered_map<string, list<string>::iterator> map;

   public:
    static void test() {
        UniqueUrlFinderWithSTL urlFinder;
        vector<string> urls = {
            "http://www.geeksforgeeks.com",
            "http://www.google.com",
            "http://www.google.com",
            "http://www.yahoo.com",
            "http://www.geeksforgeeks.com",
            "http://www.google.com",
            "http://www.microsoft.com",
            "http://www.amazon.com",
            "http://www.yahoo.com",
            "http://www.amazon.com",
            "http://www.msn.com",
            "http://www.microsoft.com"};

        for (const auto& url : urls) {
            cout << "Inserted url " << url << endl;
            urlFinder.insert(url);
            cout << "First Unique URL So Far = " << urlFinder.getFirstUniqueUrl() << endl;
        }
    }

   private:
    string getFirstUniqueUrl() {
        return dll.empty() ? "" : dll.front();
    }

    void insert(const string& str) {
        if (map.find(str) == map.end())  // this will add only unique urls.
        {
            dll.push_back(str);               // put the unique value in dll
            map[str] = std::prev(dll.end());  // set to reference to hashmap
        } else if (map[str] != dll.end())     // this check with filter out the urls which are already visited and marked duplicate.
        {
            dll.erase(map[str]);   // find the reference from map and remove it from dll
            map[str] = dll.end();  // set to null
        }
    }
};