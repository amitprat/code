package programs.careercup;

import java.util.Stack;

public class PrintOrderedSeq {
    public static void test() {
        int[] arr = {3, 4, 7, 1, 8, 12};

        printSeq(arr);

        printSeqUsingStack(arr);
    }

    // INF, 3, 4, 7,
    private static void printSeq(int[] arr) {
        int[] leftMax = new int[arr.length];

        leftMax[0] = Integer.MIN_VALUE;
        for (int i = 1; i < arr.length; i++) {
            leftMax[i] = Math.max(leftMax[i - 1], arr[i - 1]);
        }

        int rightMin = Integer.MAX_VALUE;
        for (int i = arr.length - 1; i >= 0; i--) {
            if (i < arr.length - 1) rightMin = Math.min(rightMin, arr[i + 1]);
            if (arr[i] > leftMax[i] && arr[i] < rightMin) System.out.println(arr[i]);
        }
    }

    private static void printSeqUsingStack(int[] arr) {
        Stack<Integer> st = new Stack<>();
        int mx = Integer.MIN_VALUE;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > mx) {
                mx = arr[i];
                st.push(mx);
            }
            while (!st.empty() && arr[i] < st.peek()) st.pop();
        }

        while (!st.empty()) {
            System.out.println(st.pop());
        }
    }
}
