package programs.misc;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;

public class MedianStream {
    public static void test() {
        MedianStream obj = new MedianStream();
        int[] arr = {45, 8, 65, 5, 75, 7, 34, 24, 6, 57, 57, 45};
        int n = arr.length;
        for (int i = 1; i < n; i++) {
            double res = obj.getMedian(arr, i);
            System.out.println("programs.misc.Median: " + res);
            int[] newArr = Arrays.copyOf(arr, i);
            Arrays.sort(newArr);
            //Arrays.stream(newArr).forEach(x -> System.out.print(x + " "));
            //System.out.println();
            double correctMedian = (i % 2 == 0) ? (newArr[i / 2 - 1] + newArr[i / 2]) / 2 : newArr[i / 2];
            System.out.println("Correct programs.misc.Median: " + correctMedian);
        }
    }

    double getMedian(int[] arr, int n) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());

        if (n == 0) return 0;
        for (int i = 0; i < n; i++) {
            minHeap.offer(arr[i]);
            maxHeap.offer(minHeap.poll());

            if (minHeap.size() < maxHeap.size()) {
                minHeap.offer(maxHeap.poll());
            }
        }

        if (minHeap.size() > maxHeap.size()) return minHeap.peek();
        else return (minHeap.peek() + maxHeap.peek()) / 2;
    }
}
