package programs.careercup;

import java.util.Arrays;
import java.util.Stack;

public class StockSpan {
    public static void test() {
        int[] price = {10, 4, 5, 90, 120, 80};
        stockSpan(price);
        stockSpan1(price);
    }

    private static void stockSpan(int[] price) {
        Stack<Integer> st = new Stack<>();
        int[] span = new int[price.length];
        for (int i = 0; i < price.length; i++) {
            while (!st.empty() && price[st.peek()] < price[i]) st.pop();
            span[i] = st.empty() ? (i + 1) : (i - st.peek());
            st.push(i);
        }

        System.out.println(Arrays.toString(span));
    }

    private static void stockSpan1(int[] price) {
        int[] span = new int[price.length];
        for (int i = 0; i < price.length; i++) {
            int j = i - 1;
            for (; j >= 0 && price[j] <= price[i]; j--) ;

            span[i] = (j == -1) ? i + 1 : (i - j);
        }

        System.out.println(Arrays.toString(span));
    }
}
