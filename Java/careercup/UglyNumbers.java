package programs.careercup;

import java.util.Arrays;

/*
https://www.careercup.com/question?id=23823662

Given an equation in the form 2^i * 3^j * 5^k * 7^l where i,j,k,l >=0 are integers.write a program to generate numbers from that equation in sorted order efficiently.

for example numbers from that equation will be in the order 2,3,5,6,7,8,9.....and so on..
 */

public class UglyNumbers {
    public static void test() {
        int n = 20;
        UglyNumbers obj = new UglyNumbers();
        int[] res = obj.getUglyNumbers(n);
        System.out.println(Arrays.toString(res));
    }

    private int[] getUglyNumbers(int n) {
        int[] arr = new int[n];
        arr[0] = 1;

        int i = 1;
        int i2 = 0, i3 = 0, i5 = 0, i7 = 0;
        while(i < n) {
            int mn = Math.min(Math.min(2*arr[i2], 3*arr[i3]), Math.min(5*arr[i5], 7*arr[i7]));
            if(mn == 2*arr[i2]) i2++;
            if(mn == 3*arr[i3]) i3++;
            if(mn == 5*arr[i5]) i5++;
            if(mn == 7*arr[i7]) i7++;

            arr[i++] = mn;
        }

        return arr;
    }
}
