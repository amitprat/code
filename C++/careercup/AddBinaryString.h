#include "../header.h"
/*
Implement binary addition of two strings.
For example "101101" and "111101" equal "1101010"
You cannot use any type conversion, operate only with strings.

https://careercup.com/question?id=5699214707785728
*/
class AddBinaryString {
   public:
    static void test() {
        vector<pair<string, string>> inputs = {
            {"10101010", "00100011"},
            {"101101", "111101"},
            {"1", "101011"},
            {"01011", "0"},
            {"", "101010"}};

        AddBinaryString obj;
        for (auto &input : inputs) {
            string s3 = obj.addBinary(input.first, input.second);

            stringstream ss;
            ss << input.first << " + " << input.second << " = " << s3;

            cout << ss.str() << endl;
        }
    }

   private:
    string addBinary(string s1, string s2) {
        int l1 = s1.length();
        int l2 = s2.length();
        int l = max(l1, l2);
        if (l1 != l2) {
            if (l1 < l2)
                s1 = prepend(s1, l2 - l1, '0');
            else
                s2 = prepend(s2, l1 - l2, '0');
        }

        int carry = 0;
        string s3 = addBinary(s1, s2, 0, l, carry);
        if (carry) s3 = "1" + s3;

        return s3;
    }

    string addBinary(string s1, string s2, int idx, int l, int &carry) {
        if (idx == l) return "";

        string next = addBinary(s1, s2, idx + 1, l, carry);

        int res = carry + s1[idx] - '0' + s2[idx] - '0';
        carry = res / 2;
        string cur = res & 1 ? "1" : "0";

        return cur + next;
    }

    string prepend(string &str, int d, char ch) {
        return string(d, ch) + str;
    }
};