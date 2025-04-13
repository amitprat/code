#include "../header.h"

/*
https://leetcode.com/problems/subarray-sums-divisible-by-k/description/

Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.
*/

class SubarrayDivisibleByK {
   public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int cnt = 0;

        int prefixSum = 0;
        unordered_map<int, int> prefixMap;
        prefixMap.insert({0, 1});  // {mod, cnt}

        for (auto& num : nums) {
            prefixSum += num;
            int mod = prefixSum % k;
            if (mod < 0) mod += k;

            if (prefixMap.find(mod) != prefixMap.end()) {
                cnt += prefixMap[mod];
                prefixMap[mod] += 1;
            } else {
                prefixMap[mod] = 1;
            }
        }

        return cnt;
    }
};