package programs.careercup;

import java.util.Arrays;

public class AddBigIntegers {
    public static void test() {
        AddBigIntegers obj = new AddBigIntegers();

        {
            int[] arr1 = {1, 2, 9, 8};
            int[] arr2 = {9, 0, 8, 2};

            var res = obj.add(arr1, arr2);
            System.out.println(Arrays.toString(res));
        }

        {
            int[] arr1 = {9, 9, 9, 9};
            int[] arr2 = {9};

            var res = obj.add(arr1, arr2);
            System.out.println(Arrays.toString(res));
        }

        {
            int[] arr1 = {9, 9};
            int[] arr2 = {1, 9, 9, 0};

            var res = obj.add(arr1, arr2);
            System.out.println(Arrays.toString(res));
        }

        {
            int[] arr1 = {9, 9};
            int[] arr2 = {1, 0, 0, 0};

            var res = obj.add(arr1, arr2);
            System.out.println(Arrays.toString(res));
        }

        {
            int[] arr1 = {1, 0, 9, 0, 9};
            int[] arr2 = {1, 0, 0, 0};

            var res = obj.add(arr1, arr2);
            System.out.println(Arrays.toString(res));
        }
    }

    private int[] add(int[] arr1, int[] arr2) {
        int n = arr1.length;
        int m = arr2.length;
        int[] res = new int[Math.max(n, m) + 1];
        int k = res.length - 1;
        int i = n - 1, j = m - 1;
        int carry = 0;

        while (k >= 0) {
            int cur = carry;
            if (i >= 0) cur += arr1[i--];
            if (j >= 0) cur += arr2[j--];
            res[k--] = cur % 10;
            carry = cur / 10;
        }

        return res;
    }
}
