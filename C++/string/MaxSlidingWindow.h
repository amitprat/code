#pragma once
#include "../header.h"

/********* https://leetcode.com/problems/sliding-window-maximum/ *********
 * You are given an array of integers nums, there is a sliding window of size k which is moving
 * from the very left of the array to the very right. You can only see the k numbers in the window.
 * Each time the sliding window moves right by one position. Return the max sliding window.
 * Example 1:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 */

class SlidingWindowMaximum {
   public:
    static void test() {
        SlidingWindowMaximum obj;
        vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;
        vector<int> expected = {3, 3, 5, 5, 6, 7};

        vector<int> res = obj.maxSlidingWindow(nums, k);
        assert(expected == res);
        cout << format("Max sliding window of nums={} with window size={} is {}", nums, k, res) << endl;
    }

   private:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;  // stores indices of elements in the current window
        vector<int> result;

        for (int i = 0; i < nums.size(); i++) {
            // Remove indices that are out of the current window
            while (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }
            // Remove indices whose corresponding values are less than nums[i]
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            // Add the current index to the deque
            dq.push_back(i);
            // The front of the deque is the largest element in the current window
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }

    vector<int> maxSlidingWindow2(vector<int>& nums, int k) {
        deque<int> dq;       // stores indices of elements in the current window
        vector<int> result;  // stores the maximum of each sliding window

        for (int i = 0; i < nums.size(); i++) {
            // Remove indices that are out of the current window
            if (!dq.empty() && i - dq.front() >= k) dq.pop_front();

            // Remove indices whose corresponding values are less than nums[i]
            while (!dq.empty() && nums[i] > nums[dq.back()]) dq.pop_back();

            // Add the current index to the deque
            dq.push_back(i);

            // The front of the deque is the largest element in the current window
            if (i >= k - 1) result.push_back(nums[dq.front()]);
        }

        return result;
    }
};