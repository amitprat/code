package programs.careercup;

import java.util.Arrays;
import java.util.Stack;

public class NextGreaterElementArray {
    public static void test() {
        int[] arr = {7, 5, 6, 3, 4, 1, 2, 9, 11};
        var res = populateNextGreater(arr);
        System.out.println(Arrays.toString(res));
    }

    private static int[] populateNextGreater(int[] arr) {
        int n = arr.length;
        int[] res = new int[n];
        Stack<Integer> st = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[i] >= st.peek()) st.pop();

            if (st.empty()) res[i] = -1;
            else res[i] = st.peek();

            st.push(arr[i]);
        }

        return res;
    }
}
