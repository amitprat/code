package programs.misc;

import java.util.Arrays;

public class Median {
    static void test() {
        Median obj = new Median();
        int[] arr = {12, 3, 5, 7, 4, 19, 26, 8};
        double res = obj.findMedian(arr);
        System.out.println("res = " + res);

        double median;
        Arrays.sort(arr);
        int m = arr.length;
        if (m % 2 == 1) median = arr[m / 2];
        else median = (arr[m / 2-1] + arr[m / 2]) / 2;
        System.out.println("Correct median: " + median);
    }

    double findMedian(int[] arr) {
        int l = arr.length;
        if (l % 2 == 1) return findMedianInternal(arr, 0, l - 1, l / 2 + 1);
        return (findMedianInternal(arr, 0, l - 1, l / 2) + findMedianInternal(arr, 0, l - 1, l / 2 + 1)) / 2;
    }

    int findMedianInternal(int[] arr, int l, int r, int k) {
        int p = partition(arr, l, r);
        int q = p - l + 1;
        if (q == k) return arr[p];
        else if (q < k) return findMedianInternal(arr, p + 1, r, k - q);
        else return findMedianInternal(arr, l, p - 1, k);
    }

    int partition(int[] arr, int l, int r) {
        int p = arr[r];
        int i = l;
        for (int j = l; j < r; j++) {
            if (arr[j] <= p) {
                swap(arr, i, j);
                i++;
            }
        }
        swap(arr, i, r);
        return i;
    }

    void swap(int[] a, int i, int j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}
