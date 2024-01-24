#pragma once
#include "../Header.h"

class JosephusProblem
{
public:
    static void test()
    {
        vector<int> arr = { 1,2,3,4,5 };
        int n = 5;
        int k = 2;

        josephus(arr, n, k, 0);
    }

    static void josephus(vector<int>& arr, int n, int k, int index)
    {
        if (n == 1)
        {
            cout << arr[0] << endl;
            return;
        }

        index = (index + k) % n;
        cout << "Deleting index: " << index << ", val: " << arr[index] << endl;
        arr.erase(arr.begin() + index);

        josephus(arr, n - 1, k, index);
    }
};
// 1 2 3 4 5
// 1 2 4 5
// 2 4 5
// 2 4
// 2