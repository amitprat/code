package programs.careercup;

import programs.types.Interval;

import java.util.Arrays;
import java.util.Comparator;

public class MaxTimeCovered {
    public static void test() {
        MaxTimeCovered obj = new MaxTimeCovered();
        Interval[] input = {new Interval(1, 4), new Interval(6, 11), new Interval(2, 4), new Interval(7, 9), new Interval(10, 15)};
        var out = obj.maxTimeCovered(input);
        System.out.println("Time covered = " + out);
    }

    private int maxTimeCovered(Interval[] input) {
        Arrays.sort(input, Comparator.comparingInt((var interval) -> interval.start));
        int timeCovered = 0;
        int ending = 0;
        for (Interval interval : input) {
            timeCovered += Math.max(interval.end - Math.max(interval.start, ending), 0);
            ending = Math.max(interval.end, ending);
        }

        return timeCovered;
    }
}
