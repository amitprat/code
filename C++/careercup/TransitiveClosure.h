#include "../header.h"

class TransitiveClosure
{
public:
    static void test()
    {
        /* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)
            3           */

        vector<vector<int>> graph = {
            {1, 1, 0, 1},
            {0, 1, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 1}};

        // Print the solution
        TransitiveClosure obj;
        // obj.transitiveClosure(graph);
        // cout << endl;
        obj.transitiveClosureUsingDfs(graph);
        cout << endl;
    }

    void transitiveClosure(vector<vector<int>> &graph)
    {
        vector<vector<int>> reach(graph.size(), vector<int>(graph.size()));
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph[i].size(); j++)
            {
                reach[i][j] = graph[i][j];
            }
        }

        for (int k = 0; k < graph.size(); k++)
        {
            for (int i = 0; i < graph.size(); i++)
            {
                for (int j = 0; j < graph.size(); j++)
                {
                    reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
                }
            }
        }

        for (int i = 0; i < reach.size(); i++)
        {
            for (int j = 0; j < reach[i].size(); j++)
            {
                cout << reach[i][j] << " ";
            }
            cout << endl;
        }
    }

    void transitiveClosureUsingDfs(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<vector<bool>> reach(n, vector<bool>(n, false));

        for (int u = 0; u < n; u++)
        {
            dfs(graph, u, u, reach);
        }

        for (int i = 0; i < reach.size(); i++)
        {
            for (int j = 0; j < reach[i].size(); j++)
            {
                cout << reach[i][j] << " ";
            }
            cout << endl;
        }
    }

    void dfs(vector<vector<int>> &graph, int u, int v, vector<vector<bool>> &reach)
    {
        reach[u][v] = true;

        for (auto &next : graph[u])
        {
            if (graph[u][next] && !reach[u][next])
                dfs(graph, u, next, reach);
        }
    }
};