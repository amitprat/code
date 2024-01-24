#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <map>
using namespace std;

class MakeSmallestString
{
public:
    static void test()
    {
        MakeSmallestString obj;
        vector<string> inputs = {
            {"bcsbc", "cbacdcbc"}
        };
        for (auto input : inputs) {
            cout << obj.findSmallest(input) << endl;
        }
    }

    string findSmallest(string str)
    {
        int len = str.length();
        vector<int> next(len);
        int lastPos[26];
        for (int i = 0; i < 26; i++) lastPos[i] = -1;
        for (int i = len - 1; i >= 0; i--) {
            char cur = str[i] - 'a';
            next[i] = lastPos[cur];
            lastPos[cur] = i;
        }

        vector<bool> visited(26, false);
        string res;

        for (int i = 0; i < len; i++) {
            int cur = str[i] - 'a';
            if (visited[cur]) continue;
            if (next[i] == -1) {
                res += str[i];
                visited[cur] = true;
            }
            else
            {
                int j = i + 1;
                char nextSmall = str[i];
                while (j < len) {
                    if (!visited[str[j] - 'a']) {
                        nextSmall = str[j];
                        nextSmall = min(nextSmall, str[i]);
                        if (next[j] == -1) break;
                    }
                    j++;
                }

                if (str[i] <= nextSmall) {
                    res += str[i];
                    visited[cur] = true;
                }
            }
        }

        return res;
    }
};