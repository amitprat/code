#pragma once
#include "../header.h"
using namespace std;

class BoolStream {
    using BitStream = vector<int>;

   private:
    BitStream stream;

   public:
    static void test(vector<int> input) {
        BoolStream obj;
        int mx = 0;
        for (auto index : input) {
            bool res = obj.getIndex(index);
            cout << "Value at index: " << index << " :: {";
            cout << res << ", ";

            obj.setTrue(index);
            // res = obj.getIndex(index);
            // cout << res << ", ";

            // obj.setFalse(index);
            // res = obj.getIndex(index);
            // cout << res << ", ";

            // obj.setAllTrue();
            // res = obj.getIndex(index);
            // cout << res << ", ";

            // obj.setAllFalse();
            // res = obj.getIndex(index);
            cout << res << "}" << endl;
            mx = max(mx, index);
        }

        for (int i = 0; i <= mx; i++) {
            bool res = obj.getIndex(i);
            if (res) cout << "Value at index: " << i << " :: " << res << endl;
        }
    }

    void setTrue(int index) {
        int remainder = index % 32;
        int dividend = index / 32;
        if (stream.size() <= dividend) stream.resize(dividend + 1);
        stream[dividend] |= 1 << remainder;
    }

    void setFalse(int index) {
        int remainder = index % 32;
        int dividend = index / 32;
        if (stream.size() <= dividend) stream.resize(dividend + 1);
        stream[dividend] &= ~(1 << remainder);
    }

    void setAllTrue() {
        for (int i = 0; i < stream.size(); i++) stream[i] |= 0xFFFF;
    }

    void setAllFalse() {
        for (int i = 0; i < stream.size(); i++) stream[i] &= 0x0000;
    }

    bool getIndex(int index) {
        int remainder = index % 32;
        int dividend = index / 32;
        if (stream.size() <= dividend) return false;
        return (stream[dividend] >> remainder) & 1;
    }
};