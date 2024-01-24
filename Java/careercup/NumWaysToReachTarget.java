package programs.careercup;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class NumWaysToReachTarget {
    public static void test() {
        NumWaysToReachTarget obj = new NumWaysToReachTarget();
        int[] arr = {2, 4, 6, 8};
        int target = 12;

        Map<String, Integer> cache = new HashMap<>();
        List<Integer> curResult = new ArrayList<>();
        var res = obj.getNumWays(arr, target, arr.length, cache, curResult);
        System.out.println(res);
    }

    private int getNumWays(int[] arr, int target, int index, Map<String, Integer> cache, List<Integer> curResult) {
        if (target == 0) {
            System.out.println("Res: " + curResult);
            return 1;
        }
        if (cache.containsKey(index + ":" + target)) return cache.get(index + ":" + target);
        if (index == 0) return 0;

        var cur = getNumWays(arr, target, index - 1, cache, curResult);

        curResult.add(arr[index - 1]);
        cur += getNumWays(arr, target - arr[index - 1], index - 1, cache, curResult);
        curResult.remove(curResult.size() - 1);

        curResult.add(-arr[index - 1]);
        cur += getNumWays(arr, target + arr[index - 1], index - 1, cache, curResult);
        curResult.remove(curResult.size() - 1);

        cache.put(index + ":" + target, cur);
        return cache.get(index + ":" + target);
    }
}
