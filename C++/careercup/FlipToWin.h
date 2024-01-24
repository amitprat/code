#include "../header.h"

class FlipToWin {
   public:
    static void test() {
        FlipToWin obj;
        string bin = "1111001111";
        int num1 = obj.to_num(bin);
        int num2 = obj.to_num1(bin);
        int numUsingSTL = bitset<32>(bin).to_ulong();
        assert(num1 == numUsingSTL);
        assert(num2 == numUsingSTL);

        string binUsingSTL = bitset<32>(numUsingSTL).to_string();
        string binUsingCustomMethod = obj.to_binary(num1);
        // assert(binUsingSTL == binUsingCustomMethod);

        cout << format("Binary={} to num={}", bin, num1) << endl;
        cout << format("Num={} to binary={}.", num1, binUsingSTL) << endl;

        auto res = obj.getLongest(num1);
        cout << "Longest 1s: " << res << endl;
    }

    int getLongest(int num) {
        int mx = 1;
        int pz = -1, cz = -1, index = 0;

        while (num) {
            if ((num & 1) == 0) {
                if (cz != -1) {
                    mx = max(mx, index - pz - 1);
                }

                pz = cz;
                cz = index;
            }

            index++;
            num >>= 1;
        }

        if (cz != -1) {
            mx = max(mx, index - pz - 1);
        }

        return mx;
    }

    string to_binary(int num) {
        stringstream ss;
        while (num) {
            ss << (num % 2);
            num /= 2;
        }

        string res = ss.str();
        reverse(res.begin(), res.end());

        return res;
    }

    int to_num(string str) {
        int num = 0;
        int n = str.length() - 1;
        for (int i = n; i >= 0; i--) {
            num += (str[i] - '0') * pow(2, n - i);
        }

        return num;
    }

    int to_num1(string str) {
        int num = 0;
        for (int i = 0; i < str.length(); i++) {
            num = (num << 1) + (str[i] - '0');
        }

        return num;
    }
};