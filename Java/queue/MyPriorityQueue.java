package programs.queue;

import java.util.*;

public class MyPriorityQueue<T extends Comparable<T>> {
    List<T> elements = null;
    private Comparator<T> comparator = null;

    public MyPriorityQueue() {
        elements = new ArrayList<>();
        comparator = Comparator.naturalOrder();
    }

    public MyPriorityQueue(Comparator<T> comparator) {
        this.comparator = comparator;
        elements = new ArrayList<>();
    }

    public MyPriorityQueue(List<T> elements) {
        this.elements = new ArrayList<>(elements);
        comparator = Comparator.naturalOrder();
        buildHeap();
    }

    public MyPriorityQueue(List<T> elements, Comparator<T> comparator) {
        this.elements = new ArrayList<>(elements);
        this.comparator = comparator;
        buildHeap();
    }

    public static void test() {
        // Min heap
        {
            System.out.println("Min heap : ");
            MyPriorityQueue<Integer> pq = new MyPriorityQueue<>(Arrays.asList(1, 5, 2, 6, 3, 9, 2, 7));

            try {
                while (!pq.isEmpty()) System.out.print(pq.pop() + " ");
            } catch (Exception e) {
                System.out.println(e);
            }
            System.out.println();
        }

        // Min heap
        {
            System.out.println("Min heap : ");
            MyPriorityQueue<Integer> pq = new MyPriorityQueue<>();
            pq.add(1);
            pq.add(5);
            pq.add(2);
            pq.add(6);
            pq.add(3);
            pq.add(9);
            pq.add(2);
            pq.add(7);

            try {
                while (!pq.isEmpty()) System.out.print(pq.pop() + " ");
            } catch (Exception e) {
                System.out.println(e);
            }
            System.out.println();
        }

        // Max heap
        {
            System.out.println("Max heap : ");
            MyPriorityQueue<Integer> pq = new MyPriorityQueue<Integer>(Comparator.reverseOrder());
            pq.add(1);
            pq.add(5);
            pq.add(2);
            pq.add(6);
            pq.add(3);
            pq.add(9);
            pq.add(2);
            pq.add(7);

            try {
                while (!pq.isEmpty()) System.out.print(pq.pop() + " ");
            } catch (Exception e) {
                System.out.println(e);
            }
            System.out.println();
        }

        // Max heap
        {
            System.out.println("Max heap : ");
            MyPriorityQueue<Integer> pq = new MyPriorityQueue<>(Arrays.asList(1, 5, 2, 6, 3, 9, 2, 7), Comparator.reverseOrder());
            try {
                while (!pq.isEmpty()) System.out.print(pq.pop() + " ");
            } catch (Exception e) {
                System.out.println(e);
            }
            System.out.println();
        }

        // Max heap
        {
            System.out.println("Max heap : ");
            MyPriorityQueue<Integer> pq = new MyPriorityQueue<>(Arrays.asList(1, 5, 2, 6, 3, 9, 2, 7), Comparator.reverseOrder());

            try {
                pq.set(0, 10);
                pq.set(2, 20);
                pq.set(2, 1);
                pq.set(4, 3);
                while (!pq.isEmpty()) System.out.print(pq.pop() + " ");
            } catch (Exception e) {
                System.out.println(e);
            }
            System.out.println();
        }
    }

    public void add(T elem) {
        elements.add(elem);

        upHeapify(elements.size() - 1);
    }

    public void set(int index, T elem) throws Exception {
        if (index > elements.size()) throw new Exception("Out of index!!");
        if (index == elements.size()) add(elem);
        else {
            T old = elements.get(index);
            elements.set(index, elem);
            if (comparator.compare(elem, old) <= 0) upHeapify(index);
            else downHeapify(index);
        }
    }

    public T top() throws Exception {
        if (isEmpty()) throw new Exception("Empty!!");
        return elements.get(0);
    }

    public T pop() throws Exception {
        if (isEmpty()) throw new Exception("Empty!!");
        var elem = elements.get(0);
        elements.set(0, elements.get(elements.size() - 1));
        elements.remove(elements.size() - 1);

        downHeapify(0);

        return elem;
    }

    public boolean isEmpty() {
        return elements.isEmpty();
    }

    private void downHeapify(int index) {
        int target = index;
        int l = left(index);
        if (isValid(l) && isLess(l, target)) target = l;

        int r = right(index);
        if (isValid(r) && isLess(r, target)) target = r;

        if (target != index) {
            Collections.swap(elements, index, target);
            downHeapify(target);
        }
    }

    private void upHeapify(int index) {
        int p = parent(index);
        while (index != 0 && isLess(index, p)) {
            Collections.swap(elements, index, p);
            index = p;
            p = parent(index);
        }
    }

    private void buildHeap() {
        for (int i = elements.size() - 1; i >= 0; i--) {
            downHeapify(i);
        }
    }

    private boolean isValid(int index) {
        return index < elements.size();
    }

    private int left(int i) {
        return 2 * i + 1;
    }

    private int right(int i) {
        return 2 * i + 2;
    }

    private int parent(int i) {
        return (i - 1) / 2;
    }

    private boolean isLess(int index, int target) {
        return comparator.compare(elements.get(index), elements.get(target)) <= 0;
    }
}
