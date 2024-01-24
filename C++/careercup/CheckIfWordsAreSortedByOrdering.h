#include "../header.h"

class CheckIfWordsAreSortedByOrdering {
   public:
    static void test() {
        CheckIfWordsAreSortedByOrdering obj;
        vector<string> words = {"bb", "cc", "ac", "cb"};
        vector<char> order = {'c', 'b', 'a'};

        auto res = obj.isSorted(words, order);
        if (res) cout << format("1. words={} are sorted by order={}.", to_string(words), to_string(order)) << endl;

        obj.sortWordsWithGivenOrder(words, order);
        cout << format("2. words={} are sorted by order={}.", to_string(words), to_string(order)) << endl;
    }

    bool isSorted(vector<string>& strs, vector<char>& order) {
        unordered_map<char, int> map;
        for (int i = 0; i < order.size(); i++) map[order[i]] = i;

        for (int i = 1; i < strs.size(); i++) {
            auto prev = strs[i - 1];
            auto cur = strs[i];
            int j = 0, k = 0;
            for (; j < prev.length() && k < cur.length(); j++, k++) {
                if (prev[j] != cur[k]) break;
            }
            if (map[prev[j]] > map[cur[k]]) return false;
        }

        return true;
    }

    void sortWordsWithGivenOrder(vector<string>& strs, vector<char>& order) {
        unordered_map<char, int> map;
        for (int i = 0; i < order.size(); i++) map[order[i]] = i;
        sort(strs.begin(), strs.end(), [&](auto& word1, auto& word2) {
            int i = 0, j = 0;
            for (; i < word1.size() && j < word2.size(); i++, j++) {
                if (word1[i] != word2[j]) break;
            }

            return map[word1[i]] < map[word2[j]];
        });
    }

    static string to_string(vector<string>& strs) {
        stringstream ss;
        for (auto& str : strs) {
            ss << str << " ";
        }

        return ss.str();
    }

    static string to_string(vector<char>& order) {
        stringstream ss;
        for (auto& ch : order) {
            ss << ch << " ";
        }

        return ss.str();
    }
};