#include "../header.h"

class CountNumberOfSubarraysWithElementsLessThanK {
   public:
   private:
    int countSubarrays(vector<int>& arr, int k) {
        int l = 0;
        int n = arr.length();
        int cnt = 0;
        for (int r = 0; r < n; r++) {
            if (arr[r] < k)
                cnt += (r - l + 1);
            else
                l = r + 1;
        }

        return cnt;
    }
};