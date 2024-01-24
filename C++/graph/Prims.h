#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
using namespace std;
#define V 5

class Prims
{
public:
    void test()
    {
        int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };

        findMst(graph);
    }

    void findMst(int graph[][V])
    {
        bool mstSet[V];
        int parent[V];
        int vertexWts[V];
        for (int i = 0; i < V; i++) {
            mstSet[i] = false;
            vertexWts[i] = INT_MAX;
        }
        vertexWts[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < V; count++) {
            int minWtVertex = findMinWeightVertex(mstSet, vertexWts);
            mstSet[minWtVertex] = true;
            //cout << "minWtVertex=" << minWtVertex << endl;
            for (int j = 0; j < V; j++)
            {
                if (graph[minWtVertex][j] && !mstSet[j])
                {
                    if (vertexWts[j] > graph[minWtVertex][j]) {
                        vertexWts[j] = graph[minWtVertex][j];
                        parent[j] = minWtVertex;
                    }
                    //cout << parent[j] << "->" << j << endl;
                }
            }
        }

        printEdges(mstSet, parent, graph);
    }

private:
    int findMinWeightVertex(bool mstSet[], int vertexWts[])
    {
        int res = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < V; i++)
        {
            if (!mstSet[i] && vertexWts[i] < res) {
                res = vertexWts[i]; minIndex = i;
            }
        }

        return minIndex;
    }

    void printEdges(bool mstSet[], int parent[], int graph[][V])
    {
        cout << "{";
        for (int i = 1; i < V; i++) {
            if (mstSet[i])
            {
                cout << "(" << parent[i] << "->" << i << ":" << graph[parent[i]][i] << ")";
                cout << " ";
            }
        }
        cout << "}";
    }
};