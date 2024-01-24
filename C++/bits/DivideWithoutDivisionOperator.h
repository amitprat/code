#include "../header.h"

class DivideWithoutDivisionOperator {
   public:
    static void test() {
        DivideWithoutDivisionOperator obj;
        vector<pair<int, int>> tests = {{-2147483648, -1}};
        for (auto test : tests) {
            cout << obj.divide(test.first, test.second) << endl;
        }
    }

    int divide(int dividend, int divisor) {
        bool sign = true;
        if (dividend < 0 || divisor < 0) sign = false;
        if (dividend < 0 && divisor < 0) sign = true;

        int x = abs(dividend);
        int y = abs(divisor);
        if (x == INT_MIN) x = INT_MAX;
        unsigned int m = 1;
        unsigned int q = 0;

        while (y <= x) {
            y <<= 1;
            m <<= 1;
        }

        while (m > 1) {
            y >>= 1;
            m >>= 1;
            if (x >= y) {
                x -= y;
                q |= m;
            }
        }

        return sign ? q : 0 - q;
    }
};