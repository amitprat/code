#include "../header.h"

/*
https://careercup.com/question?id=6139456847347712

Microsoft Excel numbers cells as 1...26 and after that AA, AB.... AAA, AAB...ZZZ and so on.
Given a number, convert it to that format and vice versa.

def toStr(n):
    out = '';
    while(n != 0):
        d = (n - 1) % 26 + 1;
        out = chr(ord('A') + d - 1) + out;
        n = (n-d)/26
    print out;

def toNum(v):
    sum = 0;
    for c in v:
        sum = sum*26 + ord(c) - ord('A') + 1;
    return sum;

>>> toStr(toNum('AZCZS'));
AZCZS
*/
class ConvertToFromExcelColumn {
    int toNum(string str) {
        int num = 0;
        for (auto ch : str) {
            int id = ch - 'A' + 1;
            num = num * 26 + id;
        }

        return num;
    }

    string toStr(int num) {
        string str;
        while (num) {
            int r = (num - 1) / 26 + 1;
            str = string(1, (r + 'A' - 1)) + str;

            num = (num - r) / 26;
        }

        return str;
    }

    string toStr2(int num) {
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