#include "../header.h"

/*
https://careercup.com/question?id=5090137058836480

Write a function which, given two integers (a numerator and a denominator), prints the decimal representation of the rational number "numerator/denominator".
Since all rational numbers end with a repeating section, print the repeating section of digits inside parentheses; the decimal printout will be/must be

Example:
1 , 3 = 0.(3)
2 , 4 = 0.5(0)
22, 7 = 3.(142857)
*/
class PrintDecimalDivision {
   public:
    static void test() {
        PrintDecimalDivision obj;
        string result = obj.decimalDivision(22, 7);
        cout << result << endl;

        result = obj.decimalDivision(41, 7);
        cout << result << endl;

        result = obj.decimalDivision(2, 4);
        cout << result << endl;

        result = obj.decimalDivision(50, 8);
        cout << result << endl;
    }

   private:
    string decimalDivision(int a, int b) {
        int d = a / b;
        int r = a % b;

        string result = to_string(d);
        unordered_map<char, int> pos;
        string dec;
        string repPart;
        int l = 0;
        while (r > 0 && l < 32) {
            r *= 10;
            d = r / b;
            r = r % b;
            if (pos.find(d) != pos.end()) {
                repPart = dec.substr(pos[d]);
                dec = dec.substr(0, pos[d]);
                break;
            } else {
                pos[d] = l;
            }
            dec += to_string(d);
            l++;
        }

        if (!dec.empty()) result += "." + dec;
        if (!repPart.empty()) {
            result += (dec.empty() ? "." : "");
            result += "(" + repPart + ")";
        }

        return result;
    }
};