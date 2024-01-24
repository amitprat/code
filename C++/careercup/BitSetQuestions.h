#include "../header.h"

class BitSetQuestions {
   public:
    static void test() {
    }

   private:
    int countSetBits(int n) {
        int num = 0;
        while (n) {
            num++;
            n& = (n - 1);
        }

        return num;
    }

    int bitsSwapRequired(int a, int b) {
        int cnt = 0;
        for (int c = a ^ b; c != 0; c = c & (c - 1)) {
            cnt++;
        }

        return cnt;
    }

    int nextNumberWithSameSetOfBits(int n) {
        int c = n;
        int c0 = 0, c1 = 0;

        // find first 1
        while (c && (c & 1 == 0)) c0++;

        // find next 0
        while (c & 1 == 1) c1++;

        int p = c0 + c1;

        // Set this 1
        n |= (1 << p);
        c1--;

        // Set all bits to 0
        n &= ~(1 << (p - 1));

        // Set last bits to 1
        n |= (1 << c1) - 1;

        return n;
    }

    void swapEvenOddBits(int n) {
        return ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    }
};