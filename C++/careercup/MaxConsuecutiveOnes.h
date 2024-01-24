#include "../header.h"

class MaxConsuecutiveOnes {
   public:
    static void test() {
    }

    int consecutiveOnes(vector<int>& num, int k) {
        int l = 0, mx = 0, zeros = 0;

        for (int i = 0; i < num.size(); i++) {
            if (num[i] == 0) zeros++;
            while (zeros > k) {
                if (num[l] == 0) l++;
                zeros--;
            }
            mx = max(mx, i - l + 1);
        }

        return mx;
    }
};