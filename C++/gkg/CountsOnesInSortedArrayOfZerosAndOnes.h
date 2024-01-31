#pragma once
#include "../Header.h"

class CountsOnesInSortedArrayOfZerosAndOnes {
   public:
    static void test() {
        CountsOnesInSortedArrayOfZerosAndOnes obj;

        vector<vector<int>> inputs = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1}};
        for (auto& input : inputs) {
            auto res = obj.countOnes(input);
            cout << "Count of 1s = " << res << endl;
        }
    }

   private:
    int countOnes(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] == 0)
                l = m + 1;
            else
                r = m;
        }
        if (arr[l] == 0) return 0;
        return arr.size() - l;
    }
};