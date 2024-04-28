#pragma once
#include "../header.h"
#define INF 99999
#define V 4

class FloydWarshal {
   public:
    static void test() {
        FloydWarshal obj;
        int graph[V][V] = {
            {0, 5, INF, 10},
            {INF, 0, 3, INF},
            {INF, INF, 0, 1},
            {INF, INF, INF, 0}};

        // Print the solution
        obj.floydWarshall(graph);
    }

    void floydWarshall(int graph[][V]) {
        int dist[V][V];
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = graph[i][j];
            }
        }

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        printSolution(dist);
    }

    void printSolution(int dist[][V]) {
        cout << "The following matrix shows the shortest distances"
                " between every pair of vertices \n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF)
                    cout << "INF" << "     ";
                else
                    cout << dist[i][j] << "     ";
            }
            cout << endl;
        }
    }
};