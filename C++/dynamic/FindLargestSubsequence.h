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

class FindLargestSubsequence
{
public:
    static void test()
    {
        FindLargestSubsequence obj;
        vector<vector<int>> inputs = {
            {1,6,10,4,7,9,5}
        };
        for (auto input : inputs) {
            auto res = obj.findLargest(input);
            cout << res.first << " " << res.second << endl;
        }
    }

    pair<int, int> findLargest(vector<int> input)
    {
        unordered_map<int, int> table;
        pair<int, int> largest = { 0, 0 };
        for (auto i : input) {
            int beg = i;
            int end = i;
            if (table.find(i) != table.end()) continue;
            table[i] = i;
            if (table.find(i - 1) != table.end()) beg = table[i - 1];
            if (table.find(i + 1) != table.end()) end = table[i + 1];
            table[beg] = end;
            table[end] = beg;

            if (end - beg > largest.second - largest.first) {
                largest = { beg, end };
            }
        }

        return largest;
    }
};