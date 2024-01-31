#pragma once
#include "../header.h"

class Graph {
    unordered_set<int> vertices;
    unordered_map<int, unordered_set<int>> adjMap;
    bool isDirected = false;

   public:
    Graph(bool isDirected = false) : isDirected(false) {}

    void addVertex(int vertex) {
        vertices.insert(vertex);
    }

    void addEdge(int src, int dst) {
        if (vertices.find(src) == vertices.end()) throw exception("src vertex not found.");
        if (vertices.find(dst) == vertices.end()) throw exception("dst vertex not found.");

        adjMap[src].insert(dst);
        if (!isDirected) adjMap[dst].insert(src);
    }

    unordered_set<int> adjVertices(int src) {
        return adjMap[src];
    }

    unordered_map<int, unordered_set<int>> getAdjMap() {
        return adjMap;
    }

    unordered_set<int> getVertices() {
        return vertices;
    }

    int size() {
        return vertices.size();
    }

    string to_string() {
        stringstream ss;
        for (auto &edge : adjMap) {
            ss << edge.first << ":-> ";
            ss << ::to_string(edge.second);

            ss << endl;
        }

        return ss.str();
    }
};