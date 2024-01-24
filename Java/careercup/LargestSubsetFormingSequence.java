package programs.careercup;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/*
https://www.careercup.com/question?id=11070934

Given an int array which might contain duplicates, find the largest subset of it which form a sequence.
Eg. {1,6,10,4,7,9,5}
then ans is 4,5,6,7

Sorting is an obvious solution. Can this be done in O(n) time
 */

public class LargestSubsetFormingSequence {
    public static void test() {
        LargestSubsetFormingSequence obj = new LargestSubsetFormingSequence();
        int[] arr = {1,6,10,4,7,9,5,0,8,2,11};

        int[] res = obj.largestSubsequenceUsingSorting(arr);
        System.out.println(Arrays.toString(res));
    }

    private int[] largestSubsequenceUsingSorting(int[] arr) {
        if(arr.length == 0) return new int[] {};

        int[] result = new int[] {Integer.MAX_VALUE, Integer.MIN_VALUE};
        Arrays.sort(arr);
        int prev = arr[0];
        int start = 0;
        for(int i=1;i<arr.length;i++) {
            if(prev+1 != arr[i]) {
                if(result[0] == Integer.MAX_VALUE || result[1]-result[0] < arr[i-1]-arr[start]) {
                    result = new int[] {prev, arr[i-1]};
                    start = i;
                }
            }
            prev = arr[i];
        }

        if(result[0] == Integer.MAX_VALUE || result[1]-result[0] < arr[arr.length-1]-arr[start]) {
            result = new int[] {arr[start], arr[arr.length-1]};
        }

        return result;
    }
    private int[] largestSubseq(int[] arr) {
        int[] result = new int[] {Integer.MAX_VALUE, Integer.MIN_VALUE};
        Map<Integer, Integer> map = new HashMap<>();
        for(int i=0;i<arr.length;i++) {
            int beg = arr[i], end = arr[i];
            if(map.containsKey(beg-1)) beg = map.get(beg-1);
            if(map.containsKey(end+1)) end = map.get(end+1);

            if(result[0] == Integer.MAX_VALUE || end - beg > result[1]-result[0]) {
                result = new int[] {beg, end};
            }

            map.put(beg, end);
            map.put(end, beg);
        }

        return result;
    }
}
