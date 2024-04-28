#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=5758790009880576

Given a string which only contains lowercase. You need delete the repeated letters only leave one, and try to make the lexicographical order of new string is smallest.
i.e: bcabc
You need delete 1 'b' and 1 'c', so you delete the first 'b' and first 'c', the new string will be abc which is smallest.

ps: If you try to use greedy algorithm to solve this problem, you must sure that you could pass this case:
cbacdcbc. answer is acdb not adcb

UPD: I could find a way to optimize my code to O(N). Main idea is the same. I added updated part after my old explanations
Here's my O(N^2) idea which is absoloutly true:D (proved, and tested with many random test cases)

Let's say we have string S:
I define next[i] = next position (after i) which is equal to S[i], if there is not, -1.
So if S="bacdbcb", next={4,-1,5,-1,6,-1,-1}
Now, I iterate through S, from left to right, and at each position, I decide whether to pick the current character or not.
Also, there is an array called visited, which visited[i]=true means character i has been picked.
*/
class LexographicalSmallestString {
   public:
    static void test() {
        LexographicalSmallestString obj;

        string str = "cbacdcbc";
        auto res1 = obj.removeRepeatedLinear(str);
        auto res2 = obj.removeRepeated1(str);
        auto res3 = obj.removeRepeated2(str);
        assert(res1 == res2);
        assert(res1 == res3);

        cout << res1 << endl;
    }

   private:
    string removeRepeatedLinear(string s) {
        int N = s.size();
        stack<int> pos[26];  // positions of each character
        int lastPos[26] = {-1};

        for (int i = N - 1; i >= 0; i--) {
            int cur = s[i] - 'a';

            if (pos[cur].empty())
                lastPos[cur] = i;

            pos[cur].push(i);
        }

        vector<bool> visited(26, false);
        string ans;

        for (int i = 0; i < N; i++) {
            int cur = s[i] - 'a';
            if (visited[cur]) continue;

            if (pos[cur].size() == 1) {  // last character of cur
                ans += s[i];
                visited[cur] = true;
            } else {
                bool isSmaller = false;
                int minpos = N;

                for (int k = 0; k < 26; k++) {
                    if (!visited[k] && !pos[k].empty())
                        minpos = min(minpos, lastPos[k]);
                }

                for (int k = 0; k < cur && !isSmaller; k++) {
                    if (visited[k] || pos[k].empty()) continue;

                    if (pos[k].top() <= minpos)
                        isSmaller = true;
                }

                if (isSmaller == false) {
                    ans += s[i];
                    visited[cur] = true;
                }
            }

            pos[cur].pop();
        }

        return ans;
    }

   private:
    string removeRepeated1(string& str) {
        int n = str.length();
        vector<int> lastPos(26, -1);
        vector<int> next(n, -1);

        // get the next position of character at each index.
        // This is used to check if there are further same character is there or not.
        for (int i = n - 1; i >= 0; i--) {
            int chIdx = str[i] - 'a';
            next[i] = lastPos[chIdx];  // next position of current character.
            lastPos[chIdx] = i;        // update the position of current character in string.
        }

        vector<bool> visited(26, false);
        string result;

        for (int i = 0; i < n; i++) {
            int chIdx = str[i] - 'a';
            if (visited[chIdx]) continue;  // if this char already included, skip this one then.

            if (next[i] == -1) {  // if this is last character in string, add it to result.
                result += str[i];
                visited[chIdx] = true;
            } else {
                char smaller = str[i];
                for (int j = i + 1; j < n; j++) {  // check if there is any smaller character on right of it which can be used to make smaller string
                    smaller = min(smaller, str[j]);
                    if (next[j] == -1) break;  // if current position doesn't have any next instance of same character, then we must include this
                }

                if (str[i] <= smaller) {  // if current character is smallest then include it.
                    chIdx = str[i] - 'a';

                    result += str[i];
                    visited[chIdx] = true;
                }
            }
        }

        return result;
    }

   private:
    string removeRepeated2(string& str) {
        int n = str.size();
        unordered_set<char> visited;
        vector<bool> isLastChar(n, false);

        for (int i = n - 1; i >= 0; i--) {
            char ch = str[i];

            if (visited.find(ch) == visited.end())
                isLastChar[i] = true;
            else
                isLastChar[i] = false;

            visited.insert(ch);
        }

        visited.clear();
        string result;

        for (int i = 0; i < n; i++) {
            char ch = str[i];
            if (visited.find(ch) != visited.end()) continue;

            if (isLastChar[ch]) {
                result += ch;
                visited.insert(ch);
            } else {
                char smaller = str[i];

                for (int j = i + 1; j < n; j++) {
                    smaller = min(smaller, str[j]);
                    if (isLastChar[j]) break;
                }

                if (str[i] <= smaller) {
                    ch = str[i];
                    result += ch;
                    visited.insert(ch);
                }
            }
        }

        return result;
    }

   public:
    static string smallest(string str) {
        int n = str.length();
        vector<int> lastIndex(26, -1);  // <character to last index of it in string> mapping
        vector<int> next(n);            // <character to next index of it in string> mapping
        for (int i = n - 1; i >= 0; i--) {
            int cur = str[i] - 'a';
            next[i] = lastIndex[cur];  // next index for this character at this position
            lastIndex[cur] = i;        // last index for this character at this position
        }

        string res;
        vector<bool> visited(26, false);
        for (int i = 0; i < n; i++) {
            int idx = str[i] - 'a';
            if (visited[idx]) continue;  // if this character already included in result, exclude it

            if (next[idx] == -1) {  // if this is last index for this character, include it and mark it as visited.
                res += str[i];
                visited[idx] = true;
            } else {
                // otherwise, look for next smallest character right to it until end or this character is only character. Include the smallest character.
                char smallest = str[i];
                int j = i + 1;
                while (j < n) {
                    if (visited[idx]) continue;

                    if (str[j] < smallest) smallest = str[j];
                    if (next[j] == -1) break;  // this is last index for this character so break here, we must include this
                    j++;
                }

                if (str[i] <= smallest) {
                    res += str[i];
                    visited[idx] = true;
                }
            }
        }

        return res;
    }
};