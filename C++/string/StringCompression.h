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
using namespace std;

class StringCompression
{
public:
    static void test()
    {
        StringCompression obj;
        vector<string> strs = { "abcbcac", "","a", "ab", "aab", "aacbb", "aabsaaabbcccdddd","ccccccccccccccc","cddddddddc" };
        for (auto str : strs) {
            cout << "Is palin : " << str << " : " << obj.compress(str) << endl;
        }
    }

    string compress(string str)
    {
        int i = 0, j = 0;
        int cnt = 1;
        char prev = '\0';
        while (j <= str.length()) {
            if (prev != str[j]) {
                if (cnt > 1) {
                    string tmp = to_string(cnt);
                    for (int k = 0; k < tmp.length(); k++) {
                        str[i++] = tmp[k];
                    }
                }
                str[i++] = prev = str[j];
                cnt = 1;
            }
            else cnt++;
            j++;
        }
        return str.substr(0, i);
    }
};