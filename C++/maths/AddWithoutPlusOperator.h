#include "../header.h"

class AddWithoutPlusOperator {
   public:
    static void test() {
        AddWithoutPlusOperator obj;
        for (int i = 0; i < 10; i++) {
            cout << i << " + " << (i + 1) << " = " << obj.sum(i, i + 1) << endl;
        }
        return 0;
    }

   private:
    int sum(int a, int b) {
        while (b) {
            int tmp = (a & b) << 1;  // carry
            a = a ^ b;
            b = tmp;
        }
        return a;
    }
};