#include "../header.h"

/*
https://www.careercup.com/question?id=5680043955060736

Output top N positive integer in string comparison order. For example, let's say N=1000, then you need to output in string comparison order as below:
1, 10, 100, 1000, 101, 102, ... 109, 11, 110, ...

public static void main(String[] args) {
    for(int i=1;i<;10;i++)
    printRec(""+i, 1000);
}

static void printRec(String str, int n){
    if(Integer.parseInt(str) > n)
        return;
    System.out.println(str);
    for(int i=0;i<;10;i++)
        printRec(str+i,n);
}
*/
class PrintPositiveNumbersInStringComparisionOrder {
   public:
    static void test() {
        PrintPositiveNumbersInStringComparisionOrder obj;
        obj.printNumbers(1000);
    }

   private:
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