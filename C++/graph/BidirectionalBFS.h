#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include "Graph.h"
using namespace std;

class BidirectionalBFS
{
public:
    static void test() {
        BidirectionalBFS obj;
        Graph<int> graph;
        graph.add(1);
        graph.add(2);
        graph.add(3);
        graph.add(4);
        graph.add(5);
        graph.add(6);

        graph.addEdge(1, 2); graph.addEdge(2, 1);
        graph.addEdge(3, 2); graph.addEdge(2, 3);
        graph.addEdge(2, 4); graph.addEdge(4, 2);
        graph.addEdge(5, 4); graph.addEdge(4, 5);
        graph.addEdge(6, 4); graph.addEdge(4, 6);

        cout << graph.str();

        int begin = 1;
        int end = 5;
        cout << obj.find(graph, begin, end) << endl;
    }

    bool find(Graph<int>& g, int begin, int end) {
        unordered_set<int> s_left, s_right;
        queue<int> q_left, q_right;
        vector<int> p_left(g.size() + 1), p_right(g.size() + 1);
        p_left[begin] = -1;
        p_right[end] = -1;
        s_left.insert(begin);
        s_right.insert(end);
        q_left.push(begin);
        q_right.push(end);

        while (!q_left.empty() && !q_right.empty()) {
            bfs(g, q_left, s_left, p_left);
            bfs(g, q_right, s_right, p_right);
            auto intersect = isIntersect(g, s_left, s_right);
            if (intersect != -1) {
                cout << "Path exist between " << begin << " and " << end << "\n";
                cout << "Intersection at: " << intersect << "\n";

                // print the path and exit the program
                printPath(p_left, p_right, begin, end, intersect);
                exit(0);
            }
        }
    }

    void bfs(Graph<int>& g, queue<int> q, unordered_set<int>& s, vector<int>& p)
    {
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            for (auto& neighbour : g.getNeighbours(cur)) {
                if (s.find(neighbour) == s.end()) {
                    s.insert(neighbour);
                    p[neighbour] = cur;
                    q.push(neighbour);
                }
            }
        }
    }

    int isIntersect(Graph<int>& g, unordered_set<int>& left, unordered_set<int>& right) {
        for (int i = 1; i <= g.size(); i++) {
            if (left.find(i) != left.end() && right.find(i) != right.end()) return i;
        }
        return -1;
    }

    void printPath(vector<int>& p_left, vector<int>& p_right, int begin, int end, int intersect)
    {
        vector<int> left;
        int tmp = intersect;
        while (tmp != -1) {
            left.push_back(tmp);
            tmp = p_left[tmp];
        }
        reverse(left.begin(), left.end());

        tmp = p_right[intersect];
        while (tmp != -1) {
            left.push_back(tmp);
            tmp = p_right[tmp];
        }
        for (auto& i : left) {
            cout << i << " ";
        }
        cout << endl;
    }
};