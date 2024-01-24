package programs.graph;

import java.util.HashSet;
import java.util.Set;

/*
Given a Start Node and an End Node in a graph report if they are “necessarily connected”.
This means that all paths from the start node lead to the end node.
Report true all paths from start node lead to end node and false if at least one path does not lead to the end node.
This is a directed graph which can have cycles

Does anyone know how to solve this? I had it in my interview at Google in CA and I still cant solve it

def helper(adj, visited, start, end):
	if start == end:
		return True
	if len(adj[start])==0:
		return False
	visited[start] = True
	return all([helper(adj, visited, child, end) for child in adj[start] if not visited[child]])

def allPathsConnect(adj, start, end):
	v = {node:False for node in adj}
	return helper(adj, v, start, end)
 */
public class CheckGraphConnectivity {
    public static void test() {
        test1();
        test2();
    }

    private static void test1() {
        CheckGraphConnectivity obj = new CheckGraphConnectivity();
        Graph<String> g = new Graph();
        g.add("a");
        g.add("b");
        g.add("c");
        g.add("d");
        g.add("e");

        g.addEdge("a", "b");
        g.addEdge("a", "c");
        g.addEdge("b", "d");
        g.addEdge("d", "e");

        System.out.println("Graph:" + g);
        var res = obj.isConnected(g, "a", "e");
        System.out.println("IsConnected : " + res);
    }

    private static void test2() {
        CheckGraphConnectivity obj = new CheckGraphConnectivity();
        Graph<String> g = new Graph();
        g.add("a");
        g.add("b");
        g.add("c");
        g.add("d");
        g.add("e");
        g.add("f");
        g.add("g");

        g.addEdge("a", "b");
        g.addEdge("a", "c");
        g.addEdge("b", "d");
        // g.addEdge("c", "d");
        g.addEdge("c", "g");
        g.addEdge("d", "e");
        g.addEdge("d", "f");
        g.addEdge("e", "g");
        g.addEdge("f", "g");

        System.out.println("Graph:" + g);
        var res = obj.isConnected(g, "a", "g");
        System.out.println("IsConnected : " + res);
    }

    private boolean isConnected(Graph<String> g, String src, String dst) {
        Set<String> visited = new HashSet<>();
        return dfs(g, src, dst, visited);
    }

    private boolean dfs(Graph<String> g, String src, String dst, Set<String> visited) {
        if (src.equals(dst))
            return true;
        visited.add(src);
        if (g.getAdjList(src).isEmpty())
            return false;
        boolean res = true;
        for (String node : g.getAdjList(src)) {
            if (!visited.contains(node)) {
                res = res && dfs(g, node, dst, visited);
            }
        }
        return res;
    }
}
