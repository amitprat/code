#include "../header.h"

/*
Given the array of digits (0 is also allowed), what is the minimal sum of two integers that are made of the digits contained in the array.
For example, array: 1 2 7 8 9. The min sum (129 + 78) should be 207

Sort the array. The largest numbers should be in the least significant positions, so build up your two integers by alternating from the two arrays.
E.g. 1 3 5 7 8 9 => 1 and 3, then 15 and 37, then 158 and 379. 0 is a special case, if not allowed to use that as a leading digit then have to use it as the second digit.
*/
class MinimumSumOfIntegersFromArray {
   public:
    int findElements(int arr[], int n) {
        if (n == 0) return 0;
        if (n == 1) return arr[0];
        if (n == 2) return arr[0] + arr[1];

        sort(arr, arr + n);

        int i = 0;
        while (i < n && arr[i] == 0) i++;
        swap(arr[0], arr[i]);
        if (i + 1 < n) swap(arr[1], arr[i + 1]);

        int a, b;
        a = arr[0];
        b = arr[1];
        for (int i = 2; i < n; i++) {
            if (i % 2 == 0)
                a = a * 10 + arr[i];
            else
                b = b * 10 + arr[i];
        }

        cout << "A = " << a << ", B=" << b << endl;

        return a + b;
    }
};