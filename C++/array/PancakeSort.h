#pragma once
#include "../header.h"
using namespace std;

class PancakeSort
{
public:
    static void testReverse(vector<int> arr, int k)
    {
        PancakeSort obj;
        obj.reverse(arr, k);
        cout << "Output: ";
        for (auto i : arr) cout << i << " ";
        cout << endl;
    }

    static void testSort(vector<int> arr)
    {
        PancakeSort obj;
        obj.sort(arr);
        cout << "Output: ";
        for (auto i : arr) cout << i << " ";
        cout << endl;
    }

    void sort(vector<int>& arr)
    {
        int r = arr.size() - 1;
        for (int i = r; i >= 1; i--) {
            int mxi = findMaxIndex(arr, 0, i);
            if (mxi != i) {
                flip(arr, 0, mxi);
                flip(arr, 0, i);
            }
        }
    }

    int findMaxIndex(vector<int> arr, int s, int e)
    {
        int mx = INT_MIN;
        int mxi = INT_MIN;
        for (int i = s; i <= e; i++) {
            if (arr[i] > mx) { mx = arr[i]; mxi = i; }
        }

        return mxi;
    }

    void reverse(vector<int>& arr, int k)
    {
        int start = 0;
        int end = start + k - 1;
        while (end < arr.size()) {
            flip(arr, start, end);
            start = end + 1;
            end = start + k - 1;
        }
        flip(arr, start, arr.size() - 1);
    }

    void flip(vector<int>& arr, int s, int e)
    {
        while (s < e) {
            swap(arr[s++], arr[e--]);
        }
    }
};