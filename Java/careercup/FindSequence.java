package programs.careercup;

public class FindSequence {
    public static void test() {
        int[] arr = {4, 7, 5, 1, 3, 8, 9, 6, 2};
        printIncreasingSeq(arr);
    }

    private static void printIncreasingSeq(int[] arr) {
        int n = arr.length;
        int[] leftMin = new int[n];
        int[] rightMax = new int[n];

        leftMin[0] = 0;
        for (int i = 1; i < n; i++) {
            leftMin[i] = arr[leftMin[i - 1]] < arr[i] ? leftMin[i - 1] : i;
        }

        rightMax[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = arr[rightMax[i + 1]] > arr[i] ? rightMax[i + 1] : i;
        }

        for (int i = 1; i < n - 1; i++) {
            if (arr[leftMin[i - 1]] < arr[i] && arr[rightMax[i + 1]] > arr[i]) {
                System.out.println(arr[leftMin[i - 1]] + ", " + arr[i] + ", " + arr[rightMax[i + 1]]);
            }
        }
    }
}
