#pragma once
#include "../Header.h"

/*
Implement binary addition of two strings.
For example "101101" and "111101" equal "1101010"
You cannot use any type conversion, operate only with strings.

https://careercup.com/question?id=5699214707785728
*/

class AddBinaryStrings {
   public:
    static void test() {
        AddBinaryStrings obj;

        // Add binary strings of different sizes
        {
            vector<pair<string, string>> inputs = {
                {"10101010", "00100011"},
                {"101101", "111101"},
                {"1", "101011"},
                {"01011", "0"},
                {"", "101010"}};

            for (auto &input : inputs) {
                string res1 = obj.addBinaryStringsOfDifferentSizes(input.first, input.second);
                string res2 = obj.addBinaryStringsOfDifferentSizes2(input.first, input.second);

                assert(res1 == res2);
                cout << format("{:>8} + {:>8} = {:>8}", input.first, input.second, res1) << endl;
            }
        }

        // Add binary strings of same size.
        {
            string first = "101101";
            string second = "111101";

            string result = obj.addBinaryStringsOfSameSize(first, second);
            assert("1101010" == result);
            cout << format("{:>8} + {:>8} = {:>8}", first, second, result);
        }
    }

   private:
    // Add binary string of different sizes without prepending, but using different pointers for both.
    string addBinaryStringsOfDifferentSizes(string f, string s) {
        string res;
        int carry = 0;

        // add the common part from end
        int n = f.length() - 1, m = s.length() - 1;
        while (n >= 0 && m >= 0) {
            int val = add(f[n--], s[m--], carry);
            carry = val / 2;
            val = val & 1;
            res = to_char(val) + res;
        }

        // If elements in one of the string is still remaining.
        // add the remaining part from back +  carry
        while (n >= 0) {
            int val = add(f[n--], carry);
            carry = val / 2;
            val = val & 1;
            res = to_char(val) + res;
        }

        // add the remaining part from back +  carry
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

   private:
    // Add binary string of different sizes by prepending '0's.
    string addBinaryStringsOfDifferentSizes2(string s1, string s2) {
        int l1 = s1.length();
        int l2 = s2.length();
        int l = max(l1, l2);

        if (l1 != l2) {
            if (l1 < l2)
                s1 = prepend(s1, l2 - l1, '0');
            else
                s2 = prepend(s2, l1 - l2, '0');
        }

        int carry = 0;
        string s3 = addBinary(s1, s2, 0, l, carry);
        if (carry) s3 = "1" + s3;

        return s3;
    }

    string addBinary(string s1, string s2, int idx, int l, int &carry) {
        if (idx == l) return "";

        string next = addBinary(s1, s2, idx + 1, l, carry);

        int res = carry + s1[idx] - '0' + s2[idx] - '0';
        carry = res / 2;
        string cur = res & 1 ? "1" : "0";

        return cur + next;
    }

    string prepend(string &str, int d, char ch) {
        return string(d, ch) + str;
    }

   private:
    // sum binary string of same size.
    string addBinaryStringsOfSameSize(string f, string s) {
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

    void add(string f, string s, string &out, int &carry, int n) {
        if (n == f.length()) return;

        add(f, s, out, carry, n + 1);
        int val = f[n] - '0' + s[n] - '0' + carry;
        out[n + 1] = val % 2 + '0';
        carry = val / 2;
    }
};