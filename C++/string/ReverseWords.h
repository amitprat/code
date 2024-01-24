#pragma once
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
using namespace std;

class ReverseWords
{
public:
    static void test()
    {
        ReverseWords obj;
        string str = "This is test string";

        cout << "Original String:- " << str << endl;;
        obj.reverse(str);
        cout << "Reversed String:- " << str << endl;

        str = "This is one more example to test approach";

        cout << "Original String:- " << str << endl;;
        obj.reverse(str);
        cout << "Reversed String:- " << str;
    }

    void reverse(string& str)
    {
        int s = 0;
        int e = str.length() - 1;
        reverseChars(str, s, e);

        for (int i = 0; i <= e; i++) {
            if (str[i] == ' ') {
                reverseChars(str, s, i - 1); s = i + 1;
            }
        }
        if (s != 0) reverseChars(str, s, e);
    }

private:
    void reverseChars(string& str, int s, int e) {
        while (s < e) {
            swap(str[s++], str[e--]);
        }
    }
};