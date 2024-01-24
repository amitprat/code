package programs.careercup;

import org.jetbrains.annotations.NotNull;

import java.util.PriorityQueue;

public class PrintSorted {
    public static void test() {
        PrintSorted obj = new PrintSorted();
        int[][] matrix = {
                {20, 40, 80},
                {5, 60, 90},
                {45, 50, 55}
        };

        obj.printSorted(matrix);
    }

    private void printSorted(int[][] matrix) {
        PriorityQueue<Node> pq = new PriorityQueue<Node>();
        for (int i = 0; i < matrix.length; i++) {
            if (matrix[i].length != 0) pq.add(new Node(matrix[i][0], i, 0));
        }

        while (!pq.isEmpty()) {
            var cur = pq.poll();
            if (matrix[cur.row].length > cur.col + 1) {
                pq.add(new Node(matrix[cur.row][cur.col + 1], cur.row, cur.col + 1));
            }
            System.out.println(cur.val);
        }
    }

    class Node implements Comparable {
        int val;
        int row, col;

        Node(int val, int row, int col) {
            this.val = val;
            this.row = row;
            this.col = col;
        }

        @Override
        public int compareTo(@NotNull Object o) {
            return val - ((Node) o).val;
        }
    }
}
