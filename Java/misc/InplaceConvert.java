package programs.misc;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/*

If [a1,a2,a3...,an,b1,b2...bn] is given input change this to [a1,b1,a2,b2.....an,bn] , solution should be in-place
 */

/*
First swap elements in the middle pair
Next swap elements in the middle two pairs
Next swap elements in the middle three pairs
iterate n-1 steps.

Ex: with n = 4.
a1 a2 a3 a4 b1 b2 b3 b4
a1 a2 a3 b1 a4 b2 b3 b4
a1 a2 b1 a3 b2 a4 b3 b4
a1 b1 a2 b2 a3 b3 a4 b4
 */
public class InplaceConvert {
    public static void test() {
        List<String> arr = Arrays.asList("a1", "a2", "a3", "a4", "b1", "b2", "b3", "b4");
        transform(arr);
        System.out.println(arr);
    }

    private static void transform(List<String> arr) {
        int n = arr.size();
        int m = n / 2;

        int j = n - 2;
        for (int i = m - 1; i >= 0; i -= 1, j -= 2) {
            Collections.swap(arr, i, j);
        }
    }
}
