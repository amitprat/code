#pragma once
#include "../Header.h"

class CompressString {
public:
    static void test() {
        string str = "abb";
        cout << compress(str) << endl;
    }

    static string compress(string str) {
        int i = -1;
        char prev = '\0';
        int cnt = 0;
        for (auto ch : str) {
            if (prev != ch) {
                if (cnt > 0) {
                    str[++i] = prev;
                    if (cnt > 1) str[++i] = cnt + '0';
                }
                prev = ch;
                cnt = 0;
            } 
            cnt++;
        }
        if (cnt > 0) {
            str[++i] = prev;
            if (cnt > 1) str[++i] = cnt + '0';
        }

        return str.substr(0, i + 1);
    }
};