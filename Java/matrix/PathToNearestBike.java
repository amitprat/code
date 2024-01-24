package programs.matrix;

import programs.types.Point;

import java.util.*;

public class PathToNearestBike {
    public static void test() {
        PathToNearestBike obj = new PathToNearestBike();
        char[][] matrix = {
                {'.', '.', '.', '.', '.', '#'},
                {'.', '.', 'E', '.', '.', '#'},
                {'#', '#', '#', '#', '.', '#'},
                {'.', 'B', '.', '.', '.', '#'},
                {'.', '.', '.', '.', '.', 'B'}
        };

        Point p = new Point(1, 2);
        var res = obj.getPath(matrix, p);
        System.out.println(res);
    }

    private class Node {
        Point p;
        int dist;
        List<Point> path = new ArrayList<>();

        Node() {
        }

        Node(Point p, int dist) {
            this.p = p;
            this.dist = dist;
            path.add(p);
        }

        Node(Point p, List<Point> current, int dist) {
            this.p = p;
            this.dist = dist;
            path.addAll(current);
            path.add(p);
        }

        @Override
        public String toString() {
            return "Node{" +
                    "p=" + p +
                    ", dist=" + dist +
                    ", path=" + path +
                    '}';
        }
    }

    Node getPath(char[][] matrix, Point p) {
        Queue<Node> queue = new LinkedList<>();
        queue.add(new Node(p, 0));
        Set<Point> visited = new HashSet<>();
        visited.add(p);

        while (!queue.isEmpty()) {
            var cur = queue.poll();
            if (isBike(matrix, cur.p)) return cur;
            var neighbours = getNeighbours(matrix, cur, visited);
            for (var neighbour : neighbours) {
                queue.add(neighbour);
                visited.add(neighbour.p);
            }
        }

        return new Node();
    }

    List<Node> getNeighbours(char[][] matrix, Node node, Set<Point> visited) {
        int n = matrix.length;
        int m = matrix[node.p.x].length;
        List<Node> neighbours = new ArrayList<>();
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (Math.abs(i) != Math.abs(j)) {
                    if (node.p.x + i < n && node.p.y + j < m && node.p.x + i >= 0 && node.p.y + j >= 0) {
                        Point newPoint = new Point(node.p.x + i, node.p.y + j);
                        if (visited.contains(newPoint) || isBlocked(matrix, newPoint)) continue;
                        Node newNode = new Node(newPoint, node.path, node.dist + 1);
                        neighbours.add(newNode);
                    }
                }
            }
        }

        return neighbours;
    }

    boolean isBike(char[][] matrix, Point p) {
        return matrix[p.x][p.y] == 'B';
    }

    boolean isBlocked(char[][] matrix, Point p) {
        return matrix[p.x][p.y] == '#';
    }
}
