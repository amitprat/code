#include "../header.h"

class SqrtOfNumber {
   private:
    double e = 0.00001;

   public:
    static void test() {
        SqrtOfNumber obj;
        int num = 244;
        double val1 = obj.sqrt1(num);
        cout << format("Sqrt value of {} is {}.\n", num, val1);

        double val2 = obj.sqrt1(244);
        cout << format("Sqrt value of {} is {}.\n", num, val2);
    }

   private:
    /*
     * Reference : http://www.geeksforgeeks.org/square-root-of-a-perfect-square/
     * Babylonian method for square root
     * Algorithm:
     * This method can be derived from (but predates) Newton–Raphson method.
     *
     * 1 Start with an arbitrary positive start value x (the closer to the
     * root, the better).
     * 2 Initialize y = 1.
     * 3. Do following until desired approximation is achieved.
     * a) Get the next approximation for root using average of x and y
     * b) Set y = n/x
     */
    double sqrt1(int num) {
        double x = 1, y = num;
        double e = 0.00001;
        while (abs(x - y) > e) {
            x = (x + y) / 2;
            y = (double)num / x;
        }

        return x;
    }

    // using binary search method
    int sqrt2(int num) {
        int s = 1, e = num;

        while (s <= e) {
            int m = (s + e) / 2;
            if (m * m == num)
                return m;
            else if (m * m < num)
                s = m + 1;
            else
                e = m - 1;
        }

        return -1;
    }

   private:
    /*This method can only work if N is perfect square */
    unsigned int sqrt3(unsigned int n) {
        unsigned int x = n;
        unsigned int y = 1;

        while (x > y) {
            x = (y + y) / 2;
            y = n / x;
        }

        return x;
    }
};