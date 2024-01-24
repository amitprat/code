package Java.arrays;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MaxSubArrayWithKUniqueValues {
    public static void test() {
        List<Integer> arr = Arrays.asList(1, 2, 3, 1, 4, 3, 4, 1, 2);

        var res = maxLength(arr, 3);
        System.out.println("Max Length " + res);
    }

    private static int maxLength(List<Integer> arr, int k) {
        Map<Integer, Integer> map = new HashMap<>();
        int s = 0, e = 0;
        int mxDiff = 0, mxStart = -1, mxEnd = -1;

        while (e < arr.size()) {
            int prev = 0;
            if (map.containsKey(arr.get(e)))
                prev = map.get(arr.get(e));
            map.put(arr.get(e), prev + 1);

            if (map.size() <= k) {
                if (e - s + 1 > mxDiff) {
                    mxDiff = e - s + 1;
                    mxStart = s;
                    mxEnd = e;
                }
            } else {
                while (s < e && map.size() > k) {
                    var val = map.get(arr.get(s));
                    val--;

                    if (val == 0)
                        map.remove(arr.get(s));
                    else
                        map.put(arr.get(s), val);

                    s++;
                }
            }

            e++;
        }

        if (mxDiff != 0) {
            StringBuffer sb = new StringBuffer();
            while (mxStart <= mxEnd)
                sb.append(arr.get(mxStart++) + " ");

            System.out.println(sb.toString());
        }

        return mxDiff;
    }
}
