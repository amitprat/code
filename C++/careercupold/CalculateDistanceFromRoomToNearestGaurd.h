#include "../Header.h"

/*
Given a 2-D matrix represents the room, obstacle and guard like the following (0 is room, B->obstacle, G-> Guard):
0 0 0
B G G
B 0 0

calculate the steps from a room to nearest Guard and set the matrix, like this
2 1 1
B G G
B 1 1
Write the algorithm, with optimal solution.
*/

/*
Typed it in directly... so expect bugs (or plain incorrectness :P )
BFS initiated from all guard positions and +1 for reaching a naked position (a '0') and add it to queue to keep the BFS search going.
*/
// Assuming N x N matrix and directions are up/down/left/right

#define IN_BOUNDARY(a, b) ((a) >= 0 && (a) < N && (b) >= 0 && (b) < N)
struct Pos
{
    int x, y;
}; // struct for a "position" of a node (indices)

void findDist(vector<vector<char>> A, int N)
{
    queue<Pos> Q;

    vector<vector<int>> dist(N, vector<int>(N, INT_MAX));

    // find and enqueue guard positions
    Pos temp;
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (A[i][j] == 'G')
            {
                temp.x = i;
                temp.y = j;
                Q.push(temp); // putting guard position in Q
                dist[i][j] = 0;
            }
        }
    }

    // BFS
    while (!Q.empty())
    {
        temp = Q.front();
        Q.pop();
        i = temp.x;
        j = temp.y;

        for (int u = -1; u <= 1; u++)
        {
            for (int v = -1; v <= 1; v++)
            {
                if ((!u || !v) && IN_BOUNDARY(i + u, j + v) && A[i + u][j + v] == '0')
                {
                    // should reach here for only/all valid neighbours
                    dist[i + u][j + v] = dist[i][j] + 1; // distance to neighbour is 1 more

                    temp.x = i + u;
                    temp.y = j + v;
                    Q.push(temp); // push neighbour onto queue
                }
            }
        }
    }
}