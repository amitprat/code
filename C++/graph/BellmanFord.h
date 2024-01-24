#pragma once
#include "../header.h"

class BellmanFord {
private:
    template <class T>
    class Edge {
    public:
        T src, dst;
        int wt;
        Edge(T src, T dst, int wt) :src(src), dst(dst), wt(wt) {}
        string to_string() {
            stringstream ss;
            ss << "{";
            ss << setw(2) << src;
            ss << "->";
            ss << setw(2) << dst;
            ss << ":";
            ss << setw(2) << wt;
            ss << "}";
            return ss.str();
        }
    };

    template <class T>
    class Graph {
    public:
        int V;
        vector<Edge<T>*> edges;

        Graph(int v) :V(v) {}
        void addEdge(T src, T dst, int wt) {
            edges.push_back(new Edge(src, dst, wt));
        }
        string to_string() {
            stringstream ss;
            ss << "{\n";
            for (auto edge : edges) ss << "  " << edge->to_string() << "\n";
            ss << "}\n";
            return ss.str();
        }
    };
public:
    static void test() {
        Graph<int> graph(5);
        graph.addEdge(0, 1, -1);
        graph.addEdge(0, 2, 4);
        graph.addEdge(1, 2, 3);
        graph.addEdge(1, 3, 2);
        graph.addEdge(1, 4, 2);
        graph.addEdge(3, 2, 5);
        graph.addEdge(3, 1, 1);
        graph.addEdge(4, 3, -3);

        cout << "Graph state: " << endl;
        cout << graph.to_string() << endl;

        BellmanFord obj;
        auto dist = obj.bellman(graph);

        cout << "Distance from source:" << endl;
        for (int i = 0; i < dist.size(); i++) {
            cout << "0" << " -> " << i << " = " << setw(2) << dist[i] << endl;
        }
    }

    vector<int> bellman(Graph<int> g) {
        vector<int> dist(g.V, INT_MAX);
        dist[0] = 0;

        for (int i = 0; i < g.V - 1; i++) {
            for (auto edge : g.edges) {
                if (dist[edge->src] != INT_MAX && dist[edge->dst] > dist[edge->src] + edge->wt) {
                    dist[edge->dst] = dist[edge->src] + edge->wt;
                }
            }
        }

        for (auto edge : g.edges) {
            if (dist[edge->src] != INT_MAX && dist[edge->dst] > dist[edge->src] + edge->wt) {
                throw exception("Graph contains negative cycle");
            }
        }

        return dist;
    }
};