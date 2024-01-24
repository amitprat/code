#include "../Header.h"

class MinLexographicalStr
{
public:
    static void test() {
        {
            string str = "AAAAA";
            cout << minStrSorting(str) << endl;
        }

        {
            string str = "AAAAB";
            cout << minStrSorting(str) << endl;
        }

        {
            string str = "ABABA";
            cout << minStrSorting(str) << endl;
        }

        {
            string str = "CBAD";
            cout << minStrSorting(str) << endl;
        }

        {
            string str = "CBDJFKFJSBFLDHIKBCKHDCBDHCBDJHCCDCMCSXCXCCXDWJHBCANC";
            cout << minStrSorting(str) << endl;
        }
    }

    static string minStr(string str) {
        vector<int> minIndex = { 0 };
        for (int i = 1; i < str.length(); i++) {
            if (str[i] < str[minIndex.front()]) minIndex = { i };
            else if (str[i] == str[minIndex.front()]) minIndex.push_back(i);
        }

        for (int j = 1; j < str.length() && minIndex.size() > 1; j++) {
            int i = 0;
            int prev = 0;
            for (i = 1; i < minIndex.size(); i++) {
                if (str[(minIndex[i] + j) % str.size()] != str[(minIndex[prev] + j) % str.size()]) {
                    if (str[(minIndex[i] + j) % str.size()] < str[(minIndex[prev] + j) % str.size()]) {
                        minIndex.erase(minIndex.begin() + prev);
                        prev = i - 1;
                    }
                    else {
                        minIndex.erase(minIndex.begin() + i);
                    }
                    i--;
                }
            }

            if (i != minIndex.size()) minIndex.erase(minIndex.begin() + i);
        }

        int idx = minIndex.front();
        reverse(str.begin(), str.begin() + idx);
        reverse(str.begin() + idx, str.end());

        reverse(str.begin(), str.end());

        return str;
    }

    static string minStrSorting(string str) {
        int n = str.size();
        str += str;
        vector<string> strs;
        for (int i = 0; i < n; i++) {
            strs.push_back(str.substr(i, n));
        }

        sort(strs.begin(), strs.end());

        return strs[0];
    }
};