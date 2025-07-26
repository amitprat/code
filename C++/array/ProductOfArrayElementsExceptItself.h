#pragma once
#include "../header.h"

class ProductOfArrayElementsExceptItself {
   public:
    // brute force
    vector<int> productExceptSelf1(vector<int>& nums) {
        int n = nums.size();
        vector<int> output;
        for (int i = 0; i < n; i++) {
            int product = 1;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                product *= nums[j];
            }
            output.push_back(product);
        }
        return output;
    }

   public:
    vector<int> productExceptSelf2(vector<int>& nums) {
        int n = nums.size();
        vector<int> prod(n, 1);

        // Left prefix
        int left = 1;
        for (int i = 0; i < n; ++i) {
            prod[i] *= left;
            left *= nums[i];
        }

        // Right suffix
        int right = 1;
        for (int i = n - 1; i >= 0; --i) {
            prod[i] *= right;
            right *= nums[i];
        }

        return prod;
    }

   public:
    vector<long long> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<long long> ans(n, 1);

        long long left = 1, right = 1;

        for (int i = 0; i < n; ++i) {
            ans[i] *= left;
            left *= nums[i];

            ans[n - 1 - i] *= right;
            right *= nums[n - 1 - i];
        }

        return ans;
    }
};