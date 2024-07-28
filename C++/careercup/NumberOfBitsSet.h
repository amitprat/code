#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=4818944212860928

Given an int, write code to return the number of bits that are 1 in O(m) time, where m is the number of bits that are 1.
*/

class NumberOfBitsSet {
   public:
    int count(int n) {
        int cnt = 0;
        while (n) {
            n &= (n - 1);
            cnt++;
        }

        return cnt;
    }
};