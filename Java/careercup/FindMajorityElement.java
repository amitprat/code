package programs.careercup;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class FindMajorityElement {
    public static void test() {
        int[] arr = {4, 4, 5, 6, 7, 8, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 10};
        int n = 3;

        System.out.println("Array size = " + arr.length + ", cutoff = " + arr.length / n);
        Map<Integer, Integer> res = findMajority(arr, n);
        System.out.println(res);

        res = getMajorityElement1(arr, n);
        System.out.println(res);
    }

    private static Map<Integer, Integer> findMajority(int[] arr, int n) {
        Map<Integer, Integer> res = new HashMap<>();
        for (var e : arr) {
            res.put(e, (res.containsKey(e) ? res.get(e) : 0) + 1);
            if (res.size() == n) {
                res.entrySet().removeIf(p -> {
                    res.put(p.getKey(), res.get(p.getKey()) - 1);
                    return res.get(p.getKey()) <= 0;
                });
            }
        }
        res.entrySet().forEach(p -> res.put(p.getKey(), 0));
        Arrays.stream(arr).forEach(p -> {
            if (res.containsKey(p)) res.put(p, res.get(p) + 1);
        });
        res.entrySet().removeIf(p -> p.getValue() < arr.length / n);

        return res;
    }

    private static Map<Integer, Integer> getMajorityElement1(int[] arr, int n) {
        int a = Integer.MIN_VALUE, b = Integer.MIN_VALUE;
        int cnt1 = 0, cnt2 = 0;
        Map<Integer, Integer> res = new HashMap<>();
        for (var e : arr) {
            if (cnt1 == 0) {
                a = e;
                cnt1++;
            } else if (cnt2 == 0) {
                b = e;
                cnt2++;
            } else {
                cnt1--;
                cnt2--;
            }
        }

        cnt1 = cnt2 = 0;
        for (var e : arr) {
            if (e == a) cnt1++;
            if (e == b) cnt2++;
        }

        if (cnt1 >= arr.length / n) res.put(a, cnt1);
        if (cnt2 >= arr.length / n) res.put(b, cnt2);

        return res;
    }
}
