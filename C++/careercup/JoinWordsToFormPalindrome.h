#include "../header.h"

/*
https://www.careercup.com/question?id=4879869638868992

You are given a list of word. Find if two words can be joined to-gather to form a palindrome. eg Consider a list {bat, tab, cat} Then bat and tab can be joined to gather to form a palindrome.

Expecting a O(nk) solution where n = number of works and k is length

There can be multiple pairs
*/
class JoinWordsToFormPalindrome {
    class Trie {
       public:
        struct Node {
            bool end = false;
            unordered_map<char, Node*> children;
        };

        Node* root = new Node();

        void insert(string word) {
            root = insert(root, word, 0);
        }

        bool find(string word) {
            return find(root, word, 0);
        }

        bool isPrefix(string word, vector<string>& words) {
            return isPrefix(root, word, 0, words);
        }

       private:
        Node* insert(Node* node, string word, int index) {
            if (!node) node = new Node();
            if (index == word.size()) {
                node->end = true;
                return node;
            }

            node->children[word[index]] = insert(node->children[word[index]], word, index + 1);

            return node;
        }

        bool find(Node* node, string word, int index) {
            if (!node) return false;
            if (index == word.size()) return node->end;

            return find(node->children[word[index]], word, index + 1);
        }

        bool isPrefix(Node* node, string word, int index, vector<string>& words) {
            if (!node) return false;
            if (index == word.size()) {
                populateSuffixes(node, "", words);
                return true;
            }
            return isPrefix(node->children[word[index]], word, index + 1, words);
        }

        void populateSuffixes(Node* node, string cur, vector<string>& words) {
            if (!node) return;
            if (node->end) words.push_back(cur);

            for (auto child : node->children) {
                populateSuffixes(child.second, cur + child.first, words);
            }
        }
    };

   public:
    static void test() {
        JoinWordsToFormPalindrome obj;
        vector<vector<string>> inputs = {
            {"bat", "tab", "cat"},
            {"hellol", "leh", "hellow", "wol"},
            {"loh", "hello", "lleh"},
            {"helloword", "hellolle", "h"}};
        for (auto& input : inputs) {
            auto res = obj.findWords(input);
            cout << res << endl;

            auto word = res[0] + res[1];
            assert(obj.isPalin(word));
        }
    }

    vector<string> findWords(vector<string>& input) {
        Trie forwardTrie, reverseTrie;

        for (auto word : input) {
            string rev = word;
            reverse(rev.begin(), rev.end());

            if (forwardTrie.find(rev)) return {word, rev};
            if (reverseTrie.find(word)) return {rev, word};

            vector<string> suffixes;
            if (forwardTrie.isPrefix(rev, suffixes)) {
                for (auto suffix : suffixes) {
                    if (isPalin(suffix)) return {rev + suffix, word};
                }
            }

            suffixes.clear();
            if (reverseTrie.isPrefix(word, suffixes)) {
                for (auto suffix : suffixes) {
                    if (isPalin(suffix)) return {word + suffix, rev};
                }
            }

            forwardTrie.insert(word);
            reverseTrie.insert(rev);
        }

        return {};
    }

    bool isPalin(string word) {
        int l = 0, r = word.size() - 1;
        while (l < r && word[l] == word[r]) {
            l++;
            r--;
        }

        return l >= r;
    }
};