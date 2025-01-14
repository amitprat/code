#pragma once
#include "../header.h"

class BitsOperations {
   public:
    static void test() {
        BitsOperations obj;

        vector<int> nums = {0, 1, 2, 3, 4};
        for (auto& num : nums) {
            cout << format("Num={}, position={} is set {}", num, 0, obj.isset(num, 0));
        }
    }

   public:
    bool isset(int a, int index) {
        return a & (1 << index);
    }

    int Union(int a, int b) {
        return a | b;
    }

    int insersection(int a, int b) {
        return a & b;
    }

    int substraction(int a, int b) {
        return a & ~b;
    }

    int negation(int a) {
        return ~a;
    }

    int set(int a, int index) {
        a |= 1 << index;
        return a;
    }

    int clear(int a, int index) {
        a &= ~(1 << index);
        return a;
    }

    int extractLastSetBit(int a) {
        a = a & ~(a - 1);
        return a;
    }

    int removeLastSetBit(int a) {
        a = a & ~(a - 1);
        return a;
    }

    int getAllOnes() {
        return ~0;
    }

    bool isPowerOf2(int n) {
        return n && !(n & (n - 1));
    }

    bool isPowerOf2_1(int n) {
        return (n & ~(n - 1)) == n;
    }

    bool isPowerOf4(int n) {
        return n && !(n & (n - 1)) && !(n & 0xAAAAAAAA);
    }

    bool isPowerOf4_1(int n) {
        return ((n > 0) && ((n & n - 1) == 0) && (n % 3 == 1));
    }
};