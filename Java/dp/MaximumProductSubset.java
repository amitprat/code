package programs.dp;

public class MaximumProductSubset {
    public static void test() {
        MaximumProductSubset obj = new MaximumProductSubset();
        int[] arr1 = {-1, -2, -3, 0, 2};
        int[] arr2 = {-3, 0};
        System.out.println("Maximum Product: " + obj.maxProd1(arr1));
        System.out.println("Maximum Product: " + obj.maxProd1(arr2));
    }

    private int maxProd(int[] arr) {
        if (arr.length == 0) return 0;
        int[] pos = new int[arr.length];
        int[] neg = new int[arr.length];
        pos[0] = Math.max(1, arr[0]);
        neg[0] = Math.min(-1, arr[0]);
        for (int i = 1; i < arr.length; i++) {
            pos[i] = Math.max(arr[i], Math.max(pos[i - 1] * arr[i], neg[i - 1] * arr[i]));
            neg[i] = Math.min(arr[i], Math.min(pos[i - 1] * arr[i], neg[i - 1] * arr[i]));
        }
        int mx = pos[0];
        for (int i = 0; i < pos.length; i++) {
            mx = Math.max(mx, pos[i]);
        }
        return mx;
    }

    private int maxProd1(int[] arr) {
        if (arr.length == 0) return 0;

        int mx = 1;
        int zeros = 0, neg = 0;
        int mxNeg = Integer.MIN_VALUE;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == 0) {
                zeros++;
                continue;
            }
            if (arr[i] < 0) {
                neg++;
                mxNeg = Math.max(mxNeg, arr[i]);
            }
            mx *= arr[i];
        }
        if (zeros == arr.length) return 0;
        if (neg % 2 == 1) {
            if (neg == 1 && zeros > 0 && neg + zeros == arr.length) return 0;
            mx = mx / mxNeg;
        }
        return mx;
    }
}
