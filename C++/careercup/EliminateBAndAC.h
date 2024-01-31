#pragma once
#include "../Header.h"
/*
https://www.careercup.com/question?id=18460667

Eliminate all ‘b’ and ‘ac’ in an array of characters, you have to replace them in-place, and you are only allowed to iterate over
the char array once.

Examples:
abc -> ac
ac->''
react->rt
*/
// It can be solved using two pointers thats it :-)
class EliminateBAndAC {
   public:
    static void test() {
        EliminateBAndAC obj;

        string str = "babcaaabcccbccabbc";
        char *charArr = const_cast<char *>(str.c_str());
        obj.remove1(charArr);
        cout << charArr << endl;

        string str2 = "babcaaabcccbccabbc";
        str2 = obj.remove2(str2);
        cout << str2 << endl;
    }

   private:
    void remove1(char *str) {
        int i = 0;
        char *q = str;
        while (*q) {
            if (*q == 'b')
                q++;
            else {
                if (*q == 'c' && (i > 0 && str[i - 1] == 'a')) {
                    q++;
                    i--;
                } else {
                    str[i] = *q;
                    q++;
                    i++;
                }
            }
        }
        str[i] = '\0';
    }

   private:
    string remove2(string str) {
        int i = 0, j = 0;
        while (j < str.length()) {
            if (str[j] == 'b')
                j++;
            else if (str[j] == 'c' && (i > 0 && str[i - 1] == 'a')) {
                j++;
                i--;
            } else
                str[i++] = str[j++];
        }

        return str.substr(0, i);
    }
};