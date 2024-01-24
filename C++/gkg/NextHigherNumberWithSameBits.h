#pragma once
#include "../Header.h"

class NextHigherNumber {
   public:
    static void test() {
        NextHigherNumber obj;
        for (int i = 0; i < 20; i++) {
            cout << setw(32) << "Original Number : " << to_bin(i) << endl;
            int n = obj.next(i);
            cout << setw(32) << "Next Higher Number: " << to_bin(n) << endl;

            cout << endl;
        }
    }

    int next(int num) {
        int zeros = 0, ones = 0;
        int l = findFirstSetBitPos(num, zeros);
        int r = findFirstUnsetBitPos(num, l, ones);
        if (r == -1) {
            cout << "No higher number possible" << endl;
            return num;
        }

        setBit(num, r);
        clearBit(num, r - 1);
        ones--;

        int mask = -1;
        mask <<= (zeros + ones);

        int pos = (1 << ones) - 1;
        mask |= pos;

        return num & mask;
    }

   private:
    int findFirstSetBitPos(int num, int& zeros) {
        if (!num) return -1;
        while (!(num & (1 << zeros))) zeros++;
        return zeros;
    }

    int findFirstUnsetBitPos(int num, int offset, int& ones) {
        if (num == INT_MAX) return -1;
        while (num & (1 << (ones + offset))) ones++;
        return ones + offset;
    }

    int setBit(int& n, int pos) {
        n = n | (1 << pos);
        return n;
    }

    int clearBit(int& n, int pos) {
        n = n & ~(1 << pos);
        return n;
    }
};