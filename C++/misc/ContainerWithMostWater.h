#pragma once
#include "../header.h"

/*
https://leetcode.com/problems/container-with-most-water/description/

You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints
of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.
*/

class ContainerWithMostWater {
   public:
    static void test() {
        ContainerWithMostWater obj;
        vector<int> input = {1, 2, 4, 2, 3, 2, 5, 2};
        cout << obj.mostWater(input) << endl;
    }

   public:
    int mostWater(vector<int>& input) {
        int mxArea = 0;
        tuple<int, int, int> position;

        int left = 0, right = input.size() - 1;
        while (left <= right) {
            int height = min(input[left], input[right]);
            int width = right - left;
            int curArea = height * width;
            if (curArea > mxArea) {
                mxArea = curArea;
                position = {left, right, height};
            }

            // move pointers
            if (input[left] < input[right])
                left++;
            else
                right--;
        }

        cout << "Position = (" << std::get<1>(position) << "-" << std::get<0>(position) << ")*" << std::get<2>(position) << endl;
        return mxArea;
    }

   public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int mx = 0;
        while (l < r) {
            mx = max(mx, min(height[l], height[r]) * (r - l));
            (height[l] < height[r]) ? l++ : r--;
        }

        return mx;
    }
};