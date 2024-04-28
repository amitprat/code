package programs.careercup;

import java.util.Arrays;
import java.util.List;
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

    List<Integer> stockSpan2(int[] prices) {
        int[] span = new int[prices.length];
        Stack<Integer> indices = new Stack<>();

        for (int i = 0; i < n; i++) {
            var price = prices.get(i);
            while (!indices.empty() && prices[indices.peek()] < price) {
                indices.pop();
            }
            span[i] = indices.empty() ? (i + 1) : (i - indices.peek());
            indices.push(i);
        }

        return span;
    }
}
