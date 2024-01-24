package Java.arrays;

import java.util.Stack;

public class AreaUnderHistogram {
    public static void test() {
        int[] hist = { 6, 2, 5, 4, 5, 1, 6 };
        var res = areaUnderHist(hist);
        System.out.println("Area under histogram = " + res);
    }

    static int areaUnderHist(int[] hist) {
        Stack<Integer> st = new Stack<>();
        int mxArea = 0;
        int i = 0;
        while (i < hist.length) {
            if (st.empty() || hist[i] >= hist[st.peek()]) {
                st.push(i++);
            } else {
                int height = hist[st.pop()];
                int width = st.empty() ? i : i - st.peek() - 1;
                // System.out.printf("Height = %d, Width = %d\n", height, width);

                mxArea = Math.max(mxArea, height * width);
            }
        }

        while (!st.empty()) {
            int height = hist[st.pop()];
            int width = st.empty() ? i : i - st.peek() - 1;
            // System.out.printf("Height = %d, Width = %d\n", height, width);

            mxArea = Math.max(mxArea, height * width);
        }

        return mxArea;
    }
}
