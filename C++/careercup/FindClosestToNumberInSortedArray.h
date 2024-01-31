#pragma once
#include "../header.h"

class FindClosestToNumberInSortedArray {
   public:
    static void test() {
        FindClosestToNumberInSortedArray obj;
        std::vector<int> sortedArray = {2, 5, 8, 10, 13, 15, 18};

        for (int target = 0; target <= 20; target++) {
            int closestNumber1 = obj.findClosestNumber1(sortedArray, target);
            int closestNumber2 = obj.findClosestNumber2(sortedArray, target);
            int closestNumber3 = obj.findClosestNumber3(sortedArray, target);
            assert(closestNumber1 == closestNumber2);
            assert(closestNumber1 == closestNumber3);

            std::cout << "Closest number to " << target << " in the array: " << closestNumber1 << std::endl;
        }
    }

   private:
    // from chatgpt
    int findClosestNumber1(const std::vector<int>& arr, int target) {
        int low = 0;
        int high = arr.size() - 1;
        int closest = arr[0];  // Initialize with the first element

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Update the closest if the current element is closer to the target
            if (abs(arr[mid] - target) < abs(closest - target)) {
                closest = arr[mid];
            }

            if (arr[mid] == target) {
                return arr[mid];
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return closest;
    }

   private:
    int findClosestNumber2(vector<int>& arr, int num) {
        return findClosestNumber2(arr, 0, arr.size() - 1, num);
    }

    int findClosestNumber2(vector<int>& arr, int l, int r, int num) {
        if (l > r) return INT_MIN;

        if (l == r) return arr[l];
        if (l + 1 == r) return num - arr[l] < arr[r] - num ? arr[l] : arr[r];

        int m = (l + r) / 2;
        if (arr[m] == num) return arr[m];

        if (num < arr[m])
            return findClosestNumber2(arr, l, m, num);
        else
            return findClosestNumber2(arr, m, r, num);
    }

   private:
    int findClosestNumber3(vector<int>& arr, int num) {
        int l = 0, r = arr.size() - 1;
        if (l > r) return INT_MIN;

        while (l < r) {
            int m = (l + r + 1) / 2;
            if (arr[m] > num)
                r = m - 1;
            else
                l = m;
        }

        if (r == arr.size() - 1) return arr[r];
        return (num - arr[l] < arr[l + 1] - num) ? arr[l] : arr[l + 1];
    }
};