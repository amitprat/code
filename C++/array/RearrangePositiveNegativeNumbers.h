#pragma once
#include "../header.h"
using namespace std;

class RearrangePositiveNegativeNumbers
{
public:
    static void test(vector<int> v)
    {
        RearrangePositiveNegativeNumbers obj;
        obj.rearrange(v);
        cout << "Output: ";
        for (auto i : v) cout << i << " ";
        cout << endl;
    }
    void rearrange(vector<int>& v)
    {
        int outOfPlace = -1;
        for (int i = 0; i < v.size(); i++) {
            if (outOfPlace != -1) {
                if (correctElement(v, outOfPlace, i)) {
                    rightRotate(v, outOfPlace, i);
                    if (i - outOfPlace >= 2) outOfPlace += 2;
                    else outOfPlace = -1;
                }
            }
            else if (notInCorrectPlace(v, i)) {
                outOfPlace = i;
            }
        }
    }

    bool notInCorrectPlace(vector<int> v, int index) {
        return (index & 1 && v[index] >= 0) ||
            (!(index & 1) && v[index] < 0);
    }

    bool correctElement(vector<int> v, int outOfPlace, int index) {
        return (v[outOfPlace] >= 0 && v[index] < 0) ||
            (v[outOfPlace] < 0 && v[index] >= 0);
    }

    void rightRotate(vector<int>& v, int outOfPlace, int index) {
        int tmp = v[index];
        for (int i = index; i > outOfPlace; i--) v[i] = v[i - 1];
        v[outOfPlace] = tmp;
    }
};