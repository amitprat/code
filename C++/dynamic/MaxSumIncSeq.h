#pragma once
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <cassert>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

class MaxSumIncSeq
{
public:
    static void test()
    {
        MaxSumIncSeq obj;
        vector<vector<int>> contexts = {
            {1, 101, 2, 3, 100, 4, 5}
        };

        for (auto context : contexts) {
            cout << "Processing: {";
            for (auto j : context) cout << j << " ";
            cout << "}" << endl;

            int res = obj.maxSumSeq(context);
            cout << "Max Sum Seq = " << res << endl;

            res = obj.maxSumSeqDP(context);
            cout << "Max Sum Seq DP = " << res << endl;
        }
    }

    int maxSumSeq(vector<int> arr) {
        return maxSumSeqUtil(arr, 0, arr.size() - 1, INT_MIN);
    }

    int maxSumSeqDP(vector<int> arr) {
        int n = arr.size();
        int* table = new int[n];
        for (int i = 0; i < n; i++) table[i] = arr[i];
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (arr[i] >= arr[j]) table[i] = max(table[i], arr[i] + table[j]);
            }
        }

        int mx = INT_MIN;
        for (int i = 0; i < n; i++) mx = max(mx, table[i]);

        return mx;
    }

private:
    int maxSumSeqUtil(vector<int> arr, int s, int e, int prev) {
        if (s > e) return 0;
        if (s == e) return arr[s] >= prev ? arr[s] : 0;
        int without = maxSumSeqUtil(arr, s + 1, e, prev);
        int with = INT_MIN;
        if (arr[s] >= prev) with = arr[s] + maxSumSeqUtil(arr, s + 1, e, arr[s]);
        return max(without, with);
    }
};