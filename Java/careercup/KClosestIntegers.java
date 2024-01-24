package programs.careercup;

import programs.types.Point;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

/*
https://www.careercup.com/question?id=15974664

Given a set of 2D points, some integer k, find the k points closest to the origin, (0,0).

Build a max heap of first k elements. Now for every element left, check if it is smaller than the root of max heap. If it is, then replace the root and call heapify. Do it till the end
 */

public class KClosestIntegers {
    public static void test() {
        KClosestIntegers obj = new KClosestIntegers();
        obj.closestPoints();
    }

    public void closestPoints() {
        List<Point> points = new ArrayList<>();
        points.add(new Point(0,1));
        points.add(new Point(2,5));
        points.add(new Point(5,2));
        points.add(new Point(1,2));
        points.add(new Point(1,0));

        int k = 3;
        Point src = new Point(0, 0);
        List<Point> result = this.closestPoints(points, src, k);

        System.out.println("K Closest Points " + result);
    }

    private List<Point> closestPoints(List<Point> points, Point src, int k) {
        PriorityQueue<PointWithDistance> sortedPointsByDistance = new PriorityQueue<>((o1, o2) -> Double.compare(o1.d, o2.d));
        for(var point : points) {
            sortedPointsByDistance.add(new PointWithDistance(point, distance(src, point)));
        }

        List<Point> result = new ArrayList<>();
        while(k-- > 0) {
            result.add(sortedPointsByDistance.poll().p);
        }

        return result;
    }

    double distance(Point src, Point dst) {
        return Math.sqrt(Math.pow(src.x-src.x, 2) + Math.pow(src.y-dst.y, 2));
    }

    class PointWithDistance implements Comparator {
        Point p;
        double d;

        public PointWithDistance(Point p, double d) {
            this.p = p;
            this.d = d;
        }

        @Override
        public int compare(Object o1, Object o2) {
            return Double.compare(((PointWithDistance)o1).d, ((PointWithDistance)o2).d);
        }
    }
}
