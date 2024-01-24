#include "../header.h"

class SqrtOfNumber
{
public:
    static void test()
    {
        SqrtOfNumber obj;
        int num = 244;
        double val1 = obj.sqrt1(num);
        cout << format("Sqrt value of {} is {}.\n", num, val1);

        double val2 = obj.sqrt1(244);
        cout << format("Sqrt value of {} is {}.\n", num, val2);
    }

private:
    double sqrt1(int num)
    {
        double x = 1, y = num;
        double e = 0.00001;
        while (abs(x - y) > e)
        {
            x = (x + y) / 2;
            y = (double)num / x;
        }

        return x;
    }

    int sqrt2(int num)
    {
        int s = 1, e = num;
        while (s <= e)
        {
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
};