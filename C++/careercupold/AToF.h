#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=4901629824335872
*/
class AToF
{
public:
    static void test() {
        {
            string str = "342.18E-4";

            double res = local_atof(str);
            cout << res << endl;
        }

        {
            string str = "10";

            double res = local_atof(str);
            cout << res << endl;
        }

        {
            string str = "-10.0";

            double res = local_atof(str);
            cout << res << endl;
        }

        {
            string str = "10.124";

            double res = local_atof(str);
            cout << res << endl;
        }

        {
            string str = "-10.10E-4";

            double res = local_atof(str);
            cout << res << endl;
        }

        {
            string str = "+10.10E+4";

            double res = local_atof(str);
            cout << res << endl;
        }

        {
            string str = "+10.10E+4.0";

            double res = local_atof(str);
            cout << res << endl;
        }
    }

    static double local_atof(string str) {
        size_t exp = str.find("E");
        if (exp == string::npos) exp = str.find("e");

        string first = str.substr(0, exp);

        double result = convertToFloat(first);
        if (exp != string::npos) {
            string second = str.substr(exp + 1);
            double part = convertToFloat(second);
            part = pow(10, part);

            result += part;
        }

        return result;
    }

    static double convertToFloat(string str) {
        if (str.empty()) return 0;

        bool signSeen = false, numSeen = false, decSeen = false;
        double result1 = 0, result2 = 0;
        int decDiv = 10;
        bool isNeg = false;
        for (auto ch : str) {
            if (ch == '+' || ch == '-') {
                if (signSeen) throw exception("Invalid double string");
                signSeen = true;
                isNeg = ch == '-';
            }
            else if (ch == '.') {
                if (decSeen) throw exception("Invalid double string");
                decSeen = true;
            }
            else if (ch >= '0' && ch <= '9') {
                double num = ch - '0';
                if (!decSeen) result1 = result1 * 10 + num;
                else {
                    result2 = result2 + num / decDiv;
                    decDiv *= 10;
                }
            }
            else {
                throw exception("Invalid double string");
            }
        }

        return isNeg ? (double)(-1) * (result1 + result2) : (result1 + result2);
    }
};