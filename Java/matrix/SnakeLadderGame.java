package programs.matrix;

import java.util.LinkedList;
import java.util.Queue;

public class SnakeLadderGame {
    public static void test() {
        SnakeLadderGame obj = new SnakeLadderGame();
        int N = 30;
        int[] moves = new int[N];
        for (int i = 0; i < N; i++) moves[i] = -1;

        // Ladders
        moves[2] = 21;
        moves[4] = 7;
        moves[10] = 25;
        moves[19] = 28;

        // Snakes
        moves[26] = 0;
        moves[20] = 8;
        moves[16] = 3;
        moves[18] = 6;

        System.out.println("Min Dice throws required is = " + obj.getMinDiceThrows(moves, 0, N));
    }

    private int getMinDiceThrows(int[] moves, int start, int n) {
        Queue<Node> queue = new LinkedList<>();
        queue.add(new Node(start, 0));
        boolean[] visited = new boolean[n];
        visited[start] = true;

        while (!queue.isEmpty()) {
            var cur = queue.poll();
            if (cur.pos == n - 1) return cur.dist;

            for (int j = cur.pos + 1; j <= cur.pos + 6 &&
                    j < n; j++) {
                if (visited[j]) continue;
                visited[j] = true;

                Node nextPos = new Node(j, cur.dist + 1);
                if (moves[j] != -1) nextPos.pos = moves[j];
                queue.add(nextPos);
            }
        }

        return -1;
    }

    class Node {
        int pos;
        int dist;

        Node(int pos, int dist) {
            this.pos = pos;
            this.dist = dist;
        }
    }
}
