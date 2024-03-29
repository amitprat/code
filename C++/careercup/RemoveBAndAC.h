#include "../header.h"

/*
https://www.careercup.com/question?id=18460667

Eliminate all ‘b’ and ‘ac’ in an array of characters, you have to replace them in-place, and you are only allowed to iterate over the char array once.

Examples:
abc -> ac
ac->''
react->rt
*/

class RemoveBAndAC {
   public:
    static void test() {
        RemoveBAndAC obj;
        vector<string> inputs = {"ad", "acbac", "aaac", "react", "aa", "ababaac", "reababcct", "babcaaabcccbccabbc"};

        for (auto &str : inputs) {
            // auto res1 = replace(const_cast<char *>(str.c_str()));
            string res1 = obj.remove1(str);
            string res2 = obj.remove2(str);
            string res3 = obj.removeUsingStack(str);

            assert(res1 == res2);
            assert(res1 == res3);

            int n = str.length();
            char *charArr1 = new char[n];
            strcpy(charArr1, str.c_str());
            obj.replace(charArr1);

            char *charArr2 = new char[n];
            strcpy(charArr2, str.c_str());
            obj.remove3(charArr2);

            assert(res1 == string(charArr1));
            assert(res1 == string(charArr2));

            cout << res1 << endl;
        }
    }

   private:
    // the one taken from careercup (pointer and char array version)
    void replace(char *str) {
        int n = strlen(str);
        int i = 0;
        char *q = str;
        while (*q) {
            if (*q == 'b')
                q++;
            else {
                if (*q == 'c' && (i > 0 && str[i - 1] == 'a')) {
                    q++;
                    i--;
                } else {
                    str[i] = *q;
                    q++;
                    i++;
                }
            }
        }

        // remove rest of characters
        for (; i < n; i++) str[i] = '\0';
    }

   private:
    // Mine (string and index version)
    string remove1(string str) {
        int i = 0, j = 0;
        while (j < str.length()) {
            if (str[j] == 'b')
                j++;
            else if (str[j] == 'c' && (j > 0 && str[i - 1] == 'a')) {
                j++;
                i--;
            } else
                str[i++] = str[j++];
        }

        return str.substr(0, i);
    }

   private:
    // Alternative implementation of above remove
    string remove2(string str) {
        int i = 0;
        for (int j = 0; j < str.length(); j++) {
            if (str[j] == 'b')
                continue;
            else if (i > 0 && str[i - 1] == 'a' && str[j] == 'c')
                i -= 1;
            else
                str[i++] = str[j];
        }
        str.erase(str.begin() + i, str.end());

        return str;
    }

   private:
    // stack appraoch
    string removeUsingStack(string str) {
        stack<char> st;
        for (auto ch : str) {
            if (ch == 'b') continue;
            if (!st.empty() && st.top() == 'a' && ch == 'c')
                st.pop();
            else
                st.push(ch);
        }

        string res;
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        std::reverse(res.begin(), res.end());

        return res;
    }

   private:
    void remove3(char str[]) {
        int n = strlen(str);
        int k = 0;
        for (int i = 0; i < n; i++) {
            switch (str[i]) {
                case 'a':
                    str[k++] = 'a';
                    break;
                case 'b':
                    break;
                case 'c':
                    if (k > 0 && str[k - 1] != 'a')
                        str[k++] = 'c';
                    else
                        k--;  // remove 'a'
                    break;
                default:
                    str[k++] = str[i];
                    break;
            }
        }

        // remove rest of characters
        for (; k < n; k++) str[k] = '\0';
    }
};