package programs.graph;

import java.util.*;

public class StronglyConnectedComponentsForDirectedGraph {
    public static void test() {
        StronglyConnectedComponentsForDirectedGraph obj = new StronglyConnectedComponentsForDirectedGraph();
        Graph<Integer> graph = new Graph<Integer>();
        graph.add(0);
        graph.add(1);
        graph.add(2);
        graph.add(3);
        graph.add(4);

        graph.addEdge(1, 0);
        graph.addEdge(0, 2);
        graph.addEdge(2, 1);
        graph.addEdge(0, 3);
        graph.addEdge(3, 4);

        System.out.println("Graph: " + graph);
        var count = obj.printStronglyConnectedComponents(graph);
        System.out.println("Number of strongly connected components = " + count);
    }

    private int printStronglyConnectedComponents(Graph<Integer> graph) {
        Stack<Integer> st = new Stack<>();
        Set<Integer> visited = new HashSet<>();

        for (var vertex : graph.getVertices()) {
            if (!visited.contains(vertex)) {
                fillOrder(graph, vertex, st, visited);
            }
        }

        Graph<Integer> grTranspose = createTranspose(graph);

        int count = 0;
        visited.clear();
        while (!st.empty()) {
            if (!visited.contains(st.peek())) {
                List<Integer> component = new ArrayList<>();
                dfs(grTranspose, st.peek(), visited, component);
                System.out.println(component);

                count++;
            }
            st.pop();
        }
        return count;
    }

    private void dfs(Graph<Integer> grTranspose, Integer vertex, Set<Integer> visited, List<Integer> component) {
        visited.add(vertex);
        component.add(vertex);
        for (var neighbour : grTranspose.getAdjList(vertex)) {
            if (!visited.contains(neighbour)) {
                dfs(grTranspose, neighbour, visited, component);
            }
        }
    }

    private Graph<Integer> createTranspose(Graph<Integer> graph) {
        Graph<Integer> grTranspose = new Graph<>();
        for (var vertex : graph.getVertices()) {
            grTranspose.add(vertex);
            for (var neighbour : graph.getAdjList(vertex)) {
                grTranspose.add(neighbour);
                grTranspose.addEdge(neighbour, vertex);
            }
        }
        return grTranspose;
    }

    void fillOrder(Graph<Integer> graph, Integer vertex, Stack<Integer> stack, Set<Integer> visited) {
        visited.add(vertex);

        for (var neighbour : graph.getAdjList(vertex)) {
            if (!visited.contains(neighbour)) {
                fillOrder(graph, neighbour, stack, visited);
            }
        }
        stack.add(vertex);
    }
}
