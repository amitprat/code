/*
https://careercup.com/question?id=5668212962230272

Given an array of integers.

Move all non-zero elements to the left of all zero elements.

0
---Rearranged array is---
0

======================
---Given array is---
1
---Rearranged array is---
1

======================
---Given array is---
0 0
---Rearranged array is---
0 0

======================
---Given array is---
1 1
---Rearranged array is---
1 1

======================
---Given array is---
0 1
---Rearranged array is---
0 1

======================
---Given array is---
0 1 0
---Rearranged array is---
0 0 1

======================
---Given array is---
1 0 1
---Rearranged array is---
0 1 1

======================
---Given array is---
0 0 0 0 0 0 0 0 0 0
---Rearranged array is---
0 0 0 0 0 0 0 0 0 0

======================
---Given array is---
1 1 1 1 1 1 1 1 1 1
---Rearranged array is---
1 1 1 1 1 1 1 1 1 1

======================
---Given array is---
1 0 0 0 0 0 1 0 0 0
---Rearranged array is---
0 0 0 0 0 0 0 0 1 1

======================
---Given array is---
1 0 0 1 1 1 1 1 0 0
---Rearranged array is---
0 0 0 0 1 1 1 1 1 1

======================
*/
#include "../header.h"

class BinaryArrSort {
   public:
    static void test() {
        BinaryArrSort obj;
        vector<vector<int>> arrs = {
            {},
            {0},
            {1},
            {0, 0},
            {1, 1},
            {0, 1},
            {0, 1, 0},
            {1, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 1, 1, 1, 1, 1, 0, 0}};

        for (auto arr : arrs) {
            cout << "Input" << arr << endl;

            vector<int> arr1 = arr, arr2 = arr, arr3 = arr;
            obj.sort1(arr1);
            obj.sort2(arr2);
            obj.sort2(arr3);

            assert(arr1 == arr2);
            assert(arr1 == arr3);
            cout << "Output: " << arr1 << endl;
        }
    }

    void sort1(vector<int>& arr) {
        int s = 0, e = arr.size() - 1;
        while (s < e) {
            if (arr[s] == 0)
                s++;
            else {
                if (arr[e] == 0)
                    swap(arr[s++], arr[e]);
                else
                    e--;
            }
        }
    }

    void sort2(vector<int>& arr) {
        for (int i = 0, j = 0; j < arr.size(); j++) {
            if (arr[j] == 0) swap(arr[i++], arr[j]);
        }
    }

    void sort3(vector<int>& arr) {
        int i = 0, j = arr.size() - 1;
        while (i < j) {
            if (arr[i] == 0)
                i++;
            else
                swap(arr[i], arr[j--]);
        }
    }

    void sort4(vector<int>& arr) {
        int i = 0;
        for (int j = 0; j < arr.size(); i++) {
            if (arr[j] == 0) arr[i++] = arr[j];
        }
        for (; i < arr.size(); i++) arr[i] = 1;
    }
};