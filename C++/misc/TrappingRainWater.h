#pragma once
#include "../header.h"

/*
 * Trapping Rain Water
 * https://leetcode.com/problems/trapping-rain-water/submissions/1825815220/?envType=study-plan-v2&envId=top-interview-150
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
 */
class TrappingRainWater {
   public:
    static void test() {
        TrappingRainWater obj;
        pair<vector<int>, int> t = {{5, 3, 4, 1, 6, 2, 9, 0, 3, 11}, 26};
        cout << "Actual: " << obj.trap(t.first) << ", Expected: " << t.second << endl;
        assert(t.second == obj.trap(t.first));
        assert(t.second == obj.trap2(t.first));

        t = {{5}, 0};
        cout << "Actual: " << obj.trap(t.first) << ", Expected: " << t.second << endl;
        assert(t.second == obj.trap(t.first));
        assert(t.second == obj.trap2(t.first));

        t = {{5, 3}, 0};
        cout << "Actual: " << obj.trap(t.first) << ", Expected: " << t.second << endl;
        assert(t.second == obj.trap(t.first));
        assert(t.second == obj.trap2(t.first));

        t = {{5, 3, 4}, 1};
        cout << "Actual: " << obj.trap(t.first) << ", Expected: " << t.second << endl;
        assert(t.second == obj.trap(t.first));
        assert(t.second == obj.trap2(t.first));

        t = {{5, 6, 7}, 0};
        cout << "Actual: " << obj.trap(t.first) << ", Expected: " << t.second << endl;
        assert(t.second == obj.trap(t.first));
        assert(t.second == obj.trap2(t.first));

        t = {{5, 6, 7, 8, 9}, 0};
        cout << "Actual: " << obj.trap(t.first) << ", Expected: " << t.second << endl;
        assert(t.second == obj.trap(t.first));
        assert(t.second == obj.trap2(t.first));
    }

   private:
    int trap(vector<int> A) {
        int left = 0;
        int right = A.size() - 1;

        int water = 0;
        int level = 0;
        while (left <= right) {
            int lower = A[left] < A[right] ? A[left++] : A[right--];
            if (lower > level) level = lower;
            water += level - lower;
        }
        return water;
    }

    int trap2(vector<int> A) {
        int result = 0;
        vector<int> left(A.size());
        vector<int> right(A.size());

        int mx = INT_MIN;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] > mx) mx = A[i];
            left[i] = mx;
        }

        mx = INT_MIN;
        for (int i = A.size() - 1; i >= 0; i--) {
            if (A[i] > mx) mx = A[i];
            right[i] = mx;
        }

        for (int i = 0; i < A.size(); i++) {
            result += min(right[i], left[i]) - A[i];
        }

        return result;
    }
};