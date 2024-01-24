package Java.arrays;

public class FindDisjointContguousSubarrayWithMaxAbsDiff {
    public static void test() {
        FindDisjointContguousSubarrayWithMaxAbsDiff obj = new FindDisjointContguousSubarrayWithMaxAbsDiff();
        int[][] arrs = {
                { 2, -1, -2, 1, -4, 2, 8 },
                { -1, -2, 1, -4, 2, 8, 2 },
                { -2, 1, -4, 2, 8, 2, -1 },
                { 1, -4, 2, 8, 2, -1, -2 },
                { -4, 2, 8, 2, -1, -2, 1 },
                { 2, 8, 2, -1, -2, 1, -4 },
                { 8, 2, -1, -2, 1, -4, 2 }
        };

        for (var arr : arrs) {
            var res = obj.findMaxDiff(arr);
            System.out.println(res);
        }
    }

    private int findMaxDiff(int[] arr) {
        int[] leftMin = new int[arr.length];
        int[] leftMax = new int[arr.length];
        int[] rightMin = new int[arr.length];
        int[] rightMax = new int[arr.length];

        int leftMinSum = 0, leftMaxSum = 0;
        for (int i = 0; i < arr.length; i++) {
            leftMinSum += arr[i];
            leftMaxSum += arr[i];

            leftMin[i] = leftMinSum;
            leftMax[i] = leftMaxSum;

            if (leftMinSum > 0)
                leftMinSum = 0;
            if (leftMaxSum < 0)
                leftMaxSum = 0;
        }

        int rightMinSum = 0, rightMaxSum = 0;
        for (int i = arr.length - 1; i >= 0; i--) {
            rightMinSum += arr[i];
            rightMaxSum += arr[i];

            rightMin[i] = rightMinSum;
            rightMax[i] = rightMaxSum;

            if (rightMinSum > 0)
                rightMinSum = 0;
            if (rightMaxSum < 0)
                rightMaxSum = 0;
        }

        int mxDiff = Integer.MIN_VALUE;
        for (int i = 0; i < arr.length - 1; i++) {
            int curDiff1 = rightMax[i + 1] - leftMin[i];
            int curDiff2 = leftMax[i] - rightMin[i + 1];
            int curDiff = Math.max(curDiff1, curDiff2);
            mxDiff = Math.max(mxDiff, curDiff);
        }

        return mxDiff;
    }
}
