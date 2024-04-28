#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=14578788
https://www.careercup.com/question?id=5652354158297088

You're given an array of integers(eg [3,4,7,1,2,9,8]) Find the index of values that satisfy A+B = C+D, where A,B,C & D are integers values in the array.
Eg: Given [3,4,7,1,2,9,8] array
The following
3+7 = 1+9 satisfies A+B=C+D
so print (0,2,3,5)
*/

class FindFourSum {
   public:
    static void test() {
        {
            vector<int> arr = {3, 4, 7, 1, 2, 9, 8};

            auto result1 = fourSum(arr);
            cout << result1 << endl;

            auto result2 = fourSum2(arr);
            cout << result2 << endl;

            auto result3 = fourSum3(arr);
            cout << to_string(result3.first) << ", " << to_string(result3.second) << endl;
        }
        cout << endl;

        {
            vector<int> arr = {3, 7, 1, 2, 3, 1, 2};

            auto v = fourSum3(arr);
            cout << to_string(v.first) << ", " << to_string(v.second) << endl;
        }
    }

   private:
    // this might print duplicate element which is incorrect.
    static vector<int> fourSum(vector<int> arr) {
        unordered_map<int, vector<pair<int, int>>> sumPair;
        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                int s = arr[i] + arr[j];
                sumPair[s].push_back({i, j});
            }
        }

        for (auto e : sumPair) {
            if (e.second.size() > 1) {
                cout << "Pairs with sum " << e.first << " = ";
                for (auto p : e.second) {
                    cout << "{" << arr[p.first] << "," << arr[p.second] << "}, ";
                }
                cout << endl;
            }
        }

        return {};
    }

   private:
    static vector<int> fourSum2(vector<int> arr) {
        unordered_map<int, pair<int, int>> pairSumMap;

        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                int s = arr[i] + arr[j];
                if (pairSumMap.find(s) == pairSumMap.end()) {
                    pairSumMap[s] = {i, j};
                } else {
                    auto old = pairSumMap[s];
                    if (old.first != i && old.first != j && old.first != j && old.second != j) {
                        return {arr[old.first], arr[old.second], arr[i], arr[j]};
                    }
                }
            }
        }

        return {};
    }

   private:
    static pair<pair<int, int>, pair<int, int>> fourSum3(vector<int> arr) {
        unordered_map<int, pair<int, int>> pairSumMap;

        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                int s = arr[i] + arr[j];
                if (pairSumMap.find(s) == pairSumMap.end()) {
                    pairSumMap[s] = {i, j};
                } else {
                    auto old = pairSumMap[s];
                    if (old.first != i && old.first != j && old.second != i && old.second != j) {
                        return {{arr[old.first], arr[old.second]}, {arr[i], arr[j]}};
                    }
                }
            }
        }

        return {};
    }
};