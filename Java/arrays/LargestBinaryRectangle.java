package Java.arrays;

import java.util.Stack;

public class LargestBinaryRectangle {
    public static void test() {
        int[][] binaryRectangle = {
                { 0, 1, 1, 0 },
                { 1, 1, 1, 1 },
                { 1, 1, 1, 1 },
                { 1, 1, 0, 0 },
        };

        LargestBinaryRectangle obj = new LargestBinaryRectangle();
        var largestRectangle = obj.largestBinaryRectangle(binaryRectangle);
        System.out.println("Largest binary rectangle = " + largestRectangle);
    }

    private int largestBinaryRectangle(int[][] matrix) {
        int mxRectangle = 0;
        for (int r = 0; r < matrix.length; r++) {
            if (r != 0) {
                for (int c = 0; c < matrix[r].length; c++) {
                    if (matrix[r][c] == 1)
                        matrix[r][c] += matrix[r - 1][c];
                }
            }
            mxRectangle = Math.max(mxRectangle, areaUnderHist(matrix[r]));
        }

        return mxRectangle;
    }

    private int areaUnderHist(int[] hist) {
        Stack<Integer> st = new Stack<>();
        int mxArea = 0;
        int i = 0;

        while (i < hist.length || !st.empty()) {
            if (i == hist.length || (!st.empty() && hist[st.peek()] > hist[i])) {
                int height = hist[st.pop()];
                int width = st.empty() ? i : i - st.peek() - 1;
                mxArea = Math.max(mxArea, height * width);
            } else {
                st.push(i++);
            }
        }

        return mxArea;
    }
}
