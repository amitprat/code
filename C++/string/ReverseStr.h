#pragma once
#include "../header.h"

class ReverseStr {
public:
    static void test() {
        ReverseStr obj;
        string str = "this is test";
        cout << obj.reverseRec(str) << endl;

        str = "this is test";
        cout << obj.reverseIter(str) << endl;

        str = "";
        cout << obj.reverseRec(str) << endl;

        str = "";
        cout << obj.reverseIter(str) << endl;

        str = "a";
        cout << obj.reverseRec(str) << endl;

        str = "a";
        cout << obj.reverseIter(str) << endl;

        str = "ab";
        cout << obj.reverseRec(str) << endl;

        str = "ab";
        cout << obj.reverseIter(str) << endl;

        str = "aa";
        cout << obj.reverseRec(str) << endl;

        str = "aa";
        cout << obj.reverseIter(str) << endl;

        str = "abc";
        cout << obj.reverseRec(str) << endl;

        str = "abc";
        cout << obj.reverseIter(str) << endl;

        str = "abcd";
        cout << obj.reverseRec(str) << endl;

        str = "abcd";
        cout << obj.reverseIter(str) << endl;
    }

    string reverseRec(string str) {
        reverseRec(str, 0, str.length() - 1);
        return str;
    }

    string reverseIter(string str) {
        int s = 0, e = str.length() - 1;
        while (s < e) {
            swap(str[s++], str[e--]);
        }
        return str;
    }

    void reverseRec(string& str, int s, int e) {
        if (s >= e) return;
        if (s + 1 == e) { swap(str[s], str[e]); return; }
        reverseRec(str, s + 1, e - 1);
        swap(str[s], str[e]);
    }
};