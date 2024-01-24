package Java.arrays;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class FindLargestContiguousSequence {
    public static void test() {
        FindLargestContiguousSequence obj = new FindLargestContiguousSequence();
        int[] arr = { 1, 6, 10, 4, 7, 9, 5, 9, 11, 13, 12 };

        int[] res = obj.findLargest(arr);
        System.out.println(Arrays.toString(res));
    }

    private int[] findLargest(int[] arr) {
        Map<Integer, Integer> map = new HashMap<>();
        int first = 0, last = 0;

        for (int i = 0; i < arr.length; i++) {
            int beg = arr[i], end = arr[i];

            if (map.containsKey(beg - 1))
                beg = map.get(beg - 1);

            if (map.containsKey(end + 1))
                end = map.get(end + 1);

            map.put(beg, end);
            map.put(end, beg);

            if (end - beg > last - first) {
                last = end;
                first = beg;
            }
        }

        int[] res = new int[last - first + 1];
        for (int i = first; i <= last; i++)
            res[i - first] = i;

        return res;
    }
}
