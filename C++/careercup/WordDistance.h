// Problem: Word Distance
// -------------------------------------
// Given a sentence and two words, find the minimum number of words between the two words in the sentence.
// The words can appear multiple times. The result should reflect the closest distance between any two
// appearances of the given words.
// -------------------------------------
// Example:
// Input: "the quick the brown quick brown the frog", w1 = "quick", w2 = "frog"
// Output: 1

#pragma once
#include "../header.h"

class WordDistance {
public:
    static void test() {
        WordDistance obj;

        {
            const string s = "geeks for geeks contribute practice";
            const string w1 = "geeks";
            const string w2 = "practice";
            cout << "Distance = " << obj.distance(s, w1, w2) << endl;
            cout << "Distance (optimized) = " << obj.distanceOptimized2(s, w1, w2) << endl;
        }

        {
            const string s = "the quick the brown quick brown the frog";
            const string w1 = "quick";
            const string w2 = "frog";
            cout << "Distance = " << obj.distance(s, w1, w2) << endl;
            cout << "Distance (optimized) = " << obj.distanceOptimized2(s, w1, w2) << endl;
        }
    }

    /**
     * Brute-force approach to calculate minimum distance between two words.
     * Time Complexity: O(n)
     * Space Complexity: O(n) (for split storage)
     */
    int distance(const string& s, const string& w1, const string& w2) {
        const vector<string> parts = split(s, ' ');

        pair<int, int> minDist = {-1, -1};
        pair<int, int> current = {-1, -1};

        for (int index = 0; index < static_cast<int>(parts.size()); ++index) {
            if (parts[index] == w1) {
                current.first = index;
            }
            if (parts[index] == w2) {
                current.second = index;
            }

            if (current.first != -1 && current.second != -1) {
                if (minDist.first == -1 || abs(current.first - current.second) < abs(minDist.first - minDist.second)) {
                    minDist = current;
                }
            }
        }

        cout << "Path = ";
        for (int i = minDist.first; i <= minDist.second; ++i) {
            cout << parts[i] << " ";
        }
        cout << endl;

        return abs(minDist.second - minDist.first);
    }

    /**
     * Optimized one-pass distance calculation between two words.
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int distanceOptimized(const string& s, const string& w1, const string& w2) {
        int index1 = -1;
        int index2 = -1;
        int minDist = numeric_limits<int>::max();

        const auto parts = split(s, ' ');

        for (size_t i = 0; i < parts.size(); ++i) {
            if (parts[i] == w1) {
                index1 = static_cast<int>(i);
                if (index2 != -1) {
                    minDist = min(minDist, index1 - index2);
                }
            } else if (parts[i] == w2) {
                index2 = static_cast<int>(i);
                if (index1 != -1) {
                    minDist = min(minDist, index2 - index1);
                }
            }
        }

        return (minDist == numeric_limits<int>::max()) ? -1 : minDist;
    }

    /**
     * Optimized version (alternate structure) to calculate minimum word distance.
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int distanceOptimized2(const string& s, const string& w1, const string& w2) {
        int index1 = -1;
        int index2 = -1;
        int minDist = numeric_limits<int>::max();

        const auto parts = split(s, ' ');

        for (size_t i = 0; i < parts.size(); ++i) {
            if (parts[i] == w1) {
                index1 = static_cast<int>(i);
            } else if (parts[i] == w2) {
                index2 = static_cast<int>(i);
            }

            if (index1 != -1 && index2 != -1) {
                minDist = min(minDist, abs(index1 - index2));
            }
        }

        return (minDist == numeric_limits<int>::max()) ? -1 : minDist;
    }

private:
    /**
     * Utility function to split a string by a single character delimiter.
     */
    vector<string> split(const string& s, char delim) {
        vector<string> result;
        size_t start = 0;
        size_t end = 0;
        while ((end = s.find(delim, start)) != string::npos) {
            if (end > start) {
                result.emplace_back(s.substr(start, end - start));
            }
            start = end + 1;
        }
        if (start < s.length()) {
            result.emplace_back(s.substr(start));
        }
        return result;
    }
};
