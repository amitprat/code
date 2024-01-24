#pragma once
#include "../Header.h"

class StringToFloat {
public:
    static void test() {
        StringToFloat obj;
        string str = "342.18";
        float res = obj.convert(str);
        cout << str << " = " << res << endl;
    }

    float convert(string str) {
        if (str.empty()) return 0;
        int decPos = str.find(".");
        if (str.find(".", decPos + 1) != string::npos) throw exception("Invalid string");
        //int excPos = str.find("e");
        //if (str.find("e", excPos + 1) != string::npos) throw exception("Invalid string");

        //if (decPos != string::npos && excPos != string::npos && excPos < decPos)
        //    throw exception("Invalid string");

        int neg = 1;
        int start = 0;
        if (str[0] == '-' || str[0] == '+') {
            if (str[0] == '-') neg = -1;
            start++;
        }

        int num = toInt(str.substr(start, decPos));
        float dec = 0;
        if (decPos != string::npos) {
            dec = toFloat(str.substr(decPos + 1));
        }

        return (double)neg * ((double)num + dec);
    }

    int toInt(string str) {
        int num = 0;
        for (auto ch : str) {
            if (ch < '0' || ch >'9') throw exception("Invalid string");
            num = num * 10 + (ch - '0');
        }
        return num;
    }

    float toFloat(string str) {
        int pow = 10;
        float res = 0;
        for (auto ch : str) {
            if (ch < '0' || ch >'9') throw exception("Invalid string");
            res = res + (float)(ch - '0') / (float)pow;
            pow *= 10;
        }
        return res;
    }
};