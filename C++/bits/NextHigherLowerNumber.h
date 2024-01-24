#include "../header.h"

class NextHigherLowerNumber {
   public:
    static void test() {
        int num = 23;
        NextHigherLowerNumber obj;

        cout << "Bits count for num  " << num << " are " << obj.count(num) << endl;

        int nextHigher = obj.nextHigher(num);
        cout << "Next higher " << nextHigher << ", bits count " << obj.count(nextHigher) << endl;

        int preLower = obj.prevLower(num);
        cout << "Prev lower " << preLower << ", bits count " << obj.count(preLower) << endl;
    }

    int nextHigher(int num) {
        int ones = 0;
        int i = 0;

        // find first one
        while (!(num & (1 << i))) i++;

        // find next zero
        while (num & (1 << i)) {
            ones++;
            i++;
        }

        // set current zero as 1
        num |= (1 << i);
        ones--;

        // clear all bits on left of it
        num &= ~((1 << i) - 1);

        // set the rightmost bits as ones
        num |= (1 << ones) - 1;

        return num;
    }

    int prevLower(int num) {
        cout << setw(32) << left << "Original num " << to_binary(num) << endl;
        int zeros = 0, ones = 0;
        int i = 0;

        // find first zero
        while ((num & (1 << i))) {
            ones++;
            i++;
        }

        // find next one
        while (!(num & (1 << i))) {
            zeros++;
            i++;
        }

        // clear all bits starting from this position
        num &= ~((1 << (i + 1)) - 1);
        ones++;
        zeros--;
        cout << setw(32) << left << "After clearing first 1, num " << to_binary(num) << endl;

        // set the ones
        int mask = (1 << ones) - 1;
        mask = mask << zeros;
        cout << to_binary(mask) << endl;

        num |= mask;
        cout << setw(32) << left << "After setting correct 1s, num " << to_binary(num) << endl;

        return num;
    }

    int count(int num) {
        int cnt = 0;
        while (num) {
            cnt++;
            num &= num - 1;
        }
        return cnt;
    }

    string to_binary(int num, int numBits = 8) {
        string res;
        while (num) {
            res += (num % 2) + '0';
            num /= 2;
        }
        reverse(res.begin(), res.end());
        int n = res.length();
        res = string(numBits - n, '0') + res;

        return res;
    }
};