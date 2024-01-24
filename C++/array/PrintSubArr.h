#pragma once
#include "../header.h"
using namespace std;

class PrintSubArr
{
public:
    static void test()
    {
        PrintSubArr obj;
        vector<int> v = { 2,3,5,7 };
        int k = 30;
        auto res = obj.findSubArrays(v, k);
        for (auto i : res) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }

        cout << "Count = " << obj.countSubArr(v, k) << endl;
    }

    vector<vector<int>> findSubArrays(vector<int> v, int k)
    {
        vector<vector<int>> result;
        int i = 0;
        int j = 0;
        int cur = 1;
        vector<int> subResult;
        while (j < v.size()) {
            if (cur * v[j] < k) {
                cur *= v[j];
                subResult.push_back(v[j++]);
                result.push_back(subResult);
            }
            else {
                cur = 1;
                i++;
                j = i;
                subResult.clear();
            }
        }

        return result;
    }

    int countSubArr(vector<int> v, int k)
    {
        int start = 0;
        int end = 0;
        int prod = 1;
        int cnt = 0;
        while (start <= end && end < v.size()) {
            if (prod * v[end] < k) {
                prod *= v[end];
                cnt += end - start + 1;
                end++;
            }
            else {
                prod /= v[start++];
            }
        }

        return cnt;
    }
};