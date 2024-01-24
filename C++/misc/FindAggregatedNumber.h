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

class FindAggregatedNumber
{
public:
    static void test()
    {
        FindAggregatedNumber obj;
        vector<string> inputs = { "134", "", "01124","2324","112358","122436","1299111210","112112224" };
        for (auto input : inputs) {
            cout << obj.isAggregated(input) << endl;
        }
    }

    bool isAggregated(string input) {
        int len = input.length();
        int half = len / 2;
        for (int i = 1; i < len; i++) {
            for (int j = i; j < len; j++) {
                if (isMatch(input, i, j)) return true;
            }
        }

        return false;
    }

    bool isMatch(string input, int i, int j)
    {
        string first = input.substr(0, i);
        string second = input.substr(i, j - i + 1);
        string buffer = first + second;

        while (buffer.length() < input.length()) {
            string third = to_string(stoi(first) + stoi(second));
            first = second;
            second = third;

            buffer += third;
        }

        return buffer == input;
    }
};