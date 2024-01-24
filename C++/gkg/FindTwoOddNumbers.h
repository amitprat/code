#pragma once
#include "../Header.h"

class FindTwoOddNumbers {
public:
    static void test() {
        FindTwoOddNumbers obj;
        vector<int> nums = { 1,2,3,4,5,6,3,4,2,1,5,6,1,3 };

        pair<int, int> res = obj.findOdds(nums);
        cout << to_string(res) << endl;
    }

    pair<int, int> findOdds(vector<int> nums) {
        int xorVal = 0;
        for (auto num : nums) xorVal ^= num;

        int n = findLastSetBut(xorVal);

        int val1 = 0, val2 = 0;
        for (auto num : nums) {
            if (num & (1 << n)) val1 ^= num;
            else val2 ^= num;
        }

        return { val1, val2 };
    }

    int findLastSetBut(int val) {
        val = val & ~(val - 1);
        return log2(val);
    }
};