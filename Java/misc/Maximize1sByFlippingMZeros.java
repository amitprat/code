package programs.misc;

import programs.types.Pair;

import java.util.Arrays;

public class Maximize1sByFlippingMZeros {
    public static void test() {
        int[] arr = {1, 1, 0, 1, 1, 0,0,0,0};
        int m = 2;
        Maximize1sByFlippingMZeros obj = new Maximize1sByFlippingMZeros();
        var res = obj.maximize(arr, m);
        System.out.println(res);
        System.out.println(Arrays.toString(arr));
    }

    private int maximize(int[] arr, int m) {
        int l = 0, r = 0;
        int zeroCount = 0;
        Pair<Integer, Integer> window = new Pair<>(-1, -1);
        while (r < arr.length) {
            if (zeroCount <= m) {
                if (arr[r] == 0) zeroCount++;
                r++;
            }
            if (zeroCount > m) {
                if (arr[l] == 0) zeroCount--;
                l++;
            }

            if (zeroCount <= m && r - l > window.second - window.first) {
                window = new Pair<>(l, r);
            }
        }
        for (int i = window.first; i < window.second; i++) arr[i] = 1;
        return window.second - window.first;
    }
}
