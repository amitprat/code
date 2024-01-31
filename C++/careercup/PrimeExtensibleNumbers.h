#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=4816567298686976

Given a prime set, we call "prime expressible" if a number can be factorized only using given prime numbers. Find n-th big expressible number.

E.g., prime set = {2, 3}
expressible number = {1,2,3,4,6,8, 9, 12...}
non-expressible number = {5, 10... }

The primes in the prime set are ordered in an increasing order, and can include a prime < 10^4 (don't remember the exact range), and n can also be as large as 1-10^6.
*/

class PrimeExtensibleNumbers {
   public:
    static void test() {
        PrimeExtensibleNumbers obj;

        vector<int> arr = {2, 3, 7, 11};
        int n = 100;

        auto res1 = obj.getMultiplesOf2And3(n);
        cout << format("Multiples of 2,3 upto {0} are {1}", n, to_string(res1)) << endl;

        auto res2 = obj.getMultiples(arr, n);
        cout << format("Multiples of {0} upto {1} are {2}", to_string(arr), n, to_string(res2)) << endl;
    }

   private:
    vector<int> getMultiplesOf2And3(int n) {
        // print 2^i*3^j increasing order
        vector<int> result(n);
        result[0] = 1;

        int i2 = 0, i3 = 0;
        for (int i = 1; i < n; i++) {
            int a2 = result[i2] * 2, a3 = result[i3] * 3;
            if (a2 < a3) {
                result[i] = a2;
                i2++;
            } else if (a3 < a2) {
                result[i] = a3;
                i3++;
            } else {
                result[i] = a2;
                i2++;
                i3++;
            }
        }

        return result;
    }

   private:
    vector<int> getMultiples(vector<int>& arr, int n) {
        vector<int> result;
        vector<int> indices(arr.size(), 0);
        result.push_back(1);

        for (int i = 1; i < n; i++) {
            int mn = getMin(arr, indices, result);
            result.push_back(mn);
        }

        return result;
    }

    int getMin(vector<int>& arr, vector<int>& indices, vector<int>& result) {
        int mn = INT_MAX;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] * result[indices[i]] < mn) mn = arr[i] * result[indices[i]];
        }
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] * result[indices[i]] == mn) {
                indices[i]++;
            }
        }

        return mn;
    }
};