package programs.misc;

import java.util.Arrays;
import java.util.List;

public class FindMissingElementInAP {
    public static void test() {
        FindMissingElementInAP obj = new FindMissingElementInAP();
        List<Integer> arr = Arrays.asList(4, 6, 8, 10, 12, 16);
        System.out.println("Missing element " + obj.findMissing(arr));
    }

    private int findMissing(List<Integer> arr) {
        int l = 0, r = arr.size() - 1;
        int missingElement = -1;
        boolean exists = false;

        int a = arr.get(l);
        int d = Math.min(arr.get(l + 1) - arr.get(l),
                arr.get(l + 2) - arr.get(l + 1));

        while (l <= r) {
            int m = (l + r) / 2;
            int exp = a + m * d;
            if (exp == arr.get(m)) l = m + 1;
            else {
                exists = true;
                missingElement = exp;
                r = m - 1;
            }
        }
        if (exists) return missingElement;
        return a + (arr.size()) * d;
    }
}
