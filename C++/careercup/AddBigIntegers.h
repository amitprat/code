#include "../header.h"
/*
https://www.careercup.com/question?id=14370695

Implement the plusplus operator when we are getting the input as integer array = { 9,9,9,9 }.output will be {1,0,0,0,0}
*/

class IncrementNumberByOne {
   public:
    static void test() {
        int a[4] = {9, 9, 9, 9};
        IncrementNumberByOne obj;
        obj.increaseby1(a, 4);
    }

   private:
    void increaseby1(int a[], int n) {
        int i;
        int carry = 1;
        for (i = n - 1; i >= 0; i--) {
            a[i] = a[i] + carry;
            if (a[i] >= 10) {
                carry = 1;
                a[i] = a[i] % 10;
            } else
                carry = 0;
        }

        if (carry == 0)  // no need to make any extra space for case as 2789
        {
            for (i = 0; i < n; i++)
                printf("%d", a[i]);
        }

        else  // make extra space for case as 9999
        {
            int result[n + 1];
            result[0] = 1;
            for (i = 1; i < n + 1; i++) {
                result[i] = a[i - 1];
            }
            for (i = 0; i < n + 1; i++)
                printf("%d", result[i]);
        }
    }
};