#pragma once
#include "../Header.h"

class PrintStairs {
public:
    static void test() {
        PrintStairs obj;

        obj.printStairs(3, 3);
    }

    void printStairs(int n, string prefix = "") {
        if (n == 0) { cout << prefix << " "; return; }
        if (n < 0) return;
        printStairs(n - 1, prefix + " " + "1");
        printStairs(n - 2, prefix + " " + "2");
    }

    void printStairs(int n, int m, string prefix = "") {
        if (n == 0) { cout << prefix << " "; return; }
        if (n < 0) return;

        for (int j = 1; j <= m; j++) {
            printStairs(n - j, m, prefix + " " + std::to_string(j));
        }
    }
};