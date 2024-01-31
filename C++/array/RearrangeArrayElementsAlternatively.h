#pragma once
#include "../header.h"

class RearrangeArrayElementsAlternatively {
   public:
   private:
    // T=O(n), S=O(1)
    void rearrange1(vector<int>& arr) {
        int n = arr.size();
        int i = 0, j = n - 1;
        int mx = arr[n - 1] + 1;

        for (int k = 0; k < n; k++) {
            if (k & 1) {
                arr[k] += (arr[i] % mx) * mx;
                i++;
            } else {
                arr[k] += (arr[j] % mx) * mx;
                j--;
            }
        }

        for (int k = 0; k < n; k++) {
            arr[k] /= mx;
        }
    }

   private:
    // T=O(n), S=O(n)
    void rearrange2(vector<int>& arr) {
        int n = arr.size();
        vector<int> tmp(n);

        for (int k = 0, i = 0, j = n - 1; k < n; k++) {
            if (k & 1) {
                tmp[k] = arr[i++];
            } else {
                tmp[k] = arr[j--];
            }
        }

        for (int k = 0; k < n; k++) {
            arr[k] = tmp[k];
        }
    }
};