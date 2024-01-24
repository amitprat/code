#pragma once
#include "../Header.h"

class BinarySum {
public:
    static void test() {
        int a[2][4] = { 3, 6, 9, 12, 15, 18, 21, 24 };
        cout << *(a[1] + 2) <<" "<< * (*(a + 1) + 2) <<" "<< 2[1[a]];
        cout << endl;

        string f = "101101";
        string s = "111101";

        string out = add(f, s);
        cout << out << endl;
    }

    static string add(string f, string s) {
        int carry = 0;
        int n = 0;
        string out(f.length() + 1, '0');

        add(f, s, out, carry, n);
        if (carry) {
            out[0] = carry + '0';
            return out;
        }

        return out.substr(1);
    }

    static void add(string f, string s, string& out, int& carry, int n) {
        if (n == f.length()) return;

        add(f, s, out, carry, n + 1);
        int val = f[n] - '0' + s[n] - '0' + carry;
        out[n+1] = val % 2 + '0';
        carry = val / 2;
    }
};