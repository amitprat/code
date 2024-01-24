#include "../header.h"

class MedianOfStreamOfNumbers {
   private:
    /*
    Time Complexity: O(n2)
    Auxiliary Space: O(1)
    */
    void median(vector<int>& arr) {
        for (int j = 0; j < n; j++) {
            int num = arr[j];
            int pos = binarSearch(arr, 0, j - 1, num);

            int tmp = j - 1;
            while (tmp >= 0 && tmp >= pos) {
                arr[tmp + 1] = arr[tmp];
                tmp--;
            }
            arr[tmp + 1] = num;

            if ((j + 1) & 1)
                cout << "Median: " << arr[j / 2] << endl;
            else
                cout << "Median: " << (arr[j / 2 - 1] + arr[j / 2]) / 2 << endl;
        }
    }
};