#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=14370695
Implement the plusplus operator when we are getting the input as integer array = { 9,9,9,9 }.output will be {1,0,0,0,0}
*/
class IncrementNumberByOne {
   public:
    static void test() {
        IncrementNumberByOne obj;

        vector<vector<int>> inputs = {
            {0},
            {1},
            {1, 0},
            {1, 1},
            {1, 1, 9},
            {1, 0, 1},
            {9, 9, 9, 9}};

        for (auto& arr : inputs) {
            auto res = obj.increaseArrayNumberByOne(arr);
            cout << format("{} + {} = {}", to_string(arr), 1, to_string(res)) << endl;
        }
    }

   private:
    vector<int> increaseArrayNumberByOne(const vector<int>& arr) {
        int n = arr.size();
        int carry = 1;  // to add 1.

        vector<int> result(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            int sum = arr[i] + carry;
            result[i + 1] = sum % 10;  // result might be +1
            carry = sum / 10;
        }

        if (carry)
            result[0] = carry;
        else {
            result.erase(result.begin());
        }

        return result;
    }
};