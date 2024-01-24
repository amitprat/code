package programs.careercup;

import java.util.HashMap;
import java.util.Map;

//https://www.careercup.com/question?id=11070934
public class FindLongestConsecutiveSubset {
    public static void test() {
        int[] arr = {1, 6, 10, 4, 7, 9, 5};
        printLongest(arr);
    }

    static void printLongest(int[] arr) {
        Map<Integer, Integer> map = new HashMap<>();
        int mnBeg = 0, mxEnd = -1;
        for (int i = 0; i < arr.length; i++) {
            int beg, end;
            beg = end = arr[i];
            if (map.containsKey(beg - 1)) beg = map.get(beg - 1);
            if (map.containsKey(end + 1)) end = map.get(end + 1);

            map.put(beg, end);
            map.put(end, beg);

            if (end - beg + 1 > mxEnd - mnBeg) {
                mnBeg = beg;
                mxEnd = end;
            }
        }

        for (int i = mnBeg; i <= mxEnd; i++) {
            System.out.print(i + ", ");
        }
    }
}
