#include "../header.h"

class MultiplyDivisionWithRecursion {
   public:
    static void test() {
        int a = 6, b = 3;
        std::cout << "Multiply: " << multiply(a, b) << std::endl;
        std::cout << "Divide: " << divide(a, b) << std::endl;
    }

   private:
    static int multiply(int a, int b) {
        if (b == 0) return 0;
        if (b == 1) return a;
        if (b < 0) return -multiply(a, -b);  // Handle negative multiplication

        auto half = multiply(a, b / 2);
        return half + half + (b % 2 == 1 ? a : 0);
    }

    static int divide(int a, int b) {
        if (a <= 0) return 0;
        if (b == 0) throw std::invalid_argument("Division by zero");

        int mul = 1, sum = b;
        while (sum + sum <= a) {
            sum += sum;
            mul += mul;
        }

        return mul + divide(a - sum, b);
    }
};