package programs.careercup;

import org.jetbrains.annotations.NotNull;
import programs.types.Point;

import java.util.Arrays;
import java.util.Random;

public class KClosestPointToOrigin {
    public static void test() {
        KClosestPointToOrigin obj = new KClosestPointToOrigin();
        Random rand = new Random();
        Point[] points = {
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10)),
                new Point(rand.nextInt(10), rand.nextInt(10))
        };

        System.out.println(Arrays.toString(points));

        var res = obj.findKClosestPoints(points, 5);
        System.out.println("K Closest points: ");
        System.out.println(Arrays.toString(res));
    }

    private Node[] findKClosestPoints(Point[] points, int k) {
        Node[] res = new Node[k];
        MaxHeap maxHeap = new MaxHeap(k);
        for (var p : points) maxHeap.add(p);

        int index = 0;
        while (!maxHeap.empty()) {
            res[index++] = maxHeap.pop();
        }

        Arrays.sort(res);

        return res;
    }

    private class MaxHeap {
        private final Point origin = new Point(0, 0);
        Node[] arr = null;
        int size = 0;

        MaxHeap(int capacity) {
            arr = new Node[capacity];
        }

        void add(Point node) {
            double curDistance = getDistance(origin, node);
            if (size >= arr.length) {
                if (curDistance < arr[0].distance) {
                    arr[0] = new Node(node, curDistance);
                    downHeapify(0);
                }
                return;
            }

            arr[size++] = new Node(node, curDistance);
            upHeapify(size - 1);
        }

        Node pop() {
            var cur = arr[0];
            arr[0] = arr[size - 1];
            size--;

            downHeapify(0);

            return cur;
        }

        void downHeapify(int index) {
            int l = 2 * index + 1;
            int r = 2 * index + 2;
            int mx = index;
            if (l < size && arr[l].distance < arr[mx].distance) mx = l;
            if (r < size && arr[r].distance < arr[mx].distance) mx = r;
            if (mx != index) {
                var tmp = arr[mx];
                arr[mx] = arr[index];
                arr[index] = tmp;

                downHeapify(mx);
            }
        }

        void upHeapify(int index) {
            int p = index / 2;

            while (p != 0 && arr[p].distance < arr[index].distance) {
                var tmp = arr[index];
                arr[index] = arr[p];
                arr[p] = tmp;

                index = p;
                p = index / 2;
            }
        }

        boolean empty() {
            return size == 0;
        }

        double getDistance(Point p1, Point p2) {
            return Math.sqrt(Math.pow(p2.x - p1.x, 2) + Math.pow(p2.y - p1.y, 2));
        }
    }

    class Node implements Comparable {
        Point point;
        double distance;

        Node(Point point, double distance) {
            this.point = point;
            this.distance = distance;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "point=" + point +
                    ", distance=" + distance +
                    '}';
        }

        @Override
        public int compareTo(@NotNull Object o) {
            double res = distance - ((Node) o).distance;
            return (int) res;
        }
    }
}
