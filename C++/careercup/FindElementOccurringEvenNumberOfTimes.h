#pragma once
#include "../Header.h"

class FindNumbersOccurringEvenNumberOfTimes {
   public:
    static void test() {
        FindNumbersOccurringEvenNumberOfTimes obj;
        vector<int> nums = {1, 6, 4, 1, 4, 5, 8, 8, 4, 6, 8, 8, 9, 7, 9, 5, 9};

        vector<int> result = obj.findEvenNumbersUingBitset(nums);
        cout << result << endl;

        result = obj.findEvenNumbersUsingTracker(nums);
        cout << result << endl;
    }

    vector<int> findEvenNumbersUingBitset(vector<int>& nums) {
        bitset<32> bitMap;
        int mxRange = 0;
        for (auto num : nums) {
            bitMap.flip(num);
            mxRange = max(mxRange, num);
        }

        vector<int> result;
        for (int i = 0; i <= mxRange; i++) {
            if (!bitMap.test(i)) {
                result.push_back(i);
            }
        }

        return result;
    }

    vector<int> findEvenNumbersUsingTracker(vector<int>& nums) {
        unsigned long long tracker;
        int mxRange = 0;
        for (auto& num : nums) {
            tracker |= (1 << num);
            mxRange = max(mxRange, num);
        }

        vector<int> result;
        for (int i = 0; i <= mxRange; i++) {
            if (!(i & (1 << i))) {
                result.push_back(i);
            }
        }

        return result;
    }
};