#pragma once
#include "../Header.h"

class MaximumSumSubseq {
public:
    static void test() {
        MaximumSumSubseq obj;
        vector<int> v = { 1, -1, 3, -8, 4 };
        cout << obj.maxSum(v) << endl;
    }

    int maxSum(vector<int> v) {
        int mx = INT_MIN;
        maxSum(v, v.size(), 0, mx);
        return mx;
    }

private:
    void maxSum(vector<int> v, int n, int cur, int& mx) {
        if (n == 0) { mx = max(mx, cur); return; }
        maxSum(v, n - 1, cur, mx);
        maxSum(v, n - 1, cur + v[n - 1], mx);
    }
};