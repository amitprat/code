#pragma once
#include "../header.h"

// https://www.careercup.com/question?id=5677751244685312
// Find Consecutive 1s by turning k zeros to 1
// Given an array of 0s and 1s. find maximum no of consecutive 1s. If you have given chance to flip a bit to 1 such that it maximises the consecutive 1s. find out that flipped bit and after flipping that bit maximum no of consecutive 1s. Above question but you have options to flip k bits.*

class FindConsecutiveOnes {
   public:
    static void test() {
        FindConsecutiveOnes obj;
        vector<pair<vector<int>, int>> arrs = {
            {{1, 0, 0, 0, 0, 1}, 3},
            {{1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0}, 2},
            {{1, 1, 0, 0, 1, 1, 1, 0, 1, 1}, 2}};

        for (auto& arr : arrs) {
            auto mx = obj.findConsecutiveOnes(arr.first, arr.second);
            cout << "Consecutive ones: " << mx << endl;
        }
    }

   private:
    int findConsecutiveOnes(vector<int>& nums, int k) {
        int zc = 0, l = 0, mx = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0)
                zc++;
            while (zc > k) {
                if (nums[l++] == 0)
                    zc--;
            }

            mx = max(mx, i - l + 1);
        }

        return mx;
    }
};