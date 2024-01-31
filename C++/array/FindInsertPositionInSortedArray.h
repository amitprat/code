#pragma once
#include "../header.h"
using namespace std;

class FindInsertPositionInSortedArray {
   public:
    static void test() {
        FindInsertPositionInSortedArray obj;
        vector<pair<vector<int>, int>> tests = {
            {{}, 5},
            {{1}, 1},
            {{1}, 0},
            {{1}, 2},
            {{1, 3, 5, 6}, 5},
            {{1, 3, 5, 6}, 2},
            {{1, 3, 5, 6}, 7},
            {{1, 3, 5, 6}, 0},
            {{1, 3, 3, 3, 3, 3, 3, 5}, 2},
            {{1, 3, 3, 3, 3, 3, 3, 5}, 3},
            {{1, 3, 3, 3, 3, 3, 3, 5}, 4},
            {{3, 3, 3, 3}, 3}};

        for (auto& test : tests) {
            auto pos1 = obj.findInsertPosition1(test.first, test.second);
            auto pos2 = obj.findInsertPosition2(test.first, test.second);
            auto pos3 = obj.findInsertPosition3(test.first, test.second);

            cout << format("Insert position of element {} in array {} is {},{},{}.", test.second, to_string(test.first), pos1, pos2, pos3) << endl;
        }
    }

   private:
    // find the index of last element which is less than or equal to target
    // if we find such position then insert at +1 position otherwise at current position
    int findInsertPosition1(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        if (l > r) return l;  // if there is no element in array.

        // find the position of element < first occurance of that element.
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (target <= nums[m])
                r = m - 1;
            else
                l = m;
        }

        return (target <= nums[l]) ? l : l + 1;
    }

   private:
    // look for first greater element
    // if there is none, then we need to insert at +1 position
    int findInsertPosition2(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        if (l > r) return l;

        // find the position of last element which is greater than or equal to target element.
        while (l < r) {
            int m = (l + r) / 2;
            if (target >= nums[m])
                l = m + 1;
            else
                r = m;
        }

        return (target < nums[r]) ? r : r + 1;
    }

   private:
    int findInsertPosition3(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        if (l > r) return l;

        while (l < r) {
            int m = (l + r + 1) / 2;
            // if the element at current position is <= target elemment, then we should search on right, including current element.
            // include current element to skip duplicates to reach the last element position.
            // If the current element is greater, then we can just search on left side.
            if (target >= nums[m])
                l = m;
            else
                r = m - 1;
        }

        return (target < nums[r]) ? r : r + 1;
    }
};
