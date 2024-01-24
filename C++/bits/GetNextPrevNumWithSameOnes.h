#include "../header.h"

class GetNextPrevNumWithSameOnes {
   public:
    static void test() {
        GetNextPrevNumWithSameOnes obj;
        int num = 23;
        cout << "Cur : " << num << endl;
        cout << "Next : " << (num = obj.GetNextNum(num)) << endl;
        cout << "Next : " << (num = obj.GetNextNum(num)) << endl;
        cout << "Next : " << (num = obj.GetNextNum(num)) << endl;

        cout << "Cur : " << num << endl;
        cout << "Prev : " << (num = obj.GetPrevNum(num)) << endl;
        cout << "Prev : " << (num = obj.GetPrevNum(num)) << endl;
        cout << "Prev : " << (num = obj.GetPrevNum(num)) << endl;
    }

    int GetNextNum(int num) {
        int c0 = 0, c1 = 0;

        // first first 1
        while (!(num & (1 << c0))) c0++;

        // first next 0
        while (num & (1 << (c0 + c1))) c1++;

        // turn this bit on
        num |= 1 << (c0 + c1);

        // clear all bits right to it
        num &= ~((1 << (c0 + c1)) - 1);

        // set rightmost bits ones
        num |= (1 << (c1 - 1)) - 1;

        return num;
    }

    int GetPrevNum(int num) {
        int c0 = 0, c1 = 0;

        // first first 0
        while (num & (1 << c1)) c1++;

        // first next 1
        while (!(num & (1 << (c0 + c1)))) c0++;

        // clear all bits including it
        num &= (~0) << (c0 + c1 + 1);
        c0--;

        // set leftmost bits ones
        int mask = (1 << (c1 + 1)) - 1;
        mask <<= c0;
        num |= mask;

        return num;
    }
};