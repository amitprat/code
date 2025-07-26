#pragma once
#include "../header.h"

/**
 * @class LongestWordMadeOfOthers
 * @brief Finds the longest word that can be constructed entirely from other words in the list.
 *
 * Example:
 *   Input: ["rat","cat","ratcat","ratcatabc"]
 *   Output: "ratcat" or "ratcatabc" depending on list
 */
class LongestWordMadeOfOthers {
    // ----------------- Trie Node -----------------
    struct Node {
        bool isEnd = false;
        unordered_map<char, Node*> children;
    };

    // ----------------- Trie -----------------
    class Trie {
        Node* root = new Node();

       public:
        // Insert a word into the trie
        void insert(const string& str) {
            Node* curr = root;
            for (char c : str) {
                if (!curr->children[c]) curr->children[c] = new Node();
                curr = curr->children[c];
            }
            curr->isEnd = true;
        }

        // Check if a word can be formed by other words in the trie
        bool canFormWord(const string& word, int index = 0, int count = 0) {
            Node* curr = root;
            int n = word.size();
            for (int i = index; i < n; i++) {
                char c = word[i];
                if (!curr->children[c]) return false;
                curr = curr->children[c];
                if (curr->isEnd) {
                    if (i == n - 1) return count >= 1;  // at least 2 words
                    if (canFormWord(word, i + 1, count + 1)) return true;
                }
            }
            return false;
        }
    };

   public:
    // ----------------- Test -----------------
    static void test() {
        LongestWordMadeOfOthers obj;
        vector<string> strs = {"rat", "cat", "ratcat", "abc", "xyz", "abcxyz", "ratcatabc", "xyzcatratabc"};

        // Using HashSet + Backtracking
        vector<string> res;
        auto longest = obj.findLongestWord(strs, res);
        cout << "Longest word (backtracking) = " << longest << endl;
        cout << "Combination used: ";
        for (auto& w : res) cout << w << " ";
        cout << endl;

        // Using Trie
        auto trieLongest = obj.findLongestWordTrie(strs);
        cout << "Longest word (Trie) = " << trieLongest << endl;
    }

    // ----------------- Backtracking + HashSet -----------------
    string findLongestWord(vector<string>& strs, vector<string>& res) {
        // Sort words by length descending
        sort(strs.begin(), strs.end(), [](const auto& a, const auto& b) { return a.size() > b.size(); });
        unordered_set<string> dict(strs.begin(), strs.end());

        for (auto& word : strs) {
            res.clear();
            if (isMadeOfOthers(word, res, dict)) return word;
        }
        return "";
    }

    bool isMadeOfOthers(const string& word, vector<string>& path, const unordered_set<string>& dict) {
        if (word.empty()) return true;
        for (int len = 1; len <= word.size(); len++) {
            string prefix = word.substr(0, len);
            string rest = word.substr(len);
            if (dict.find(prefix) != dict.end()) {
                path.push_back(prefix);
                if (rest.empty() || isMadeOfOthers(rest, path, dict)) return true;
                path.pop_back();
            }
        }
        return false;
    }

    // ----------------- Trie Approach -----------------
    string findLongestWordTrie(vector<string>& strs) {
        Trie trie;
        for (auto& word : strs) trie.insert(word);

        string longest = "";
        for (auto& word : strs) {
            if (trie.canFormWord(word)) {
                if (word.size() > longest.size()) longest = word;
            }
        }
        return longest;
    }
};