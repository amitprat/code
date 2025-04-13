#pragma once
#include "../header.h"

/*
Problem: Replace spaces in a string with "%20" (URLify).
----------------------------------------------------------
- urilify1: modifies a char array in place with preallocated space
- urilify2: returns a new C-string
- urilify3: modifies a padded std::string in place
- urilify4: constructs and returns a new std::string
*/

class UrilifyString {
   public:
    static void test() {
        char str1[18] = {0};
        strcpy(str1, "Mr John Smith");
        UrilifyString obj;
        obj.urilify1(str1);
        cout << "Urilified string 1: " << str1 << endl;

        char str2[] = "Mr John Smith";
        char* str2_res = obj.urilify2(str2);
        cout << "Urilified string 2: " << str2_res << endl;
        free(str2_res);

        string str3 = "Mr John Smith    ";
        string str3_res = obj.urilify3(str3);
        cout << "Urilified string 3: " << str3_res << endl;

        string str4 = "Mr John Smith";
        string str4_res = obj.urilify4(str4);
        cout << "Urilified string 4: " << str4_res << endl;
    }

   private:
    // In-place modification assuming extra space is allocated
    void urilify1(char str[]) {
        int n = strlen(str), spaceCount = 0;
        for (int i = 0; i < n; ++i)
            if (str[i] == ' ') ++spaceCount;

        int newLen = n + 2 * spaceCount;
        str[newLen] = '\0';
        for (int i = n - 1, j = newLen - 1; i >= 0; --i) {
            if (str[i] == ' ') {
                str[j--] = '0';
                str[j--] = '2';
                str[j--] = '%';
            } else {
                str[j--] = str[i];
            }
        }
    }

   private:
    // Allocates and returns a new C-string
    char* urilify2(const char str[]) {
        int n = strlen(str), spaceCount = 0;
        for (int i = 0; i < n; ++i)
            if (str[i] == ' ') ++spaceCount;

        int newLen = n + 2 * spaceCount;
        char* newStr = static_cast<char*>(malloc(newLen + 1));
        newStr[newLen] = '\0';

        for (int i = n - 1, j = newLen - 1; i >= 0; --i) {
            if (str[i] == ' ') {
                newStr[j--] = '0';
                newStr[j--] = '2';
                newStr[j--] = '%';
            } else {
                newStr[j--] = str[i];
            }
        }
        return newStr;
    }

   private:
    // In-place modification on a pre-padded std::string
    string urilify3(string str) {
        int n = str.length(), actualLen = 0, spaceCount = 0;
        while (actualLen < n && str[actualLen] != '\0') {
            if (str[actualLen] == ' ') ++spaceCount;
            ++actualLen;
        }
        int newLen = actualLen + 2 * spaceCount;
        str.resize(newLen);

        for (int i = actualLen - 1, j = newLen - 1; i >= 0; --i) {
            if (str[i] == ' ') {
                str[j--] = '0';
                str[j--] = '2';
                str[j--] = '%';
            } else {
                str[j--] = str[i];
            }
        }
        return str;
    }

   private:
    // Constructs and returns a new std::string
    string urilify4(const string& str) {
        int spaceCount = count(str.begin(), str.end(), ' ');
        int newLen = str.length() + 2 * spaceCount;
        string newStr(newLen, '\0');

        for (int i = str.length() - 1, j = newLen - 1; i >= 0; --i) {
            if (str[i] == ' ') {
                newStr[j--] = '0';
                newStr[j--] = '2';
                newStr[j--] = '%';
            } else {
                newStr[j--] = str[i];
            }
        }
        return newStr;
    }
};
