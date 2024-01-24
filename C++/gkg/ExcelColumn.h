#pragma once
#include "../Header.h"

class ExcelColumn
{
public:
    static void test() {
        generate(26);
        generate(51);
        generate(52);
        generate(80);
        generate(676);
        generate(702);
        generate(705);
    }

    static void generate(int num) {
        string res;
        while (num > 0) {
            int d = (num - 1) / 26;
            int r = (num - 1) % 26;

            res += 'A' + r;
            num = d;
        }

        reverse(res.begin(), res.end());
        cout << res << endl;
    }
};