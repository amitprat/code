#pragma once
#include "Header.h"

class FindNumbersOccurringOddNumberOfTimes
{
public:
    static void test()
    {
        FindNumbersOccurringOddNumberOfTimes obj;
        vector<int> nums = { 2,3,2,3,3,4,5,4,2,2,5,6 };
        auto res = obj.findNumbers(nums);

        cout << "Result: " << to_string(res) << endl;
    }

private:
    pair<int, int> findNumbers(const vector<int>& nums) {
        int diff = 0;
        for (auto& num : nums) {
            diff ^= num;
        }

        int i = 0;
        for (; i < 32; i++) {
            if (diff & (1 << i)) break;
        }

        int p1 = positionOfRightMostBit1(diff);
        int p2 = positionOfRightMostBit1(diff);
        int p3 = positionOfRightMostBit1(diff);
        int p4 = positionOfRightMostBit1(diff);

        assert(p1 == p2);
        assert(p2 == p3);
        assert(p3 == p4);

        int first = 0, second = 0;
        for (auto& num : nums) {
            if (num & (1 << i)) first ^= num;
            else second ^= num;
        }

        return { first, second };
    }

    int positionOfRightMostBit1(int num) {
        int p = 0;
        while (num) {
            if (num & 1) return p;

            p++;
            num >>= 1;
        }

        return p;
    }

    int positionOfRightMostBit2(int num) {
        int p = 0;
        int m = 0;

        while (!(num & m)) {
            m <<= 1;
            p++;
        }

        return p;
    }

    int positionOfRightMostBit3(int num) {
        return log2(num & -num);
    }

    int positionOfRightMostBit4(int num) {
        int i = 0;
        for (; i < 32; i++) {
            if (num & (1 << i)) break;
        }
        return i;
    }
};