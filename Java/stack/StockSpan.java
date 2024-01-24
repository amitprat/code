package programs.stack;

import java.util.Arrays;
import java.util.List;
import java.util.Stack;

public class StockSpan {
    public static void test() {
        StockSpan obj = new StockSpan();
        List<Integer> prices = Arrays.asList(10, 4, 5, 90, 120, 80);
        var res = obj.span(prices);
        System.out.println(res);
    }

    List<Integer> span(List<Integer> prices) {
        int n = prices.size();
        List<Integer> res = Arrays.asList(new Integer[n]);
        res.set(0, 1);
        Stack<Integer> indices = new Stack<>();
        indices.push(0);

        for (int i = 0; i < n; i++) {
            var price = prices.get(i);
            while (!indices.empty() && prices.get(indices.peek()) <= price) {
                indices.pop();
            }
            res.set(i, indices.empty() ? (i + 1) : (i - indices.peek()));
            indices.push(i);
        }

        return res;
    }
}
