#pragma once
#include "../header.h"
using namespace std;

class SortBinaryArr
{
public:
    static void test(vector<int> v)
    {
        SortBinaryArr obj;
        cout << "Input: ";
        for (auto i : v) cout << i << " ";
        cout << "Output: ";
        obj.sort(v);
        for (auto i : v) cout << i << " ";
        cout << endl;
    }

    void sort(vector<int>& v)
    {
        int pos = v.size() - 1;
        for (int i = v.size() - 1; i >= 0; i--) {
            if (v[i] != 0) v[pos--] = v[i];
        }
        for (int i = pos; i >= 0; i--) v[i] = 0;
    }
};