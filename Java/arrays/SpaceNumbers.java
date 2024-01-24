package programs.arrays;

import java.util.Arrays;

public class SpaceNumbers {
    public static void test() {
        SpaceNumbers obj = new SpaceNumbers();

        for (int n = 1; n <= 10; n++) {
            int[] arr = new int[2 * n];

            var res = obj.spaceNumbers(arr, 1, n);
            System.out.print(n + " = ");
            if (res) {
                System.out.print(Arrays.toString(arr));
            }
            System.out.println();
        }
    }

    boolean spaceNumbers(int[] arr, int num, int n) {
        if (num > n) return true;

        for (int i = 0; i + num + 1 < 2 * n; i++) {
            if (arr[i] != 0 || arr[i + num + 1] != 0) continue;
            arr[i] = arr[i + num + 1] = num;
            if (spaceNumbers(arr, num + 1, n)) return true;
            arr[i] = arr[i + num + 1] = 0;
        }

        return false;
    }
}
