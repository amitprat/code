package programs.graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Graph<T> {
    private final Map<T, Node<T>> map = new HashMap<>();

    public void add(T vertex) {
        var node = new Node<>(vertex);
        map.put(vertex, node);
    }

    public void addEdge(T src, T dest) {
        var srcNode = map.get(src);
        var dstNode = map.get(dest);

        srcNode.addAdjListItem(dstNode);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        for (var entry : map.entrySet()) {
            sb.append(entry.getValue());
            sb.append("\n");
        }
        sb.append("}");
        return sb.toString();
    }

    public List<T> getAdjList(T src) {
        var node = map.get(src);
        return node.adjList.stream().map(s -> s.label).collect(Collectors.toList());
    }

    public List<T> getVertices() {
        return map.entrySet().stream().map(p -> p.getKey()).collect(Collectors.toList());
    }

    private class Node<T> {
        T label;
        List<Node<T>> adjList;

        Node(T label) {
            this.label = label;
            this.adjList = new ArrayList<>();
        }

        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("{");
            sb.append(label);
            if (!adjList.isEmpty()) {
                sb.append(",{");
                for (var node : adjList) {
                    sb.append(node.label + ",");
                }
                sb.append("}");
            }
            sb.append("}");
            return sb.toString();
        }

        void addAdjListItem(Node<T> neighbour) {
            adjList.add(neighbour);
        }
    }
}
