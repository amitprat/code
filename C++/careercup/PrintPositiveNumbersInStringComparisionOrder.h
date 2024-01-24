#include "../header.h"

/*
Output top N positive integer in string comparison order. For example, let's say N=1000, then you need to output in string comparison order as below:
1, 10, 100, 1000, 101, 102, ... 109, 11, 110, ...
*/
class PrintPositiveNumbersInStringComparisionOrder {
   public:
    static void test() {
        PrintPositiveNumbersInStringComparisionOrder obj;
        obj.printNumbers(1000);
    }

    void printNumbers(int limit) {
        for (int i = 1; i < 10; i++) {
            printNumbers(to_string(i) + "", limit);
        }
    }

    void printNumbers(string num, int limit) {
        if (stoi(num) > limit)
            return;

        cout << num << " ";
        for (int i = 0; i < 10; i++) {
            printNumbers(num + to_string(i), limit);
        }
    }
};