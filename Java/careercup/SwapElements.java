package programs.careercup;

import java.util.Arrays;

public class SwapElements {
    public static void test() {
        SwapElements obj = new SwapElements();
        String[] arr = {"a1", "a2", "a3", "a4", "a5", "b1", "b2", "b3", "b4", "b5"};

        obj.swapElements(arr);
        System.out.println(Arrays.toString(arr));
    }

    private void swapElements(String[] arr) {
        int m = arr.length/2;
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < i; j++) {
                String tmp = arr[m - i + 2 * j];
                arr[m - i + 2 * j] = arr[m - i + 2 * j + 1];
                arr[m - i + 2 * j + 1] = tmp;
            }
        }
    }
}
