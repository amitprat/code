#pragma once
#include "../Header.h"

class LongestSubarrayWithZeroSum {
public:
    static void test() {
        LongestSubarrayWithZeroSum obj;
        int N = 8;
        int A[] = { 15,-2,2,-8,1,7,10,23 };

        auto res = obj.maxLen(A, N);
        cout << to_string(res) << endl;
    }

    int maxLen(int A[], int n)
    {
        unordered_map<int, int> map;
        int sum = 0;
        int largest = 0;
        map[0] = 1;
        for (int i = 0; i < n; i++) {
            sum += A[i];
            if (map.find(sum) == map.end()) map[sum] = i;
            else largest = max(largest, i - map[sum]);
        }

        return largest;
    }
};