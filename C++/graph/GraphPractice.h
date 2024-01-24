#include "../header.h"

class GraphPractice {
private:
    unordered_map<string, list<string>> adjList;

public:
    GraphPractice() = default;
    void addVertex(string u) {
        if (adjList.find(u) != adjList.end()) throw exception("Already exists!");
        adjList[u] = {};
    }

    void addEdge(string u, string v) {
        if (adjList.find(u) == adjList.end() ||
            adjList.find(v) == adjList.end()) throw exception("Vertex not exists!");
        adjList[u].push_back(v);
    }

    string to_string() {
        stringstream ss;
        for (auto& entry : adjList) {
            ss << "[" << entry.first << ":";
            for (auto& item : entry.second) {
                ss << item << ",";
            }
            ss << "]" << endl;
        }

        return ss.str();
    }
};

class GraphPracticeTest {
public:
    static void test() {
        GraphPractice graph;
        graph.addVertex("a");
        graph.addVertex("b");
        graph.addVertex("c");
        graph.addVertex("d");
        graph.addEdge("a", "d");
        graph.addEdge("b", "c");
        cout << graph.to_string() << endl;
    }
};