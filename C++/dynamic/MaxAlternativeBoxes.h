#pragma once
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
#include <functional>
#include <future>
using namespace std;

class MaxBoxes
{
public:
    static void test()
    {
        MaxBoxes obj;
        vector<vector<int>> inputs = {
            {0,1,-2,3},
            {8,1,-1,2,2,10},
            {10,0,0,0,20},
            {-1, -2, -3},
            {},
            {-2},
            {99},
            {8,2,3,5,7,10},
        };

        for (auto input : inputs) {
            auto sum = obj.process(input);
            cout << "Max Sum: " << sum << endl;
        }
    }

    int process(vector<int> input) {
        return processRecurInternal(input, 0, true);
        //return processDP(input);
    }

    int processDP(vector<int> input)
    {
        int n = input.size();
        int prev = 0, prevprev = 0;

        for (int i = 0; i < n; i++) {
            int cur = max(prev, input[i] + prevprev);
            prevprev = prev;
            prev = cur;
        }

        return prev;
    }

    int processRecurInternal(vector<int> input, int index, bool canInclude) {
        if (index == input.size()) return 0;

        int excludeSum = processRecurInternal(input, index + 1, true);
        int includeSum = INT_MIN;
        if (canInclude) {
            includeSum = processRecurInternal(input, index + 1, false);
            includeSum = max(includeSum, includeSum + input[index]);
        }

        return max(0, max(includeSum, excludeSum));
    }
};