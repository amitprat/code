package Java.arrays;

import java.util.Arrays;

public class SortPositiveNegativeNumbers {
    public static void test() {
        int[] arr = {1, -1, -3, -2, 2};
        SortPositiveNegativeNumbers obj = new SortPositiveNegativeNumbers();
        obj.sort(arr, 0, arr.length - 1);

        System.out.println(Arrays.toString(arr));
    }

    private void sort(int[] arr, int l, int r) {
        if (l >= r) return;
        int m = (l + r) / 2;
        sort(arr, l, m);
        sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

    private void merge(int[] arr, int l, int m, int r) {
        int p1 = -1;
        for (int i = l; i <= m; i++) {
            if (arr[i] >= 0) {
                p1 = i;
                break;
            }
        }
        if (p1 == -1) p1 = m + 1;

        // reverse first half [A2]
        reverse(arr, p1, m);

        int n2 = m;
        for (int i = m + 1; i <= r; i++) {
            if (arr[i] >= 0) {
                break;
            }
            n2 = i;
        }
        // reverse second half [B1]
        reverse(arr, m + 1, n2);

        // reverse entire set [A2..B1]
        reverse(arr, p1, n2);
    }

    void reverse(int[] arr, int l, int r) {
        while (l < r) {
            int t = arr[l];
            arr[l] = arr[r];
            arr[r] = t;
            l++;
            r--;
        }
    }
}
