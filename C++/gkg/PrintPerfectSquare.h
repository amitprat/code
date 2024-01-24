#pragma once
#include "../Header.h"

/*
Let's say there is a double square number X, which can be expressed as the sum of two perfect squares, for example, 10 is double square because 10 = 3^2 + 1^2

Determine the number of ways which it can be written as the sum of two squares
*/

class PrintPerfectSquare {
public:
    static void test() {
        PrintPerfectSquare obj;
        int n = 200;
        obj.print(n);
    }

    void print(int n) {
        int i = 0;
        int j = sqrt(n);
        while (i <= j) {
            int p = pow(i, 2) + pow(j, 2);
            if (p == n) {
                cout << i << ", " << j << endl;
                i++; j--;
            }
            else if (p < n) i++;
            else j--;
        }
    }
};

/*
This solution is similar to the 2-sum algorithm, used to see whether any two values of a sorted array sum to a specific number.

In this case, however, the lower bound is zero, while the upper bound is the square root of N. We set a cursor on the lower bound, and it only moves in +1 steps. Also, we set another cursor on the upper bound, and it only moves in -1 steps.

Whenever the sum of squares is greater than N, we need to decrease the sum. In order to do so, we move the upper cursor down (j = j-1). Whenever the sum is lower than N, we move the lower cursor up (i = i+1). Else, when we find a match, we move both.


import sys
import math

n = int(sys.argv[1])

root = math.sqrt(n)
floor = int(root)

i = 0
j = floor

while i <= j:
    sqsum = i**2 + j**2
    if sqsum == n:
        print i, j
        i = i + 1
        j = j - 1
    elif sqsum > n:
        j = j - 1
    else:
        i = i + 1
This algorithm is O(n) loose, which is way better than the naive approach of two nested fors.
*/