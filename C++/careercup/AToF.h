#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=4901629824335872

Write atof in Java, which converts a string representation of a float (like "342.18E-10") to an actual float without
using any built-in parsing functions.
*/

class AToF {
   public:
    static void test() {
        vector<string> inputs = {"342.18E-4", "10", "-10.0", "10.124", "-10.10E-4", "+10.10E+4", "+10.10E+4.0"};
        for (auto& input : inputs) {
            double res = local_atof(input);
            cout << res << endl;
        }
    }

   public:
    static double local_atof(string str) {
        size_t exp = str.find("E");
        if (exp == string::npos) exp = str.find("e");

        string first = str.substr(0, exp);
        double result = convertToFloat(first);

        if (exp != string::npos) {
            string second = str.substr(exp + 1);
            double part = convertToFloat(second);

            result *= pow(10, part);
        }

        return result;
    }

   public:
    static double convertToFloat(string str) {
        if (str.empty()) return 0;

        bool signSeen = false, numSeen = false, decSeen = false;
        double result1 = 0, result2 = 0;
        int decDiv = 10;
        bool isNeg = false;
        for (auto ch : str) {
            if (ch == '+' || ch == '-') {
                if (signSeen) throw runtime_error("Invalid double string");
                signSeen = true;
                isNeg = ch == '-';
            } else if (ch == '.') {
                if (decSeen) throw runtime_error("Invalid double string");
                decSeen = true;
            } else if (ch >= '0' && ch <= '9') {
                double num = ch - '0';
                if (!decSeen)
                    result1 = result1 * 10 + num;
                else {
                    result2 = result2 + num / decDiv;
                    decDiv *= 10;
                }
            } else {
                throw runtime_error("Invalid double string");
            }
        }

        return isNeg ? (double)(-1) * (result1 + result2) : (result1 + result2);
    }
};