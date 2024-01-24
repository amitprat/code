#include "../header.h"

class SearchInSortedRotatedArray {
   public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;

        // find pivot
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > nums[hi])
                lo = mid + 1;
            else
                hi = mid;
        }

        // now bsearch with rotation as offset
        int rot = lo;
        lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int realmid = (mid + rot) % nums.size();
            if (nums[realmid] == target) return realmid;
            if (target < nums[realmid])
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        return -1;
    }

   private:
    int rotated_binary_search(int A[], int N, int key) {
        int L = 0;
        int R = N - 1;

        while (L <= R) {
            int M = L + ((R - L) / 2);
            if (A[M] == key) return M;

            // the bottom half is sorted
            if (A[L] <= A[M]) {
                if (A[L] <= key && key < A[M])
                    R = M - 1;
                else
                    L = M + 1;
            }
            // the upper half is sorted
            else {
                if (A[M] < key && key <= A[R])
                    L = M + 1;
                else
                    R = M - 1;
            }
        }
        return -1;
    }
};