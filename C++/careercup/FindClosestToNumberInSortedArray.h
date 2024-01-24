#include "../header.h"

class FindClosestToNumberInSortedArray {
   public:
    static void test() {
        FindClosestToNumberInSortedArray obj;
        std::vector<int> sortedArray = {2, 5, 8, 10, 13, 15, 18};

        for (int target = 0; target <= 20; target++) {
            int closestNumber = obj.findClosestNumber(sortedArray, target);
            std::cout << "Closest number to " << target << " in the array: " << closestNumber << std::endl;

            closestNumber = obj.findClosest(sortedArray, target);
            std::cout << "Closest number to " << target << " in the array: " << closestNumber << std::endl;
        }
    }

   private:
    // from chatgpt
    int findClosestNumber(const std::vector<int>& arr, int target) {
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

    int findClosest(vector<int>& arr, int num) {
        return findClosest(arr, 0, arr.size() - 1, num);
    }
    int findClosest(vector<int>& arr, int l, int r, int num) {
        if (l > r) return INT_MIN;
        if (num < arr[l]) return arr[l];
        if (num > arr[r]) return arr[r];
        if (l + 1 == r) return num - arr[l] < arr[r] - num ? arr[l] : arr[r];

        int m = (l + r) / 2;
        if (arr[m] == num) return arr[m];

        if (num < arr[m])
            return findClosest(arr, l, m, num);
        else
            return findClosest(arr, m, r, num);
    }
};