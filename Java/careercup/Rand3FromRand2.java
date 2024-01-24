package programs.careercup;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Rand3FromRand2 {
    Random random = new Random();

    public static void test() {
        Rand3FromRand2 obj = new Rand3FromRand2();
        Map<Integer, Integer> counter = new HashMap<>();
        int mx = 100;
        for (int i = 0; i < mx; i++) {
            int cur = obj.rand3();
            if (!counter.containsKey(cur)) counter.put(cur, 1);
            else counter.put(cur, counter.get(cur) + 1);
        }

        for (var entry : counter.entrySet()) {
            System.out.println("Probability of " + entry.getKey() + " = " + (double) (entry.getValue()) / (double) mx);
        }
    }

    private int rand3() {
        int res = Integer.MAX_VALUE;
        while (res >= 3) {
            res = 2 * rand2() + rand2();
        }
        return res;
    }

    private int rand2() {
        return random.nextInt(2);
    }
}
