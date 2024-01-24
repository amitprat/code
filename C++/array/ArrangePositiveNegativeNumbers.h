/*
Rearrange negative and positive numbers such that
negative numbers comes first and then positive numbers
but keeping the original order of numbers.

Input: 1 2 3 -23 -1 -1 -2 -3 -12 -24 -121 11 12 12 1212
Output: -23 -1 -1 -2 -3 -12 -24 -121 1 2 3 11 12 12 1212
*/
#include "../header.h"

class ArrangePositiveNegativeNumbers {
   public:
    static void test() {
        ArrangePositiveNegativeNumbers obj;
        vector<int> test = {1, 2, 3, -23, -1, -1, -2, -3, -12, -24, -121, 11, 12, 12, 1212};
        vector<int> expected = {-23, -1, -1, -2, -3, -12, -24, -121, 1, 2, 3, 11, 12, 12, 1212};
        cout << "Input: " << test << endl;

        obj.arrangeNumbersNormalSort(test);
        cout << "Output: " << test << endl;

        assert(expected == test);
        obj.arrangeNumbersMergeSort(test);
        assert(expected == test);
    }

    void arrangeNumbersNormalSort(vector<int>& v) {
        normalSort(v);
    }

    void arrangeNumbersMergeSort(vector<int>& v) {
        mergeSort(v, 0, v.size() - 1);
    }

   private:
    void normalSort(vector<int>& v) {
        for (int cur = 0; cur < v.size(); cur++) {
            if (v[cur] >= 0) rightShift(v, cur);  // find the first positive element and see if its in correct position
        }
    }

    void rightShift(vector<int>& v, int curPositivePos) {
        int nextNegPos = curPositivePos + 1;                               // look negative number of right of positive number
        while (v[nextNegPos] >= 0 && nextNegPos < v.size()) nextNegPos++;  // find next negative number

        int nextNeg = v[nextNegPos];  // store the negative number
        if (nextNeg >= 0) return;     // no negative number on right

        for (int i = nextNegPos - 1; i >= curPositivePos; i--) v[i + 1] = v[i];  // right shift all the positive number and make room for negative number
        v[curPositivePos] = nextNeg;                                             // place negative number
    }

    void mergeSort(vector<int>& v, int l, int r) {
        if (l < r) {
            int m = (l + r) / 2;
            mergeSort(v, l, m);
            mergeSort(v, m + 1, r);
            merge(v, l, m, r);
        }
    }

    void merge(vector<int>& v, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int* tmp1 = new int[n1];
        int* tmp2 = new int[n2];
        for (int i = l, j = 0; i <= m; i++, j++) tmp1[j] = v[i];
        for (int i = m + 1, j = 0; i <= r; i++, j++) tmp2[j] = v[i];
        int k = l;
        int i = 0, j = 0;
        for (; i < n1 && j < n2;) {
            if (tmp1[i] < 0)
                v[k++] = tmp1[i++];
            else if (tmp2[j] < 0)
                v[k++] = tmp2[j++];
            else
                break;
        }

        for (; i < n1; i++, k++) {
            v[k] = tmp1[i];
        }

        for (; j < n2; j++, k++) {
            v[k] = tmp2[j];
        }
    }
};