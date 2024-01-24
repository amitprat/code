package programs.misc;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/*
given an int array with no duplicate numbers, write a function to return number of ways to calculate a target number.

example: given {2,4,6,8} Target = 12
2 + 4 + 6 = 12,
4 + 8 = 12,
6 + 8 - 2 = 12,
2 - 4 + 6 + 8 = 12,

return 4
 */
public class NumberOfWaysToCalculateTargetNumber {
    public static void test() {
        NumberOfWaysToCalculateTargetNumber obj = new NumberOfWaysToCalculateTargetNumber();
        int[] arr = {2, 4, 6, 8};
//        {
//            int target = 12;
//            Map<String, Integer> cache = new HashMap<>();
//            List<Integer> result = new ArrayList<>();
//
//            int res = obj.countNumWays(arr, target, 0, cache, result);
//            System.out.println("Result[" + target + "]:" + res);
//
//            res = obj.countNumWaysDP(arr, target);
//            System.out.println("[DP]Result[" + target + "]:" + res);
//        }
//        {
//            int target = 18;
//            Map<String, Integer> cache = new HashMap<>();
//            List<Integer> result = new ArrayList<>();
//
//            int res = obj.countNumWays(arr, target, 0, cache, result);
//            System.out.println("Result[" + target + "]:" + res);
//
//            res = obj.countNumWaysDP(arr, target);
//            System.out.println("[DP]Result[" + target + "]:" + res);
//        }
//        {
//            int target = 9;
//            Map<String, Integer> cache = new HashMap<>();
//            List<Integer> result = new ArrayList<>();
//
//            int res = obj.countNumWays(arr, target, 0, cache, result);
//            System.out.println("Result[" + target + "]:" + res);
//
//            res = obj.countNumWaysDP(arr, target);
//            System.out.println("[DP]Result[" + target + "]:" + res);
//        }
        {
            int target = 4;
            Map<String, Integer> cache = new HashMap<>();
            List<Integer> result = new ArrayList<>();

            int res = obj.countNumWays(arr, target, 0, cache, result);
            System.out.println("Result[" + target + "]:" + res);

            res = obj.countNumWaysDP(arr, target);
            System.out.println("[DP]Result[" + target + "]:" + res);
        }
    }

    boolean subsetSum(int[] arr, int target) {
        boolean[][] table = new boolean[target + 1][arr.length + 1];
        for (int sum = 0; sum <= target; sum++) {
            for (int idx = 0; idx <= arr.length; idx++) {
                if (sum == 0) table[sum][idx] = true;
                else if (idx == 0) table[sum][idx] = false;
                else {
                    table[sum][idx] = table[sum][idx - 1];
                    if (arr[idx - 1] <= sum) table[sum][idx] |= table[sum - arr[idx - 1]][idx - 1];
                }
            }
        }
        return table[target][arr.length];
    }

    int countNumWays(int[] arr, int target, int pos, Map<String, Integer> cache, List<Integer> result) {
        if (target == 0) {
//            System.out.print("Result:");
//            for (Integer i : result) System.out.print(i + ", ");
//            System.out.println();
            return 1;
        }
        if (pos >= arr.length) return 0;
        String key = target + "." + pos;
        if (cache.containsKey(key)) {
//            System.out.println("Returned from cache");
            return cache.get(key);
        }
        List<Integer> l1 = new ArrayList<>(result);
        l1.add(arr[pos]);
        List<Integer> l2 = new ArrayList<>(result);
        l2.add(-arr[pos]);
        List<Integer> l3 = new ArrayList<>(result);
        int curCount = countNumWays(arr, target - arr[pos], pos + 1, cache, l1) +
                countNumWays(arr, target + arr[pos], pos + 1, cache, l2) +
                countNumWays(arr, target, pos + 1, cache, l3);
        cache.put(key, curCount);
        return curCount;
    }

    int countNumWaysDP(int[] arr, int target) {
        int[][] table = new int[target + 1][arr.length + 1];
        for (int sum = 0; sum <= target; sum++) {
            for (int idx = 0; idx <= arr.length; idx++) {
                if (sum == 0) table[sum][idx] = 1;
                else if (idx == 0) table[sum][idx] = 0;
                else {
                    table[sum][idx] += 1;
                    if (sum - arr[idx - 1] >= 0) table[sum][idx] += table[sum - arr[idx - 1]][idx - 1];
                    if (sum + arr[idx - 1] <= target) table[sum][idx] += table[sum + arr[idx - 1]][idx - 1];
                }
            }
        }
        int mxResult = table[target][0];
        for (int j = 1; j <= arr.length; j++) {
            System.out.println(table[target][j] + ", ");
            mxResult = Math.max(mxResult, table[target][j]);
        }
        System.out.println();
        return mxResult;
    }
}
