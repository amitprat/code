/**
 * @file TrieWildCardSearch.h
 * @brief Implements a Trie that supports wildcard search with `*` (zero or more) and `.` (single) wildcards.
 */

#pragma once
#include "../header.h"

class TrieWildCardSearch {
   private:
    struct Node {
        bool end = false;
        unordered_map<char, Node*> children;
    };

    Node* root = new Node();

   public:
    /**
     * @brief Test the Trie with wildcard patterns and predefined words.
     */
    static void test() {
        TrieWildCardSearch trie;
        vector<string> words = {"car", "caw", "cauw", "cat", "cut", "cart", "cup"};

        for (const auto& word : words)
            trie.insert(word);

        vector<pair<string, vector<string>>> positive_tests = {
            {"c*", {"car", "caw", "cauw", "cat", "cut", "cart", "cup"}},
            {"c.t", {"cat", "cut"}},
            {"ca*", {"car", "caw", "cauw", "cat", "cart"}},
            {"cu*", {"cut", "cup"}},
            {"c..t", {"cart"}},
        };

        for (const auto& [pattern, expected] : positive_tests) {
            auto result = trie.search(pattern);
            sort(result.begin(), result.end());
            auto sorted_expected = expected;
            sort(sorted_expected.begin(), sorted_expected.end());
            assert(result == sorted_expected);

            result = trie.searchBFS(pattern);
            sort(result.begin(), result.end());
            assert(result == sorted_expected);

            cout << "[PASS] Pattern: " << pattern << " => " << to_string(result) << endl;
        }

        vector<string> negative_patterns = {
            "z*",     // No words starting with 'z'
            "..z",    // No word ending in 'z'
            "carz*",  // 'carz' prefix not present
            "c.tz",   // No such exact length + ending
            "....z"   // Too long + unmatched end
        };

        for (const auto& pattern : negative_patterns) {
            auto result = trie.search(pattern);
            assert(result.empty());

            result = trie.searchBFS(pattern);
            assert(result.empty());

            cout << "[PASS] Pattern: " << pattern << " => No matches" << endl;
        }
    }

    /**
     * @brief Inserts a word into the Trie.
     * @param word The word to be inserted.
     */
    void insert(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->children[ch]) {
                curr->children[ch] = new Node();
            }
            curr = curr->children[ch];
        }
        curr->end = true;
    }

    /**
     * @brief Inserts a word into the Trie using recursion.
     * @param word The word to be inserted.
     */
    void insertRecur(const string& word) {
        root = insertRecur(root, word, 0, word.size());
    }

    /**
     * @brief Searches the Trie for words matching a pattern with wildcards.
     * @param pattern The wildcard pattern to search.
     * @return List of matched words.
     */
    vector<string> search(const string& pattern) const {
        vector<string> result;
        dfsSearch(root, pattern, 0, "", result);
        return result;
    }

   private:
    Node* insertRecur(Node* node, const string& word, int idx, int n) {
        if (!node) node = new Node();
        if (idx == n) {
            node->end = true;
            return node;
        }

        node->children[word[idx]] = insertRecur(node->children[word[idx]], word, idx + 1, n);

        return node;
    }

    void dfsSearch(Node* node, const string& pattern, int idx, string prefix, vector<string>& result) const {
        if (!node) return;
        if (idx == pattern.length()) {
            if (node->end) result.push_back(prefix);
            return;
        }

        char ch = pattern[idx];
        if (ch == '*') {
            // try skipping '*'
            dfsSearch(node, pattern, idx + 1, prefix, result);

            // try including all characters and without moving pat index
            for (const auto& [c, child] : node->children) {
                dfsSearch(child, pattern, idx, prefix + c, result);
            }
        } else if (ch == '.') {
            // match any character
            for (const auto& [c, child] : node->children) {
                dfsSearch(child, pattern, idx + 1, prefix + c, result);
            }
        } else {
            // matches character. (If not match, node will be null)
            dfsSearch(node->children[ch], pattern, idx + 1, prefix + ch, result);
        }
    }

   public:
    /**
     * @brief Alternative search using queue (BFS style).
     */
    vector<string> searchBFS(const string& pattern) const {
        vector<string> result;
        queue<tuple<Node*, int, string>> q;
        q.push({root, 0, ""});

        while (!q.empty()) {
            auto [node, idx, prefix] = q.front();
            q.pop();

            if (!node) continue;
            if (idx == pattern.size()) {
                if (node->end) result.push_back(prefix);
                continue;
            }

            char ch = pattern[idx];
            if (ch == '*') {
                q.push({node, idx + 1, prefix});
                for (const auto& [c, child] : node->children) {
                    q.push({child, idx, prefix + c});
                }
            } else if (ch == '.') {
                for (const auto& [c, child] : node->children) {
                    q.push({child, idx + 1, prefix + c});
                }
            } else {
                if (node->children.count(ch)) {
                    q.push({node->children.at(ch), idx + 1, prefix + ch});
                }
            }
        }

        return result;
    }
};