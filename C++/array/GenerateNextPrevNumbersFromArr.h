#pragma once
#include "../header.h"

class GenerateNextPrevNumbersFromArr {
   public:
    static void test() {
        GenerateNextPrevNumbersFromArr obj;
        vector<vector<int>> vals = {
            {1},
            {5},
            {3},
            {2},
            {1, 0},
            {1},
            {9, 9},
            {1, 0, 0},
            {0},
            {9, 9, 9},
            {1, 0, 0, 1}};

        for (auto& val : vals) {
            cout << format("Input={}", to_string(val)) << ", ";

            auto next = obj.getNext(val);
            cout << format("Next={}", to_string(next)) << ", ";

            auto prev = obj.getPrev(val);
            cout << format("Prev={}", to_string(prev)) << endl;
        }
    }

private:
    vector<int> getNext(vector<int> val) {
        int sz = val.size() - 1;

        int carry = 1;  // to add 1
        for (int i = sz; i >= 0; i--) {
            int cur = val[i];
            int newVal = cur + carry;
            
            carry = newVal / 10;
            val[i] = newVal % 10;
        }

        if (carry) val.insert(val.begin(), carry);

        return val;
    }

private:
    vector<int> getPrev(vector<int> val) {
        int sz = val.size() - 1;

        int borrow = 1;  // to substract 1
        for (int i = sz; i >= 0; i--) {
            int cur = val[i];
            int newVal = cur - borrow;

            if (newVal < 0) {
                newVal += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            val[i] = newVal % 10;
        }

        if (borrow) val[0] -= 1;
        if (val[0] == 0) val.erase(val.begin());
        if (val.size() == 0) val.push_back(0);

        return val;
    }
};