#include "../header.h"

class AllPairShortestPath {
   public:
    static void test() {
        /* Let us create the following weighted graph
            10
        (0)------->(3)
        |          /|\
        5     |     |
            |     | 1
        \|/     |
        (1)------->(2)
                3
        */

        vector<vector<int>> matrix = {
            {0, 5, INT_MAX, 10},
            {INT_MAX, 0, 3, INT_MAX},
            {INT_MAX, INT_MAX, 0, 1},
            {INT_MAX, INT_MAX, INT_MAX, 0}};

        AllPairShortestPath obj;
        obj.floydWarshalPath(matrix, 2, 3);

        // int V = matrix.size();
        // for (int i = 0; i < V; i++)
        // {
        //     for (int j = 0; j < V; j++)
        //     {
        //         if (matrix[i][j] != INT_MAX)
        //         {
        //             cout << "Distance from " << i << " -> " << j << " : " << matrix[i][j] << endl;
        //         }
        //     }
        // }
    }

   private:
    void floydWarshal(vector<vector<int>> &matrix) {
        int V = matrix.size();

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX && matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }
    }

    void floydWarshalPath(vector<vector<int>> &matrix, int src, int dst) {
        vector<vector<int>> dist(matrix.size(), vector<int>(matrix.size()));
        vector<vector<int>> path(matrix.size(), vector<int>(matrix.size()));

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                dist[i][j] = matrix[i][j];
                if (dist[i][j] == INT_MAX)
                    path[i][j] = -1;
                else
                    path[i][j] = j;
            }
        }

        this->floydWarshalPath(dist, path);

        vector<int> shortestPath = {src};
        int k = src;
        int j = dst;
        while (k != j) {
            k = path[k][j];
            shortestPath.push_back(k);
        }

        cout << "Shorted path between " << src << "->" << dst << " = " << shortestPath << endl;
    }

    void floydWarshalPath(vector<vector<int>> &dist, vector<vector<int>> &path) {
        int V = dist.size();

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = path[i][k];
                    }
                }
            }
        }
    }
};