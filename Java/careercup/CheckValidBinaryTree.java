package programs.careercup;

import java.util.*;

/*
https://www.careercup.com/question?id=5724387312402432

Write a program to check whether it is a valid binary tree or not. Check all test cases (e.g. No left Node case).
 */

public class CheckValidBinaryTree {
    class Graph {
        Set<String> vertices = new HashSet<>();
        Map<String, Set<String>> edges = new HashMap<>();

        void add(String src) {
            vertices.add(src);
        }
        void addEdge(String src, String dst) {
            vertices.add(src);
            vertices.add(dst);

            if(!edges.containsKey(src)) edges.put(src, new HashSet<>());
            edges.get(src).add(dst);
        }

        void bfs(String src) {
            Set<String> visited = new HashSet<>();
            Queue<String> q = new LinkedList<>();
            q.add(src);
            visited.add(src);

            List<String> result = new ArrayList<>();
            while(!q.isEmpty()) {
                String u = q.poll();
                result.add(u);

                for(var v : edges.get(u)) {
                    if(!visited.contains(v)) {
                        q.add(v);
                        visited.add(v);
                    }
                }
            }

            System.out.println(String.join(",", result));
        }
    }

    public static void test() {
        CheckValidBinaryTree obj = new CheckValidBinaryTree();
        obj.testGraph1();
    }

    /*
               0
          1           2
        3   4       5   6
     */
    public void testGraph1() {
        Graph g = new Graph();
        g.addEdge("0", "1");
        g.addEdge("0", "2");
        g.addEdge("1", "0");
        g.addEdge("1", "3");
        g.addEdge("1", "4");
        g.addEdge("2", "0");
        g.addEdge("2", "5");
        g.addEdge("2", "6");
        g.addEdge("3", "1");
        g.addEdge("4", "1");
        g.addEdge("5", "2");
        g.addEdge("6", "2");

        boolean result = this.isValidBinaryTree(g);
        System.out.println("Is Valid Binary Tree: " + result);
    }

    private boolean isValidBinaryTree(Graph g) {
        Set<String> visited = new HashSet<>();
        String parent = null;
        String src = "0";
        boolean result =  isACyclicAndHasTwoChildren(g, src, parent, visited);
        if(!result) return false;

        return visited.size() == g.vertices.size();
    }

    private boolean isACyclicAndHasTwoChildren(Graph g, String src, String parent, Set<String> visited) {
        visited.add(src);

        if(g.edges.get(src).size() > 3) return false;
        if(g.edges.get(src).size() > 2 && !g.edges.get(src).contains(parent)) return false;
        for(var v : g.edges.get(src)) {
            if(v != parent && visited.contains(v)) return false;
            if(!visited.contains(v) && !isACyclicAndHasTwoChildren(g, v, src, visited)) return false;
        }

        return true;
    }

    public void testGraph() {
        Graph g = new Graph();
        g.addEdge("0", "1");
        g.addEdge("0", "3");
        g.addEdge("1", "0");
        g.addEdge("1", "2");
        g.addEdge("2", "1");
        g.addEdge("2", "3");
        g.addEdge("3", "0");
        g.addEdge("3", "2");
        g.addEdge("0", "2");
        g.addEdge("2", "0");

        g.bfs("0");
    }
}
