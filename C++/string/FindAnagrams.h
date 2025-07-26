#pragma once
#include "../header.h"

/**
 * @class FindAnagrams
 * @brief Groups words that are anagrams of each other using a hash-based approach.
 *
 * Two strings are anagrams if they contain the same characters in the same frequency,
 * but possibly in a different order.
 *
 * Example:
 *   Input:  {"bat", "tab", "cat", "act", "tac"}
 *   Output:
 *       1 : bat tab
 *       2 : cat act tac
 *
 * This implementation uses a simple hashing method where the key
 * is derived from the frequency of characters in each word.
 */
class FindAnagrams {
   public:
    /**
     * @brief Test driver for the anagram grouping function.
     *
     * @param strs Vector of input strings to group.
     *
     * Example Output:
     * ```
     * 1685235349872345 : bat tab
     * 2847593456283643 : cat act tac
     * ```
     */
    static void test(const vector<string>& strs) {
        FindAnagrams obj;
        auto res = obj.calculateUsingSorting(strs);

        cout << "Grouped Anagrams:" << endl;
        for (const auto& [key, group] : res) {
            cout << key << " : ";
            for (const auto& s : group) cout << s << " ";
            cout << endl;
        }
    }

   public:
    unordered_map<string, vector<string>> calculateUsingSorting(const vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (auto& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }

        return groups;
    }

   public:
    unordered_map<string, vector<string>> calculateUsingCharCount(const vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (auto& s : strs) {
            array<int, 26> count = {0};
            for (char c : s) count[c - 'a']++;

            string key;
            for (int c : count) key += "#" + to_string(c);

            groups[key].push_back(s);
        }

        return groups;
    }

   public:
    unordered_map<unsigned long long, vector<string>> calculateUsingPrimesHash(const vector<string>& strs) {
        unordered_map<unsigned long long, vector<string>> groups;

        vector<int> primes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
            31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
            73, 79, 83, 89, 97, 101};

        for (auto& s : strs) {
            unsigned long long hashVal = 1;
            for (char c : s) hashVal *= primes[c - 'a'];

            groups[hashVal].push_back(s);
        }

        return groups;
    }

   public:
    /**
     * @brief Groups input strings by their hash (representing anagram equivalence).
     *
     * @param strs List of input strings.
     * @return Vector of pairs, where each pair contains:
     *         (hash_value, list_of_anagrams)
     *
     * ### Algorithm:
     *  1. For each string, compute a hash value based on its character frequencies.
     *  2. If the hash already exists, append to that anagram group.
     *  3. Otherwise, start a new group.
     *
     * ### Time Complexity:
     * O(n * m) — where n = number of strings, m = length of longest string.
     *
     * ### Space Complexity:
     * O(n) for storing groups.
     */
    unordered_map<unsigned long long, vector<string>> calculateUsingHash(const vector<string>& strs) {
        unordered_map<unsigned long long, vector<string>> res;

        for (const auto& s : strs) {
            unsigned long long h = computeHash(s);
            res[h].push_back(s);
        }

        return res;
    }

    /**
     * @brief Computes a simple polynomial rolling hash for a given string.
     *
     * @param str Input string.
     * @return Unsigned long long hash value.
     *
     * ⚠️ Note: This is a custom hash (not cryptographically safe).
     *          It works reasonably well for short alphabetic strings.
     */
    unsigned long long computeHash(const string& str) {
        const unsigned long long base = 257;
        const unsigned long long mod = 1e9 + 9;

        // Sort string to make it order-independent for anagrams
        string sorted = str;
        sort(sorted.begin(), sorted.end());

        unsigned long long hash = 0;
        for (char ch : sorted) {
            hash = (hash * base + static_cast<unsigned long long>(ch)) % mod;
        }

        return hash;
    }

    /**
     * @brief Demonstrates standard library hash usage for debugging.
     *
     * @param input Input string.
     * @return Computed hash value.
     *
     * Example:
     * ```
     * Hash of string: bat is 142384872394872394
     * ```
     */
    size_t calculateHash(const string& input) {
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(input);
        cout << "Hash of string: " << input << " = " << hash_value << endl;
        return hash_value;
    }
};