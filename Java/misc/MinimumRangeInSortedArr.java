package programs.misc;

import programs.types.Pair;

import java.util.*;

public class MinimumRangeInSortedArr {
    public static void test() {
        List<List<Integer>> l = Arrays.asList(
                Arrays.asList(0, 10, 255),
                Arrays.asList(2, 11, 257),
                Arrays.asList(4, 19, 258)
        );

        Set<Integer> res = getMinRange(l);
        System.out.println(res);
    }

    private static Set<Integer> getMinRange(List<List<Integer>> l) {
        PriorityQueue<Pair<Integer, Integer>> pq = new PriorityQueue<>(
                Comparator.comparingInt(a -> l.get(a.first).get(a.second))
        );

        int minDiff = Integer.MAX_VALUE;
        int curMaxValue = Integer.MIN_VALUE;
        Set<Integer> localMinSet = new HashSet<>();
        Set<Integer> globalMinSet = null;

        for (int i = 0; i < l.size(); i++) {
            if (i < l.get(i).size()) {
                curMaxValue = Math.max(curMaxValue, l.get(i).get(0));
                pq.add(new Pair(i, 0));
                localMinSet.add(l.get(i).get(0));
            } else return localMinSet;
        }

        while (!pq.isEmpty()) {
            var top = pq.poll();
            int minValue = get(l, top);
            int curDiff = curMaxValue - minValue;
            if (curDiff < minDiff) {
                minDiff = curDiff;
                globalMinSet = new HashSet<>(localMinSet);
            }
            localMinSet.remove(minValue);

            if (hasNext(l, top)) {
                top.second += 1;
                int nextVal = get(l, top);
                if (nextVal > curMaxValue) curMaxValue = nextVal;
                pq.add(top);
                localMinSet.add(nextVal);
            } else break;
        }

        return globalMinSet;
    }

    private static boolean hasNext(List<List<Integer>> l, Pair<Integer, Integer> top) {
        return top.second + 1 < l.get(top.first).size();
    }

    private static int get(List<List<Integer>> l, Pair<Integer, Integer> top) {
        return l.get(top.first).get(top.second);
    }
}
