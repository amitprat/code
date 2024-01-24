#include "../header.h"

/*
https://careercup.com/question?id=19638671

Write a program to find whether a given number is a perfect square or not. You can only use addition and subtraction operation to find a solution with min. complexity.

i/p : 25
o/p : True

i/p : 44
o/p: False
*/

class CheckIfNumberIsPerfectSqaure {
   public:
    static void test() {
        int num = 25;
        CheckIfNumberIsPerfectSqaure obj;
        bool res = obj.IsPerfectSquare(num);
        cout << res << endl;
    }

    bool IsPerfectSquare(int num) {
        int i = 1;
        while (num > 0) {
            num -= i;
            i += 2;
        }

        if (num == 0)
            return true;
        return false;
    }
};