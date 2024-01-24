package programs.queue;

import java.util.*;
import java.util.stream.Collectors;

public class SlidingWindow {
    public static void test() {
        SlidingWindow obj = new SlidingWindow();
        List<Integer> arr = Arrays.asList(12, 1, 78, 90, 57, 89, 56);
        int k = 3;
        List<Integer> res = obj.slidingWindowMax(arr, k);
        System.out.println(res.stream().map(i -> arr.get(i)).collect(Collectors.toList()));
    }

    public List<Integer> slidingWindowMax(List<Integer> arr, int k) {
        Deque<Integer> dq = new LinkedList<>();
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < arr.size(); i++) {
            removeFromFront(dq, i - k);
            addToDeque(dq, arr, i);
            if (i >= k - 1) result.add(dq.getFirst());
        }
        return result;
    }

    private void addToDeque(Deque<Integer> dq, List<Integer> arr, int index) {
        while (!dq.isEmpty() && arr.get(dq.getLast()) <= arr.get(index)) dq.removeLast();
        dq.add(index);
    }

    private void removeFromFront(Deque<Integer> dq, int index) {
        while (!dq.isEmpty() && dq.getFirst() <= index) dq.removeFirst();
    }
}
