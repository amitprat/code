package programs.careercup;

import java.util.Arrays;

public class FindMinDiff {
    public static void test() {
        int[] arr1 = {1, 5, 100};
        int[] arr2 = {40, 45, 75};
        int[] arr3 = {50, 100, 200};

        Arrays.sort(arr1);
        Arrays.sort(arr2);
        Arrays.sort(arr3);

        int aPos = 0, bPos = 0, cPos = 0;
        int a = arr1[0], b = arr2[0], c = arr3[0];
        int minDiff = Integer.MAX_VALUE;
        while (true) {
            int mn = Math.min(a, Math.min(b, c));
            minDiff = Math.min(minDiff, Math.abs(a - b) + Math.abs(b - c) + Math.abs(c - a));
            if (mn == a) {
                aPos++;
                if (aPos == arr1.length) break;
                a = arr1[aPos];
            } else if (mn == b) {
                bPos++;
                if (bPos == arr2.length) break;
                b = arr2[bPos];
            } else {
                cPos++;
                if (cPos == arr3.length) break;
                c = arr3[cPos];
            }
        }

        System.out.println(minDiff);
    }
}
