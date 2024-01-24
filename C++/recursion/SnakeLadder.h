#pragma once
#include "../Header.h"

class SnakeLadder {
    class Node {
    public:
        int v;
        int dist;
        vector<int> path;
        Node(int v, int dist) :v(v), dist(dist) {
            path.push_back(v);
        }
        Node(int v, int dist, vector<int> oldPath) :v(v), dist(dist) {
            path.insert(path.begin(), oldPath.begin(), oldPath.end());
            path.push_back(v);
        }
    };
public:
    static void test() {
        SnakeLadder obj;
        int N = 30;
        vector<int> moves(N);
        for (int i = 0; i < N; i++)
            moves[i] = -1;

        // Ladders 
        moves[2] = 21;
        moves[4] = 7;
        moves[10] = 25;
        moves[19] = 28;

        // Snakes 
        moves[26] = 0;
        moves[20] = 8;
        moves[16] = 3;
        moves[18] = 6;

        cout << "Min Dice throws required is " << obj.getMinDiceThrows(moves);
    }

    int getMinDiceThrows(vector<int> moves) {
        unordered_set<int> visited;
        queue<Node> q;
        q.push({ 0,0 });
        visited.insert(0);

        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (u.v == moves.size() - 1) {
                cout << to_string(u.path) << endl;
                return u.dist;
            }
            if (moves[u.v] != -1) { q.push({ moves[u.v],u.dist,u.path }); continue; }
            for (auto dice = 1; u.v + dice < moves.size() && dice <= 6; dice++) {
                auto v = u.v + dice;
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    q.push({ v, u.dist + 1,u.path });
                }
            }
        }
        return -1;
    }
};