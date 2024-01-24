#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class FindPermInDistance
{
public:
    static void test(vector<int> inputs)
    {
        FindPermInDistance obj;
        for (auto input : inputs) {
            cout << "Input: " << input << ", ";
            auto res = obj.calculate(input);
            for (auto i : res) {
                cout << "{";
                for (auto j : i) {
                    cout << j << " ";
                }
                cout << "}, ";
            }
            cout << endl;
        }
    }

    set<vector<int>> calculate(int input)
    {
        set<vector<int>> res;
        vector<int> arr;
        for (int i = 0; i < input * 2; i++) arr.push_back(0);

        calculate(arr, res, input);

        return res;
    }

private:
    void calculate(vector<int> arr, set<vector<int>>& res, int n)
    {
        unordered_set<int> uniques;
        for (auto val : arr) if (val != 0) uniques.insert(val);
        if (uniques.size() == n) {
            res.insert(arr);
            return;
        }

        for (int i = 1; i <= n; i++) {
            if (find(uniques.begin(), uniques.end(), i) != uniques.end()) continue;

            for (int j = 0; j < arr.size() - i - 1; j++) {
                if (arr[j] == 0 && arr[j + i + 1] == 0) {
                    arr[j] = i;
                    arr[j + i + 1] = i;
                    calculate(arr, res, n);
                    arr[j] = 0;
                    arr[j + i + 1] = 0;
                }
            }
        }
    }
};