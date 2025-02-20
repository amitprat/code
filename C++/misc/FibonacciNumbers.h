#pragma once
#include "../header.h"

class FibonacciNumbers {
   public:
    /*
    Fib series : 0 1 1 2 3 5 8 13 21 ....
    /*print nth fibonacci number using recursion, T = exponential time */
    static int fibn(int n) {
        if (n <= 1) return n;
        return fibn(n - 1) + fibn(n - 2);
    }

   public:
    /* T = O(n) time algorithms
     using extra space */
    static int fibn1(int n) {
        int fib[n + 1];
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i <= n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }

        return fib[n];
    }

   public:
    /* without using any extra space */
    static int fibn2(int n) {
        if (n == 0) return 0;

        int a = 0;
        int b = 1;
        int c = b;
        for (int i = 2; i <= n; i++) {
            a = b;
            b = c;
            c = a + b;
        }

        return b;
    }

   public:
    /*print fib series upto nth element using extra space*/
    static void fib1(int n) {
        int fib[n + 1];
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i <= n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }

        for (int i = 0; i < n; i++) {
            cout << fib[i] << " ";
        }
        cout << endl;
    }

    /*print fib series upto nth element without using any extra space*/
    static void fib2(int n) {
        int a = 0;
        int b = 1;
        int c = b;

        cout << a << " ";
        for (int i = 2; i <= n; i++) {
            cout << b << " ";
            a = b;
            b = c;
            c = a + b;
        }
        cout << endl;
    }

   public:
    static void test() {
        for (int i = 0; i < 10; i++) {
            cout << "fib(" << i << ") = " << fibn(i) << " , " << fibn1(i) << " , " << fibn2(i) << endl;
        }
    }
};