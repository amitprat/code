#include "../header.h"

class Bitset {
   public:
    static void test() {
        Bitset obj;

        for (int i = 0; i < 21; i++) {
            obj.setTrue(i);

            cout << "state = " << obj.to_string() << endl;
            cout << "Index State = " << obj.Isset(i) << endl;

            obj.setFalse(i);
            cout << "state = " << obj.to_string() << endl;
            cout << "Index State = " << obj.Isset(i) << endl;

            obj.setAllTrue();
            cout << "state = " << obj.to_string() << endl;

            obj.setAllFalse();
            cout << "state = " << obj.to_string() << endl;
        }

        println("\n");

        int cnt = obj.countSetBits(997);
        println("Binary representation of {0} is {1}", 997, obj.to_bin2(997));
        println("Set bits are: {0}", cnt);

        int next = obj.nextNumberWithSameSetOfBits(997);
        println("Next number with same set bits: {0}", next);
        println("Binary representation of {0} is {1}", next, obj.to_bin2(next));
    }

   private:
    vector<int> bitset;
    const int INT_SIZE = 4 * 8;

   public:
    void setTrue(int index) {
        resize(index);
        set(bitset[pos(index)], offset(index), true);
    }

    void setFalse(int index) {
        resize(index);
        set(bitset[pos(index)], offset(index), false);
    }

    void setAllTrue() {
        for (int i = 0; i < bitset.size(); i++) {
            bitset[i] = -1;
        }
    }

    void setAllFalse() {
        for (int i = 0; i < bitset.size(); i++) {
            bitset[i] = 0;
        }
    }

    bool Isset(int index) {
        return bitset[pos(index)] & (1 << offset(index));
    }

    void toggle(int index) {
        resize(index);
        toggle(bitset[pos(index)], offset(index));
    }

    string to_string() {
        stringstream ss;
        for (auto e : bitset) {
            ss << to_bin(e) << " ";
        }
        return ss.str();
    }

    int countSetBits(int n) {
        int num = 0;
        while (n) {
            num++;
            n &= (n - 1);
        }

        return num;
    }

    int bitsSwapRequired(int a, int b) {
        int cnt = 0;
        for (int c = a ^ b; c != 0; c = c & (c - 1)) {
            cnt++;
        }

        return cnt;
    }

    int nextNumberWithSameSetOfBits(int n) {
        int c = n;
        int c0 = 0, c1 = 0;

        // find first 1
        while ((c & (1 << c0)) == 0) c0++;

        // find next 0
        while (c & (1 << (c0 + c1))) c1++;

        int p = c0 + c1;

        // Set this 1
        n |= (1 << p);
        c1--;

        // Set all bits to 0
        n &= ~(1 << (p - 1));

        // Set last bits to 1
        n |= (1 << c1) - 1;

        return n;
    }

    int swapEvenOddBits(int n) {
        return ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    }

   private:
    void resize(int index) {
        while (bitset.size() < pos(index) + 1) {
            bitset.push_back(0);
        }
    }

    void set(int &elem, int index, bool state) {
        if (state) {
            elem |= (1 << index);
        } else {
            elem &= ~(1 << index);
        }
    }

    void toggle(int &elem, int off) {
        elem ^= (1 << off);
    }

    string to_bin(int e) {
        string cur;
        for (int i = INT_SIZE - 1; i >= 0; i--) {
            if (e & (1 << i))
                cur += "1";
            else
                cur += "0";

            if (i % 8 == 0)
                cur += " ";
        }

        return cur;
    }

    string to_bin2(int e) {
        std::bitset<32> binary(e);
        return binary.to_string();
    }

    string to_bin3(int e) {
        string str;
        while (e) {
            str += e & 1 ? "1" : "0";
            e >>= 1;
        }

        std::reverse(str.begin(), str.end());

        return str;
    }

    int pos(int index) { return index / INT_SIZE; }
    int offset(int index) { return index % INT_SIZE; }
};
