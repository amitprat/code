#pragma once
#include "../Header.h"

class AddBinary {
public:
    static void test() {
        AddBinary obj;
        string f = "1101";
        string s = "111";

        cout << f << "+" << s << " = " << obj.add(f, s) << endl;
    }

    string add(string f, string s) {
        string res;
        int carry = 0;

        int n = f.length() - 1, m = s.length() - 1;
        while (n >= 0 && m >= 0) {
            int val = add(f[n--], s[m--], carry);
            carry = val / 2;
            val = val & 1;
            res = to_char(val) + res;
        }

        while (n >= 0) {
            int val = add(f[n--], carry);
            carry = val / 2;
            val = val & 1;
            res = to_char(val) + res;
        }

        while (m >= 0) {
            int val = add(s[m--], carry);
            carry = val / 2;
            val = val & 1;
            res = to_char(val) + res;
        }
        if (carry) res = to_char(carry) + res;

        return res;
    }

    char to_char(int val) {
        return '0' + val;
    }

    int add(char f, char s, int v) {
        int r = (f - '0') + (s - '0') + v;
        return r;
    }

    int add(char f, int v) {
        int r = (f - '0') + v;
        return r;
    }
};