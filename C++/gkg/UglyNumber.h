#pragma once
#include "../Header.h"

class UglyNumber {
public:
    static void test() {
        int n = 10;
        printKUglyNumbers(n);
        cout << n << "th Ugly no = " << kthUglyNumber(n) << endl;

        printKUglyNumbersUsingQueue(n);
        cout << n << "th Ugly no = " << kthUglyNumbersUsingQueue(n) << endl;
    }

    static void printKUglyNumbers(int n) {
        vector<int> numbers;
        numbers.push_back(1);
        int i2 = 0, i3 = 0, i5 = 0;

        while (n-- > 1) {
            int mn = min(2 * numbers[i2], min(3 * numbers[i3], 5 * numbers[i5]));
            numbers.push_back(mn);
            if (mn == 2 * numbers[i2]) i2++;
            if (mn == 3 * numbers[i3]) i3++;
            if (mn == 5 * numbers[i5]) i5++;
        }

        cout << "K ugly numbers = " << to_string(numbers) << endl;
    }

    static int kthUglyNumber(int n) {
        vector<int> numbers;
        numbers.push_back(1);
        int i2 = 0, i3 = 0, i5 = 0;
        int mn = 1;

        while (n-- > 1) {
            mn = min(2 * numbers[i2], min(3 * numbers[i3], 5 * numbers[i5]));
            numbers.push_back(mn);
            if (mn == 2 * numbers[i2]) i2++;
            if (mn == 3 * numbers[i3]) i3++;
            if (mn == 5 * numbers[i5]) i5++;
        }

        return mn;
    }

    static void printKUglyNumbersUsingQueue(int n) {
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
            }
            else if (mn == q3.front()) {
                q3.pop();
                q3.push(3 * mn);
            }
            else if (mn == q2.front()) {
                q2.pop();

                q2.push(2 * mn);
                q3.push(3 * mn);
            }

            q5.push(5 * mn);
        }

        cout << "K ugly numbers = " << to_string(numbers) << endl;
    }

    static int kthUglyNumbersUsingQueue(int n) {
        if (n == 0) return 0;
        queue<int> q2, q3, q5;
        vector<int> numbers;
        numbers.push_back(1);
        q2.push(2);
        q3.push(3);
        q5.push(5);
        int mn = 1;

        while (n-- > 1) {
            mn = min(q2.front(), min(q3.front(), q5.front()));
            numbers.push_back(mn);
            if (mn == q5.front()) {
                q5.pop();
            }
            else if (mn == q3.front()) {
                q3.pop();
                q3.push(3 * mn);
            }
            else if (mn == q2.front()) {
                q2.pop();

                q2.push(2 * mn);
                q3.push(3 * mn);
            }

            q5.push(5 * mn);
        }

        return mn;
    }
};