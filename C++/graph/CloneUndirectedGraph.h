#pragma once
#include "../header.h"
#include "../design/Set.h"

class GraphNode {
public:
    int label;
    GraphNode(int label) : label(label) {}
    string to_string() {
        return std::to_string(label);
    }
};

class Graph {
private:
    unordered_map<GraphNode*, list<GraphNode*>> nodes;

public:
    void addNode(GraphNode* node) {
        nodes.insert({ node,{} });
    }
    void addChild(GraphNode* src, GraphNode* dst) {
        if (nodes.find(src) == nodes.end()) throw exception("Source Not not found!");
        if (nodes.find(dst) == nodes.end()) throw exception("Destination Not not found!");
        nodes[src].push_back(dst);
        nodes[dst].push_back(src);
    }
    void addChild_1(GraphNode* src, GraphNode* dst) {
        if (nodes.find(src) == nodes.end()) throw exception("Source Not not found!");
        if (nodes.find(dst) == nodes.end()) throw exception("Destination Not not found!");
        nodes[src].push_back(dst);
    }
    unordered_map<GraphNode*, list<GraphNode*>>& getNodes() {
        return nodes;
    }
    list<GraphNode*>& getNodes(GraphNode* node) {
        return nodes[node];
    }
    GraphNode* getNode(int label) {
        for (auto& node : nodes) {
            if (node.first->label == label) return node.first;
        }
        return nullptr;
    }
    string to_string() {
        stringstream ss;
        for (auto node : nodes) {
            ss << node.first->to_string() << ":";
            for (auto& child : node.second) {
                ss << child->to_string() << ", ";
            }
            ss << endl;
        }
        return ss.str();
    }
};
class CloneGraph {
public:
    static void test() {
        CloneGraph obj;
        Graph graph;
        graph.addNode(new GraphNode(1));
        graph.addNode(new GraphNode(2));
        graph.addNode(new GraphNode(3));
        graph.addNode(new GraphNode(4));
        graph.addNode(new GraphNode(5));
        graph.addNode(new GraphNode(6));

        graph.addChild(graph.getNode(1), graph.getNode(2));
        graph.addChild(graph.getNode(1), graph.getNode(3));
        graph.addChild(graph.getNode(2), graph.getNode(4));
        graph.addChild(graph.getNode(3), graph.getNode(4));
        graph.addChild(graph.getNode(5), graph.getNode(6));
        cout << "Graph: " << endl;
        cout << graph.to_string() << endl;
        cout << "Connected Components: " << endl;
        print(obj.connectedComponents(graph));
        cout << endl;

        cout << "Cloned Graph: " << endl;
        auto cloned = obj.clone(graph);
        cout << cloned.to_string() << endl;
        cout << "Connected Components: " << endl;
        print(obj.connectedComponents(cloned));
        cout << endl;
    }

    Graph clone(Graph& org) {
        unordered_map<GraphNode*, GraphNode*> map;
        Set<int> visited;
        Graph clonedGraph;
        for (auto& node : org.getNodes()) {
            clonedGraph.addNode(node.first);
            map[node.first] = clonedGraph.getNode(node.first->label);
        }
        for (auto& node : org.getNodes()) {
            for (auto& child : node.second) {
                clonedGraph.addChild_1(map[node.first], map[child]);
            }
        }
        return clonedGraph;
    }

    vector<vector<int>> connectedComponents(Graph& graph) {
        Set<int> visited;
        vector<vector<int>> result;
        for (auto& node : graph.getNodes()) {
            if (!visited.exists(node.first->label)) {
                vector<int> cur;
                bfs(graph, node.first->label, visited, cur);
                result.push_back(cur);
            }
        }
        return result;
    }

    void bfs(Graph& graph, int node, Set<int>& visited, vector<int>& result) {
        queue<int> q;
        q.push(node);
        visited.add(node);

        while (!q.empty()) {
            auto front = q.front(); q.pop();
            result.push_back(front);
            for (auto& child : graph.getNodes(graph.getNode(front))) {
                if (!visited.exists(child->label)) {
                    q.push(child->label);
                    visited.add(child->label);
                }
            }
        }
    }
};