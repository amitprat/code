package programs.careercup;

import java.util.Arrays;
import java.util.Random;

public class KLargestElements {
    public static void test() throws Exception {
        KLargestElements obj = new KLargestElements();
        Random rand = new Random();
        int[] arr = new int[30];
        for (int i = 0; i < 30; i++) arr[i] = rand.nextInt(100);

        int k = 10;

        var res = obj.getKLargestElements(arr, k);
        System.out.println(Arrays.toString(arr));
        System.out.println(Arrays.toString(res));

        MinHeap mnHeap = obj.new MinHeap(k);
        for (var e : arr) mnHeap.add(e);
        int[] newRes = new int[k];
        int j = 0;
        while (!mnHeap.empty()) {
            newRes[j++] = mnHeap.pop();
        }
        System.out.println(Arrays.toString(newRes));
    }

    private int[] getKLargestElements(int[] arr, int k) {
        int[] res = new int[k];

        int p = selectionRank(arr, 0, arr.length - 1, k);
        for (int i = 0; i < k; i++) res[i] = arr[p + i];

        return res;
    }

    private int selectionRank(int[] arr, int l, int r, int k) {
        if (l > r) return -1;
        int p = partition(arr, l, r);
        int q = r - p + 1;
        if (q == k) return p;
        if (q < k) return selectionRank(arr, l, p - 1, k - q);
        return selectionRank(arr, p + 1, r, k);
    }

    private int partition(int[] arr, int l, int r) {
        int pivot = arr[r];
        int j = l;
        for (int i = l; i < r; i++) {
            if (arr[i] <= pivot) {
                swap(arr, j++, i);
            }
        }
        swap(arr, j, r);
        return j;
    }

    private class MinHeap {
        int[] arr;
        int capacity;
        int n = 0;

        MinHeap(int capacity) {
            this.capacity = capacity;
            this.n = 0;
            arr = new int[capacity];
        }

        void add(int elem) throws Exception {
            if (n >= capacity) {
                arr[0] = elem;
                downHeapify(arr, 0);
            } else {
                arr[n++] = elem;
                upHeapify(arr, n - 1);
            }
        }

        int pop() throws Exception {
            if (n <= 0) throw new Exception("Heap empty");

            int res = arr[0];
            arr[0] = arr[n - 1];
            n--;

            downHeapify(arr, 0);

            return res;
        }

        void upHeapify(int[] arr, int e) {
            int p = parent(e);
            while (p != 0 && arr[p] > arr[e]) {
                swap(arr, p, e);
                e = p;
            }
        }

        void downHeapify(int[] arr, int e) {
            int mnPos = e;

            int l = left(e);
            if (l < n && arr[l] < arr[mnPos]) mnPos = l;

            int r = right(e);
            if (r < n && arr[r] < arr[mnPos]) mnPos = r;

            if (mnPos != e) {
                swap(arr, e, mnPos);
                downHeapify(arr, mnPos);
            }
        }

        boolean empty() {
            return n <= 0;
        }

        int left(int e) {
            return 2 * e + 1;
        }

        int right(int e) {
            return 2 * e + 2;
        }

        int parent(int e) {
            return e / 2;
        }
    }

    void swap(int[] arr, int l, int r) {
        int tmp = arr[l];
        arr[l] = arr[r];
        arr[r] = tmp;
    }
}
