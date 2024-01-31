package Java.careercup;

import Java.types.Point;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
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

        System.out.println("Input Points: " + Arrays.toString(points));

        var res1 = obj.findKClosestPoints(points, 5);
        System.out.println("K Closest points: ");
        System.out.println(Arrays.toString(res1));

        var res2 = obj.findKClosestPoints2(Arrays.asList(points), new Point(0, 0), 5);
        System.out.println("K Closest points: ");
        System.out.println(res2);

        obj.findKClosestPoints2();
    }

    private Node[] findKClosestPoints(Point[] points, int k) {
        Node[] res = new Node[k];

        MaxHeap maxHeap = new MaxHeap(k);
        for (var p : points)
            maxHeap.add(p);

        int index = 0;
        while (!maxHeap.empty()) {
            res[index++] = maxHeap.pop();
        }

        Arrays.sort(res, (f, s) -> Double.compare(f.distance, s.distance));

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

            if (l < size && arr[l].distance > arr[mx].distance)
                mx = l;

            if (r < size && arr[r].distance > arr[mx].distance)
                mx = r;

            if (mx != index) {
                var tmp = arr[mx];
                arr[mx] = arr[index];
                arr[index] = tmp;

                downHeapify(mx);
            }
        }

        void upHeapify(int index) {
            int p = (index - 1) / 2;

            while (p != 0 && arr[p].distance < arr[index].distance) {
                var tmp = arr[index];
                arr[index] = arr[p];
                arr[p] = tmp;

                index = p;
                p = (index - 1) / 2;
            }
        }

        boolean empty() {
            return size == 0;
        }

        double getDistance(Point p1, Point p2) {
            return Math.sqrt(Math.pow(p2.x - p1.x, 2) + Math.pow(p2.y - p1.y, 2));
        }
    }

    class Node implements Comparable<Node> {
        Point point;
        double distance;

        Node(Point point, double distance) {
            this.point = point;
            this.distance = distance;
        }

        @Override
        public int compareTo(Node o) {
            double res = distance - o.distance;
            return (int) res;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "point=" + point +
                    ", distance=" + distance +
                    '}';
        }
    }

    // Using build-in priority queue
    public void findKClosestPoints2() {
        List<Point> points = new ArrayList<>();
        points.add(new Point(0, 1));
        points.add(new Point(2, 5));
        points.add(new Point(5, 2));
        points.add(new Point(1, 2));
        points.add(new Point(1, 0));

        int k = 3;
        Point src = new Point(0, 0);
        List<Point> result = this.findKClosestPoints2(points, src, k);

        System.out.println("K Closest Points " + result);
    }

    private List<Point> findKClosestPoints2(List<Point> points, Point src, int k) {
        PriorityQueue<PointWithDistance> sortedPointsByDistance = new PriorityQueue<>(
                (o1, o2) -> Double.compare(o1.d, o2.d));

        for (var point : points) {
            sortedPointsByDistance.add(new PointWithDistance(point, distance(src, point)));
        }

        List<Point> result = new ArrayList<>();
        while (k-- > 0) {
            result.add(sortedPointsByDistance.poll().p);
        }

        return result;
    }

    double distance(Point src, Point dst) {
        return Math.sqrt(Math.pow(dst.x - src.x, 2) + Math.pow(dst.y - src.y, 2));
    }

    class PointWithDistance implements Comparator<PointWithDistance> {
        Point p;
        double d;

        public PointWithDistance(Point p, double d) {
            this.p = p;
            this.d = d;
        }

        @Override
        public int compare(PointWithDistance o1, PointWithDistance o2) {
            return Double.compare(o1.d, o2.d);
        }

        @Override
        public String toString() {
            return "Node{" +
                    "point=" + p +
                    ", distance=" + d +
                    '}';
        }
    }
}
