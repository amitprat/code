package programs.careercup;

public class SortedRotatedArray {
    public static void test() {
        SortedRotatedArray obj = new SortedRotatedArray();
        int[] arr = {6, 7, 8, 1, 2, 3, 4, 5};

        var timesRotated = obj.arrRotated(arr);
        System.out.println(timesRotated);
    }

    private int arrRotated(int[] arr) {
        int l = 0, r = arr.length - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] > arr[r]) l = m + 1;
            else r = m;
        }

        return l;
    }
}
