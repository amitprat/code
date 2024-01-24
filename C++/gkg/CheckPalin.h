#pragma once
#include "../Header.h"

class CheckPalin {
public:
    static void test() {
        CheckPalin obj;
        string str = "A man, a plan, a canal: Panama.";

        cout << "Is Palin " << obj.isPalin(str) << endl;
    }

    bool isPalin(string str) {
        int i = 0, j = str.length()-1;

        while (i < j) {
            if (!valid(str[i])) {
                i++; continue;
            }
            if (!valid(str[j])) {
                j--; continue;
            }
            if (tolower(str[i]) != tolower(str[j])) return false;
            i++; j--;
        }

        return true;
    }

    bool valid(char ch) {
        return ((ch >= '0' && ch <= '9') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z'));
    }
};