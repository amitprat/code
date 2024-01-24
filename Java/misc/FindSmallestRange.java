package programs.misc;

import programs.types.Pair;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class FindSmallestRange {
    public static void test() {
        FindSmallestRange obj = new FindSmallestRange();
        List<Integer> l1 = Arrays.asList(4, 10, 15, 24, 26);
        List<Integer> l2 = Arrays.asList(0, 9, 12, 20);
        List<Integer> l3 = Arrays.asList(5, 18, 22, 30);
        System.out.println("Smallest Range = " + obj.findRange(Arrays.asList(l1, l2, l3)));
    }

    private List<Integer> findRange(List<List<Integer>> lists) {
        int minDiff = Integer.MAX_VALUE;
        List<Integer> indices = new ArrayList<>(Collections.nCopies(lists.size(), 0));
        List<Integer> result = null;
        boolean done = false;
        while (!done) {
            Pair<Integer, Integer> curMinDiff = getDiff(lists, indices);
            if (curMinDiff.first < minDiff) {
                minDiff = curMinDiff.first;
                result = indices;
            }
            int next = indices.get(curMinDiff.second) + 1;
            if (next >= lists.get(curMinDiff.second).size()) done = true;
            else indices.set(curMinDiff.second, next);
        }
        return result;
    }

    private Pair<Integer, Integer> getDiff(List<List<Integer>> lists, List<Integer> indices) {
        int index = 0;
        int mn = lists.get(index).get(indices.get(index));
        int mx = lists.get(index).get(indices.get(index));
        for (int i = 1; i < indices.size(); i++) {
            int cur = lists.get(i).get(indices.get(i));
            if (cur < mn) {
                mn = cur;
                index = i;
            } else if (cur > mx) {
                mx = cur;
            }
        }
        return new Pair<>(mx - mn, index);
    }

    private List<Integer> findRange(List<Integer> l1, List<Integer> l2, List<Integer> l3) {
        int minDiff = Integer.MAX_VALUE;
        List<Pair<Integer, Integer>> positions = Arrays.asList(new Pair(0, l1.size() - 1), new Pair(0, l2.size() - 1), new Pair(0, l3.size() - 1));
        List<Pair<Integer, Integer>> result = null;
        boolean done = false;
        while (!done) {
            Pair<Integer, Integer> curDiffMin = getDiff(l1, l2, l3, positions);
            if (curDiffMin.first < minDiff) {
                minDiff = curDiffMin.first;
                result = positions;
            }
            positions.get(curDiffMin.second).first++;
            if (positions.get(curDiffMin.second).first >= positions.get(curDiffMin.second).second) done = true;
        }
        return result.stream().map(s -> s.first).collect(Collectors.toList());
    }

    private Pair<Integer, Integer> getDiff(List<Integer> l1, List<Integer> l2, List<Integer> l3, List<Pair<Integer, Integer>> positions) {
        int mnIndex = 0;
        int curMin = l1.get(positions.get(0).first);
        if (l2.get(positions.get(1).first) < curMin) {
            curMin = l2.get(positions.get(1).first);
            mnIndex = 1;
        }
        if (l3.get(positions.get(2).first) < curMin) {
            curMin = l3.get(positions.get(2).first);
            mnIndex = 2;
        }

        return new Pair<>(curMin, mnIndex);
    }
}
