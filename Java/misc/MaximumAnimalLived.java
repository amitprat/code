package programs.misc;

import programs.types.Interval;

import java.util.Arrays;
import java.util.List;

public class MaximumAnimalLived {
    public static void test() {
        List<Interval> l = Arrays.asList(
                new Interval(5, 11),
                new Interval(6, 18),
                new Interval(2, 12),
                new Interval(3, 12)
        );

        var res = maxPeriod(l);

        System.out.println(res);
    }

    private static Interval maxPeriod(List<Interval> l) {
        int[] starts = l.stream().mapToInt(s -> s.start).toArray();
        int[] ends = l.stream().mapToInt(s -> s.end).toArray();

        Arrays.sort(starts);
        Arrays.sort(ends);

        int s = 0, e = 0;
        int mx = 0;
        Interval res = null;
        while (s <= l.size()) {
            if (s < l.size() && starts[s] <= ends[e]) s++;
            else {
                if (s - e > mx) {
                    mx = Math.max(mx, s - e);
                    res = new Interval(starts[s - 1], ends[e]);
                }
                e++;
                if (s == l.size()) break;
            }
        }

        System.out.println("Max Period " + mx);

        return res;
    }
}
