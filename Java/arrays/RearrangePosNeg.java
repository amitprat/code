package programs.arrays;

import java.util.Arrays;
import java.util.List;

public class RearrangePosNeg {
    public static void test() {
        List<Integer> l = Arrays.asList(1, -2, 3, -4, -5, -6, -7, 8, 9, 4, 10, 11, 12);

        System.out.println(l.toString());
        rearrange(l);

        System.out.println(l.toString());
    }

    static void rearrange(List<Integer> l) {
        int i = 0, j = 0;
        boolean evenExp = true;

        while (j < l.size()) {
            if (isExp(l, j, evenExp)) {
                rightShift(l, i, j);
                i++;
            }
            j++;
            evenExp = !evenExp;
        }
    }

    static void rightShift(List<Integer> l, int i, int j) {
        int tmp = l.get(i);
        int k = i + 1;
        while (k <= j) {
            tmp = l.get(k);
            l.set(k, l.get(k - 1));
            k++;
        }
        l.set(i, tmp);
    }

    static boolean isExp(List<Integer> l, int pos, boolean isEven) {
        if (isEven && (pos & 1) == 0 && l.get(pos) > 0) return true;
        return !isEven && (pos & 1) != 0 && l.get(pos) < 0;
    }
}
