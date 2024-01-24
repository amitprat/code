package programs.misc;

public class MaxOutput {
    static void test() {
        MaxOutput obj = new MaxOutput();
        {
            int[] arr = {3, 4, 5, 1};
            Long res = obj.findMax(arr);
            System.out.println("res = " + res);
        }
        {
            int[] arr = {1, 1, 1, 5};
            Long res = obj.findMax(arr);
            System.out.println("res = " + res);
        }
    }

    Long findMax(int[] arr) {
        Long[][] memo = new Long[arr.length][arr.length];
        return findMax(arr, 0, arr.length - 1, memo);
    }

    private Long findMax(int[] arr, int i, int j, Long[][] memo) {
        if (memo[i][j] != null) return memo[i][j];

        if (i == j) return Long.valueOf(arr[i]);

        long mx = Integer.MIN_VALUE;
        for (int k = i; k < j; k++) {
            Long left = findMax(arr, i, k, memo);
            Long right = findMax(arr, k + 1, j, memo);

            for (char c : "*-+/".toCharArray()) {
                long res = apply(c, left, right);
                mx = Math.max(mx, res);
            }
        }
        memo[i][j] = mx;

        return mx;
    }

    private long apply(char c, Long left, Long right) {
        switch (c) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
        }
        return 0;
    }
}
