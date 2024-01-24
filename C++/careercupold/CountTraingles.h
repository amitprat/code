#pragma once
#include "../Header.h"

/*
Given a undirected graph with corresponding edges. Find the number of possible triangles?
Example:
0 1
2 1
0 2
4 1

Answer:
1
https://www.careercup.com/question?id=5988741646647296
*/

class CountTraingles {
    class Graph {
        unordered_map<int, unordered_set<int>> vertices;
    public:
        void add(int src, int dst) {
            vertices[src].insert(dst);
            vertices[dst].insert(src);
        }
        bool contains(int u, int v) {
            auto cur = vertices[u];
            return cur.find(v) != cur.end();
        }
        unordered_map<int, unordered_set<int>> getVertices() {
            return vertices;
        }
    };
    class Graph1 {
    public:
        struct Node {
            int src;
            unordered_map<int, Node*> neighbours;
            Node(int src) :src(src) {}
            void addEdge(int dst, Node* dstNode) {
                neighbours.insert({ dst,dstNode });
            }
            bool contains(int v) {
                return neighbours.find(v) != neighbours.end();
            }
        };
        unordered_map<int, Node*> vertices;
        void add(int u, int v) {
            if (vertices.find(u) == vertices.end()) vertices.insert({ u, new Node(u) });
            if (vertices.find(v) == vertices.end()) vertices.insert({ v, new Node(v) });
            vertices[u]->addEdge(v, vertices[v]);
            vertices[v]->addEdge(u, vertices[u]);
        }
        bool contains(int v) {
            return vertices.find(v) != vertices.end();
        }
    };
public:
    static void test() {
        CountTraingles obj;
        Graph1 g;
        g.add(1, 2);
        g.add(2, 3);
        g.add(3, 4);
        g.add(4, 1);
        g.add(1, 3);
        g.add(2, 4);
        auto res = obj.count(g);
        cout << "Traingles Count = " << res << endl;
    }

    int count(Graph1 g) {
        int traingles = 0;
        for (auto u : g.vertices) {
            for (auto v : u.second->neighbours) {
                for (auto w : u.second->neighbours) {
                    if (v.first != w.first && v.second->contains(w.first)) {
                        traingles++;
                    }
                }
            }
        }
        return traingles / 6;
    }
};

/*
I can think of two approaches:

First approach - A naive approach using an adjacency map

The adjacency map is a Map whose keys are vertices and whose values are sets of vertices which are all the neighbors of the key vertex. For every vertex, we'll check for every pair of its neighbors whether there is an edge between them and increment the triangle counter if so.

The total number of triangles will be the number of triangles we counted divided by 6 (we count each triangle 6 times).

Code:


private static class Edge {
        private final Object from;
        private final Object to;

        public Edge(Object from, Object to){
            this.from = from;
            this.to = to;
        }

        public Object getFrom(){return from;}
        public Object getTo(){return to;}

        @Override
        public String toString(){
            return "(" + ((from!=null) ? from.toString() : null) + "," + ((to!=null) ? to.toString() : null) + ")";
        }
    }

    public static Map<Object,Set<Object>> buildAdjacencyMap(List<Edge> edges){
        if ((edges==null) || (edges.isEmpty())){
            return Collections.<Object,Set<Object>>emptyMap();
        }

        Map<Object,Set<Object>> graph = new HashMap<>();
        for (Edge e : edges){
            if (!graph.containsKey(e.getFrom())){
                graph.put(e.getFrom(), new HashSet<Object>());
            }
            if (!graph.containsKey(e.getTo())){
                graph.put(e.getTo(), new HashSet<Object>());
            }
            graph.get(e.getFrom()).add(e.getTo());
            graph.get(e.getTo()).add(e.getFrom());
        }

        return graph;
    }

    public static int getNumberOfTriangles1(List<Edge> edges){
        Map<Object,Set<Object>> graph = buildAdjacencyMap(edges);

        int triangles = 0;
        for (Set<Object> neighbors : graph.values()){
            for (Object v2 : neighbors){
                for (Object v3 : neighbors){
                    if ((!v2.equals(v3)) && (graph.get(v2).contains(v3))){
                        triangles++;
                    }
                }
            }
        }

        return (triangles/6);
    }
Complexity: The overall run-time complexity is O(n*d^2) where n is the number of vertices and d is the maximum degree of a vertex in the graph. This is a good approach for graphs with small maximum vertex degree. But if the graph contains a vertex whose degree is O(n) then the overall complexity in this case would be O(n^3).



Second approach - Using matrix multiplication

Suppose A is the graph's adjacency matrix (A[i][j] = 1 if and only if there is an edge between i and j in the graph). It can be shown that trace(A^3)/6 is the number of triangles in the graph (using the fact that A^k[i][j] is the number of paths with k edges from i to j). This means that all we need to know the number of triangles is to calculate the matrix A^3 and its trace.

This means that our algorithm complexity would depend on the complexity of the matrix multiplication algorithm:
Naive: O(n^3)
Strassen: O(n^{2.8074})
Coppersmith-Winograd: O(n^{2.3729})

I can post a code for this approach using Strassen matrix multiplication but it's rather long and isn't pretty.
*/