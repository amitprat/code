package programs.matrix;

import programs.types.Pair;

import java.util.Arrays;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

public class SortRowColumnWiseSortedMatrix {
    public static void test() {
        test1();
        test2();
    }

    private static void test2() {
        SortRowColumnWiseSortedMatrix obj = new SortRowColumnWiseSortedMatrix();
        int[][] arr = {
                {1, 2, 3},
                {6, 7, 8},
                {8, 9, 10},
                {13, 14, 15}
        };

        int[] res = obj.sort(arr);
        System.out.println(Arrays.toString(res));
    }

    private static void test1() {
        SortRowColumnWiseSortedMatrix obj = new SortRowColumnWiseSortedMatrix();
        int[][] arr = {
                {1, 9, 17},
                {11, 34, 37},
                {35, 36, 39}
        };

        int[] res = obj.sort(arr);
        System.out.println(Arrays.toString(res));
    }

    // TODO - correct me
    private int[] sort(int[][] arr) {
        int n = arr.length;
        int m = arr[0].length;
        int[] res = new int[n * m];
        PriorityQueue<Pair<Integer, Integer>> pq = new PriorityQueue<>(Math.max(n, m),
                (a, b) -> arr[a.first][a.second] - arr[b.first][b.second]);
        pq.add(new Pair<>(0, 0));
        int index = 0;
        int mxPqSize = 1;
        Set<Pair<Integer, Integer>> set = new HashSet<>();
        while (!pq.isEmpty()) {
            var pos = pq.remove();
            res[index++] = arr[pos.first][pos.second];
            if (pos.first + 1 < n && set.contains(pos)) pq.add(new Pair<>(pos.first + 1, pos.second));
            if (pos.second + 1 < m) pq.add(new Pair<>(pos.first, pos.second + 1));
            if (pq.size() > mxPqSize) mxPqSize = pq.size();
        }
        System.out.println("Max PQ Size = " + mxPqSize);
        return res;
    }
}
