#include "../header.h"

class MultiplyWithoutMultiplicationOperator {
   public:
    static void test() {
        MultiplyWithoutMultiplicationOperator obj;

        int num1 = 7;
        int num2 = 19;

        int result = obj.multiply(num1, num2);
        std::cout << num1 << " * " << num2 << " = " << result << std::endl;
    }

   private:
    int multiply(int a, int b) {
        int result = 0;
        while (b) {
            if (b & 1) result += a;
            a <<= 1;
            b >>= 1;
        }
        return result;
    }
};