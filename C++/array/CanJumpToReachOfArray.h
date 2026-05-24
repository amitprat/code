#pragma once
#include "../header.h"

/*
https://leetcode.com/problems/jump-game/description/?envType=problem-list-v2&envId=oizxjoit

You are given an integer array nums. You are initially positioned at the array's first index,
and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
*/

class CanJumpToReachOfArray {
   public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > maxReach) return false;
            maxReach = max(maxReach, i + nums[i]);
        }
        return true;
    }

    bool canReach(vector<int>& nums) {
        int goal = nums.size() - 1;

        for (int i = nums.size() - 2; i >= 0; i--) {
            // minimum target to reach
            if (i + nums[i] >= goal) {
                goal = i;
            }
        }

        return goal == 0;
    }
};