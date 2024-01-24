#include "../header.h"

/*
Given s string, Find max size of a sub-string, in which no duplicate chars present.

https://careercup.com/question?id=5684278553739264
*/

class LongestNonRepeatingSubstring {
   public:
    static void test() {
        string str = "abcabaabccfdsaewer";
        LongestNonRepeatingSubstring obj;
        string result1 = obj.longestNonRepeating(str);
        string result2 = obj.longestNonRepeating2(str);
        assert(result1 == result2);

        cout << format("Longest non-repeating string in str='{}' is '{}'.", str, result1) << endl;
    }

    string longestNonRepeating(string str) {
        int n = str.size();
        vector<int> seen(256, -1);
        int l = 0;

        string longest;
        string longestSoFar;

        for (int i = 0; i < n; i++) {
            int ch = (int)str[i];
            int pos = seen[ch];

            // If this character is already seen, move the pointer till pos (including pos).
            if (pos != -1) {
                if (longestSoFar.size() > longest.size()) {
                    longest = longestSoFar;
                }

                for (int i = l; i <= pos; i++)
                    seen[(int)str[i]] = -1;

                l = pos + 1;
                longestSoFar = str.substr(l, i - l);
            }

            // Add current character and mark it as seen.
            longestSoFar += str[i];
            seen[ch] = i;
        }

        if (longestSoFar.size() > longest.size()) {
            longest = longestSoFar;
        }

        return longest;
    }

   private:
    string longestNonRepeating2(string& str) {
        vector<int> visited(256, -1);
        int start = 0;
        string longest;
        for (int end = 0; end < str.size(); end++) {
            if (visited[str[end]] == -1) {
                visited[str[end]] = end;
            } else {
                string curLongest = str.substr(start, end - start);
                if (curLongest.length() > longest.length()) longest = curLongest;
                int found = visited[str[end]];
                for (int j = start; j <= found; j++) visited[str[j]] = -1;
                start = found + 1;
            }
        }

        return longest;
    }
};