#include "../header.h"

class UpdateBits {
   private:
   public:
    static void test() {
        UpdateBits obj;
        int n = 1024;
        int m = 19;
        int i = 2, j = 6;
        cout << obj.binary(n) << " " << obj.binary(m) << " " << i << " " << j << endl;
        n = obj.update(n, m, i, j);
        cout << obj.binary(n) << endl;

        cout << obj.binary(0.5) << endl;

        vector<char> s;
        s.push_back('+');
        s.push_back('/');
        for (int i = 0; i <= 9; i++) s.push_back('0' + i);
        for (char i = 'a'; i <= 'z'; i++) s.push_back(i);
        for (char i = 'A'; i <= 'Z'; i++) s.push_back(i);

        string res;
        cout << (res = obj.encode(s, 100)) << endl;
        cout << obj.decode(res) << endl;
    }

    int update(int n, int m, int i, int j) {
        int allOnes = ~0;
        int left = allOnes << (1 + j);
        int right = (1 << i) - 1;
        int mask = left | right;
        int ncleared = n & mask;
        int mshifted = m << i;

        return ncleared | mshifted;
    }

    string binary(int n) {
        string res;
        while (n) {
            res = (n & 1 ? '1' : '0') + res;
            n /= 2;
        }

        return res;
    }

    string binary(double n) {
        int decimal = n;
        double fractional = n - decimal;
        string res;

        while (decimal) {
            res = (decimal & 1 ? '1' : '0') + res;
            decimal /= 2;
        }
        res = ".";
        int places = 0;
        while (fractional && places < 32) {
            fractional *= 2;
            if (fractional >= 1) {
                fractional -= 1;
                res += '1';
            } else {
                res += '0';
            }
            places++;
        }

        return res;
    }

    int maxLengthSeq(int a) {
        int prev = 0;
        int cur = 0;
        int mx = 1;
        while (a) {
            bool b = a & 1;
            if (b) {
                cur++;
            } else {
                prev = cur;
                cur = 0;
                mx = max(mx, cur + prev + 1);
            }

            a >>= 1;
        }

        return mx;
    }

    int index(char ch) {
        if (ch == '+') return 0;
        if (ch == '/') return 1;
        if (ch >= 'a' && ch <= 'z') return ch - 'a' + 2;
        if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 2 + 26;

        return -1;
    }

    string encode(vector<char> s, int a) {
        string res;
        while (a) {
            res = s[a % 64] + res;
            a /= 64;
        }

        return res;
    }

    int decode(string s) {
        int res = 0;
        for (auto ch : s) {
            res += index(ch) * 64;
        }

        return res;
    }
};