package Java.arrays;

public class LargestRectangleSum {
    public static void test() {
        int[][] matrix = {
                { 1, 2, -1, -4, -20 },
                { -8, -3, 4, 2, 1 },
                { 3, 8, 10, 1, 3 },
                { -4, -1, 1, 7, -6 }
        };

        LargestRectangleSum obj = new LargestRectangleSum();
        var largestRect = obj.largestRectangleSum(matrix);
        System.out.println("Largest rectangle = " + largestRect);
    }

    public int largestRectangleSum(int[][] matrix) {
        int mxRectSum = 0;
        for (int top = 0; top < matrix.length; top++) {
            int[] tmp = new int[matrix[top].length];
            for (int bottom = top; bottom < matrix.length; bottom++) {
                for (int j = 0; j < matrix[bottom].length; j++) {
                    tmp[j] += matrix[bottom][j];
                }
                // System.out.println(Arrays.toString(tmp));
                mxRectSum = Math.max(mxRectSum, kadane(tmp));
            }
        }

        return mxRectSum;
    }

    private int kadane(int[] arr) {
        int sum = 0;
        int curSum = 0;
        for (int i = 0; i < arr.length; i++) {
            curSum += arr[i];
            sum = Math.max(sum, curSum);
            if (curSum < 0)
                curSum = 0;
        }

        return sum;
    }
}
