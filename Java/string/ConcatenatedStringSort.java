package programs.string;

import java.util.Arrays;

/*
Given an integer array, sort the integer array such that the concatenated integer of the result array is max. e.g. [4, 94, 9, 14, 1] will be sorted to [9,94,4,14,1] where the result integer is 9944141

quick sort the input BUT
  while comparing two inputs A and B
  instead of doing the regular A > B, DO THIS
      if(ToInt('AB') > ToInt('BA')) return 1
             else -1;
 */
public class ConcatenatedStringSort {
    public static void test() {
        test1();
    }

    private static void test1() {
        ConcatenatedStringSort obj = new ConcatenatedStringSort();
        Integer[] arr = {4, 94, 9, 14, 1};

        System.out.println(Arrays.toString(arr));
        obj.sort(arr);
        System.out.println(Arrays.toString(arr));
    }

    private void sort(Integer[] arr) {
        Arrays.sort(arr, (a, b) -> {
            String as = Integer.toString(a);
            String bs = Integer.toString(b);
            return Integer.valueOf(bs + as) - Integer.valueOf(as + bs);
        });
    }
}
