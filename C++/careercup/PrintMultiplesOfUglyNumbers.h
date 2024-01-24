#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=23823662


Given an equation in the form 2^i * 3^j * 5^k * 7^l where i,j,k,l >=0 are integers.write a program to generate numbers from that equation in sorted order efficiently.

for example numbers from that equation will be in the order 2,3,5,6,7,8,9.....and so on..

These are basically referred to as ugly numbers . Here is the code for it:
a. Take variables for multiples of 2,3,5,7.
b. Everytime find a minimum of the multiple.
c. Store 1 in the first index as it is multiple of all.
d. Find the minimum of all the multiples of 2,3,5,7. Whenever that minimum is equal to any of the multiples.
Store that multiple in the indexes assigned for 2,3,5,7 and also multiply that element with the number to get
the next higher multiple in next iteration.
*/
class PrintMultiplesOfUglyNumbers {
   public:
    static void test() {
        PrintMultiplesOfUglyNumbers obj;
        vector<int> inputs = {0, 1, 2, 10, 20};
        for (auto& num : inputs) {
            auto res1 = obj.printAllMultiples(num);
            auto res3 = obj.printAllMultiplesCareercup(num);
            obj.printKUglyNumbersUsingQueue(num);

            assert(res1 == res3);
            cout << to_string(res1) << endl;
        }
    }

   private:
    vector<int> printAllMultiples(int n) {
        if (n == 0) return {};

        vector<int> result(n);
        result[0] = 1;
        int i2 = 0, i3 = 0, i5 = 0, i7 = 0;
        for (int i = 1; i < n; i++) {
            int minMultiple = min(min(2 * result[i2], 3 * result[i3]), min(5 * result[i5], 7 * result[i7]));
            result[i] = minMultiple;
            if (minMultiple == 2 * result[i2]) i2++;
            if (minMultiple == 3 * result[i3]) i3++;
            if (minMultiple == 5 * result[i5]) i5++;
            if (minMultiple == 7 * result[i7]) i7++;
        }

        return result;
    }

   private:
    void printKUglyNumbersUsingQueue(int n) {
        queue<int> q2, q3, q5;
        vector<int> numbers;
        numbers.push_back(1);
        q2.push(2);
        q3.push(3);
        q5.push(5);

        while (n-- > 1) {
            int mn = min(q2.front(), min(q3.front(), q5.front()));
            numbers.push_back(mn);
            if (mn == q5.front()) {
                q5.pop();
            } else if (mn == q3.front()) {
                q3.pop();
                q3.push(3 * mn);
            } else if (mn == q2.front()) {
                q2.pop();

                q2.push(2 * mn);
                q3.push(3 * mn);
            }

            q5.push(5 * mn);
        }

        cout << "K ugly numbers = " << to_string(numbers) << endl;
    }

   private:
    vector<int> printAllMultiplesCareercup(int n) {
        if (n == 0) return {};

        unsigned* ugly = (unsigned*)malloc(n * sizeof(unsigned*));
        unsigned next_multiple_2 = 2;
        unsigned next_multiple_3 = 3;
        unsigned next_multiple_5 = 5;
        unsigned next_multiple_7 = 7;
        unsigned i2 = 0, i3 = 0, i5 = 0, i7 = 0;
        ugly[0] = 1;

        for (int i = 1; i < n; i++) {
            unsigned next_ugly_no = min4(next_multiple_2, next_multiple_3, next_multiple_5, next_multiple_7);
            *(ugly + i) = next_ugly_no;

            if (next_ugly_no == next_multiple_2) {
                i2 = i2 + 1;
                next_multiple_2 = ugly[i2] * 2;
            }
            if (next_ugly_no == next_multiple_3) {
                i3 = i3 + 1;
                next_multiple_3 = ugly[i3] * 3;
            }
            if (next_ugly_no == next_multiple_5) {
                i5 = i5 + 1;
                next_multiple_5 = ugly[i5] * 5;
            }
            if (next_ugly_no == next_multiple_7) {
                i7 = i7 + 1;
                next_multiple_7 = ugly[i7] * 7;
            }
        }

        vector<int> result;
        for (int i = 0; i < n; i++) result.push_back(ugly[i]);
        return result;
    }

    int min4(int a, int b, int c, int d) {
        return min(a, min(b, min(c, d)));
    }
};