#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5863307617501184

Given a array of positive integers, find all possible triangle triplets that can be formed from this array.
eg: 9 8 10 7
ans: 9 8 10, 9 8 7, 9 10 7, 7 8 10
Note : array not sorted, there is no limit on the array length
*/

class FindPossibleTraingleTriplets {
   public:
    static void test() {
        FindPossibleTraingleTriplets obj;
        vector<int> arr = {9, 8, 7, 10};
        int res = obj.countTraingles(arr);
        cout << "Traingles: " << res << endl;
    }

   public:
    int countTraingles(vector<int>& arr) {
        int count = 0;
        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                for (int k = j + 1; k < arr.size(); k++) {
                    if (arr[i] + arr[j] > arr[k] && arr[i] + arr[k] > arr[j] && arr[j] + arr[k] > arr[i]) {
                        count++;
                    }
                }
            }
        }

        return count / 6;
    }
};