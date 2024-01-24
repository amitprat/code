#pragma once
#include "../Header.h"

class DijkastraMatrix {
private:
    static const int V = 9;
public:
    static void test() {
        int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

        for (int s = 0; s < V; s++) {
            vector<int> distance = dijkastra(graph, s);

            for (int i = 0; i < V; i++) {
                cout << "Distance from " << s << " to " << i << " = " << distance[i] << endl;
            }
            cout << endl;
        }
    }

    static vector<int> dijkastra(int graph[][V], int s) {
        vector<int> distance(V, INT_MAX);
        vector<bool> visited(V, false);
        distance[s] = 0;

        for (int i = 0; i < V - 1; i++) {
            int u = minCostVertex(distance, visited);
            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (visited[v]) continue;
                if (distance[u] == INT_MAX || !graph[u][v]) continue;

                distance[v] = min(distance[v], distance[u] + graph[u][v]);
            }
        }

        return distance;
    }

    static int minCostVertex(vector<int>& distance, vector<bool>& visited) {
        int mnCostVertex = -1;
        for (int i = 0; i < V; i++) {
            if (visited[i]) continue;

            if (mnCostVertex == -1 || distance[i] < distance[mnCostVertex]) {
                mnCostVertex = i;
            }
        }

        return mnCostVertex;
    }
};