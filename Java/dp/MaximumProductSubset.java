package Java.dp;

/*
 * https://www.careercup.com/question?id=5655534577385472
 * find the Maximum product subset with negative and positive integer
 */
public class MaximumProductSubset {
    public static void test() {
        MaximumProductSubset obj = new MaximumProductSubset();

        int[] arr1 = { -1, -2, -3, 0, 2 };
        int[] arr2 = { -3, 0 };
        int[] arr3 = { -5, -4, 2, 3, 0, 0, 0, 10, -1 };

        System.out.println("Maximum Product: " + obj.maxProd1(arr1));
        System.out.println("Maximum Product: " + obj.maxProd1(arr2));
        System.out.println("Maximum Product: " + obj.maxProd1(arr3));
    }

    private int maxProd(int[] arr) {
        if (arr.length == 0)
            return 0;

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

    // https://www.geeksforgeeks.org/maximum-product-subset-array/
    // space optimized
    private int maxProd1(int[] arr) {
        if (arr.length == 0)
            return 0;

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

        // if all elements are zeros
        if (zeros == arr.length)
            return 0;

        // if number of negatives are odd.
        if (neg % 2 == 1) {
            // if there is only one negative and rest are zeros, then zero is max product.
            if (neg == 1 && zeros > 0 && neg + zeros == arr.length)
                return 0;

            mx = mx / mxNeg;
        }
        return mx;
    }

    // another appraoch
    private int maxProdSubset(int[] arr) {
        if(arr.length == 0) return 0;

        int maxPos = 1;
        int minNeg = 1;
        int maxNeg = INT_MIN;

        for(int i=0;i<arr.length;i++) {
            if(arr[i] > 0) maxPos *= arr[i];
            else if(arr[i] < 0) {
                minNeg *= arr[i];
                maxNeg = Math.max(maxNeg, arr[i]);
            }
        }

        // minNeg can only be negative if number of negative numbers is odd. In that case, divide it by max negative number to get
        // product positive.
        if(minNeg < 0) minNeg /= maxNeg;

        return maxPos * minNeg;
    }
}
