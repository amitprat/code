#pragma once
#include "../header.h"

namespace graph2 {
    template <class T>
    class Edge {
    public:
        T id;
        string edgeCharacteristic;
        int dist;

        Edge(T id, string edgeCharacteristic, int dist) : id(id), edgeCharacteristic(edgeCharacteristic), dist(dist) {}
    };

    template <class T, class V>
    class GraphNode {
    public:
        T id;
        V val;
        list<Edge<T>> adjList;

        GraphNode() {}
        GraphNode(T id, V val) : id(id), val(val) {}
        void add(T dstId, string characteristic, int dist) {
            adjList.push_back({ dstId,characteristic,dist });
        }

        string to_string() {
            stringstream ss;
            ss << "{";
            ss << id << ",";
            ss << val.to_string() << ",";
            for (auto& node : adjList) {
                ss << "{";
                ss << node.id << ",";
                ss << "}";
            }
            ss << "}";
            return ss.str();
        }

        string to_string_concise() {
            stringstream ss;
            ss << "{";
            ss << id << ",";
            for (auto& node : adjList) {
                ss << "{";
                ss << node.id << ",";
                ss << "}";
            }
            ss << "}";
            return ss.str();
        }
    };

    template <class T, class V>
    class Graph
    {
    private:
        unordered_map<string, GraphNode<T, V>> nodes;
        string ch;

    public:
        Graph() {}
        Graph(string ch) : ch(ch) {}
        void addNode(T nodeId, V val) {
            auto node = GraphNode<T, V>(nodeId, val);
            nodes.insert({ nodeId, node });
        }

        void addChild(string srcId, string dstId, int dist) {
            if (nodes.find(srcId) == nodes.end()) { throw exception("Src Not not found!"); }
            if (nodes.find(dstId) == nodes.end()) { throw exception("Dst Not not found!"); }
            nodes[srcId].add(dstId, ch, dist);
        }

        string to_string() {
            stringstream ss;
            ss << "{";
            for (auto& node : nodes) {
                ss << node.second.to_string();
            }
            ss << "}";
            return ss.str();
        }

        string to_string_concise() {
            stringstream ss;
            ss << "{";
            for (auto& node : nodes) {
                ss << node.second.to_string_concise();
            }
            ss << "}";
            return ss.str();
        }
    };

    class Student {
    public:
        string name;
        int age;
        string course;
        Student() {}
        Student(string name, int age, string course) :name(name), age(age), course(course) {}

        string to_string() {
            stringstream ss;
            ss << "{";
            ss << name << ", " << age << ", " << course;
            ss << "}";
            return ss.str();
        }
    };

    class Graph2 {
    public:
        static void test() {
            Graph<string, Student> graph("friend");
            GraphNode<string, Student> node1("node1", Student("Amit", 25, "Computer"));
            GraphNode<string, Student> node2("node2", Student("Kapil", 26, "Computer"));
            graph.addNode(node1.id, node1.val);
            graph.addNode(node2.id, node2.val);
            graph.addChild(node1.id, node2.id, 1);
            cout << graph.to_string_concise() << endl;
        }
    };
}