package Java.arrays;

import java.util.*;

public class KSortedArrayIterator implements Iterable {
    private final List<List<Integer>> arrays;

    public KSortedArrayIterator(List<List<Integer>> arrays) {
        this.arrays = arrays;
    }

    public static void test() {
        List<List<Integer>> arrays = new ArrayList<>();
        arrays.add(Arrays.asList(1, 5, 7));
        arrays.add(Arrays.asList(2, 3, 10));
        arrays.add(Arrays.asList(4, 6, 9));
        KSortedArrayIterator obj = new KSortedArrayIterator(arrays);
        for (var item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();
    }

    @Override
    public Iterator iterator() {
        return new PriorityQueueIterator2(arrays);
    }

    // store the pointers array of size of number of arrays and keep the indices.
    class SortedArrayIterator implements Iterator<Integer> {
        private final List<List<Integer>> arrays;
        private final List<Position> pointers;

        SortedArrayIterator(List<List<Integer>> arrays) {
            this.arrays = arrays;
            this.pointers = new ArrayList<>();
        }

        @Override
        public boolean hasNext() {
            boolean isEmpty = true;
            for (var pointer : pointers) {
                if (pointer.arrIndex + 1 < this.arrays.get(pointer.arrIndex).size()) {
                    isEmpty = false;
                    break;
                }
            }

            return isEmpty;
        }

        @Override
        public Integer next() {
            Position minPos = null;
            int minVal = Integer.MAX_VALUE;

            for (var pointer : this.pointers) {
                if (pointer.arrIndex < this.arrays.get(pointer.arrNumber).size()) {
                    Integer curVal = this.arrays.get(pointer.arrNumber).get(pointer.arrIndex);
                    if (curVal < minVal) {
                        minVal = curVal;
                        minPos = pointer;
                    }
                }
            }

            if (minPos != null)
                minPos.arrIndex++;

            return minVal;
        }

        class Position {
            int arrNumber = -1;
            int arrIndex = -1;

            Position(int num, int idx) {
                this.arrNumber = num;
                this.arrIndex = idx;
            }
        }
    }

    // Here the priority queue has size of n*m
    class PriorityQueueIterator implements Iterator<Integer> {
        private final PriorityQueue<Integer> pq;

        PriorityQueueIterator(List<List<Integer>> arrays) {
            pq = new PriorityQueue<>();
            for (var arr : arrays) {
                for (var item : arr) {
                    pq.add(item);
                }
            }
        }

        @Override
        public boolean hasNext() {
            return !pq.isEmpty();
        }

        @Override
        public Integer next() {
            return pq.poll();
        }
    }

    // uses priority queue of size m.
    class PriorityQueueIterator2 implements Iterator<Integer> {
        List<List<Integer>> arrs = new ArrayList<>();
        PriorityQueue<Pair> pq = new PriorityQueue<>((p1, p2) -> Integer.compare(p1.value, p2.value));

        PriorityQueueIterator2(List<List<Integer>> arrs) {
            this.arrs = arrs;

            for (int arrIndex = 0; arrIndex < this.arrs.size(); arrIndex++) {
                var arr = this.arrs.get(arrIndex);
                var val = arr.get(0);
                if (!arr.isEmpty()) {
                    pq.add(new Pair(arrIndex, 0, val));
                }
            }
        }

        @Override
        public boolean hasNext() {
            return !pq.isEmpty();
        }

        public Integer next() {
            var top = pq.poll();
            var arrIndex = top.arrIndex;
            var index = top.index;
            var val = top.value;

            if (index + 1 < this.arrs.get(arrIndex).size()) {
                var newVal = this.arrs.get(arrIndex).get(index + 1);
                pq.add(new Pair(arrIndex, index + 1, newVal));
            }

            return val;
        }
    };

    class Pair {
        Integer arrIndex;
        Integer index;
        Integer value;

        Pair(Integer arrIndex, Integer index, Integer value) {
            this.arrIndex = arrIndex;
            this.index = index;
            this.value = value;
        }
    };
}
