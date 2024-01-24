package programs.careercup;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class GenerateLexographicalSortedNumbers {
    public static void test() {
        int n = 101;
        generate(n);

        List<Integer> res = new ArrayList<>();
        generate(n, 1, res);
        System.out.println(res);
    }

    private static void generate(int n) {
        Stack<Integer> st = new Stack<>();
        for (int i = 9; i >= 1; i--) st.push(i);
        List<Integer> res = new ArrayList<>();

        int totalIter = 0;
        while (!st.isEmpty()) {
            totalIter++;
            int cur = st.pop();
            res.add(cur);

            for (int i = 9; i >= 0; i--) {
                if (cur * 10 + i > n) continue;
                st.push(cur * 10 + i);
            }
        }

        System.out.println(res);
        System.out.println("Total iterations = " + totalIter);
    }

    private static void generate(int n, int k, List<Integer> res) {
        if (k > n) return;
        for (int i = 0; i < 10; i++) {
            if (k <= n) {
                res.add(k);
                generate(n, k * 10, res);
                k++;
            }
            if (k % 10 == 0) return;
        }
    }
}
