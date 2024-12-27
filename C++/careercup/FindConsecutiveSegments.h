#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5693954190213120

Number list compressing.
Given an sorted array. Input: sorted number list
1, 2, 3,10, 25, 26, 30, 31, 32, 33

Output: find consecutive segments
print: 1-3, 10, 25-26, 30-33
*/
class FindConsecutiveSegments {
   public:
    static void test() {
        FindConsecutiveSegments obj;

        vector<vector<int>> inputs = {
            {},
            {1},
            {1, 2, 3, 4},
            {1, 3, 5, 7},
            {1, 3, 5, 6, 7, 8, 9},
            {1, 2, 3, 10, 25, 26, 30, 31, 32, 33}};

        for (auto& input : inputs) {
            auto res = obj.findConsecutiveSequence(input);
            println("Consecutive sequence={0}", res);
        }
    }

   public:
    vector<string> findConsecutiveSequence(const vector<int>& arr) {
        vector<string> output;
        if (arr.size() == 0) return output;

        int a = arr[0];
        int b = arr[0];

        for (int i = 1; i <= arr.size(); i++) {
            if (i < arr.size() && arr[i] == b + 1) {
                b = arr[i];
            } else {
                if (a == b)
                    output.push_back(std::to_string(a));
                else
                    output.push_back(to_string<int>(std::make_pair(a, b)));

                if (i < arr.size()) a = b = arr[i];
            }
        }

        return output;
    }
};