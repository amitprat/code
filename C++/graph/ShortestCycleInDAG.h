#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <functional>
#include <future>
#include <sstream>
#include <cassert>
using namespace std;

struct Node
{
    string label;
    unordered_set<Node*> children;
    Node(string label) : label(label) {}
    bool add(Node* other) {
        auto res = children.insert(other);
        return res.second;
    }

    string to_string() {
        stringstream ss;
        ss << "{";
        ss << label;
        ss << ":";
        ss << "{";
        for (auto n : children) {
            ss << n->label << ", ";
        }
        ss << "}";
        ss << "}";

        return ss.str();
    }
};

class Graph
{
private:
    Node* root = nullptr;
    unordered_map<string, Node*> map;

public:
    bool add(string source, string destination) {
        if (!root) {
            root = new Node(source);
            map[source] = root;
        }

        if (map.find(source) == map.end()) return false;
        Node* sourceNode = map[source];
        Node* destnationNode = map.find(destination) != map.end() ? map[destination] : new Node(destination);

        map[destination] = destnationNode;
        return sourceNode->add(destnationNode);
    }

    string to_string() {
        stringstream ss;
        queue<Node*> q;
        q.push(root);
        unordered_set<Node*> visited;
        visited.insert(root);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            ss << cur->to_string() << ", ";

            for (auto n : cur->children) {
                if (visited.find(n) == visited.end()) {
                    visited.insert(n);
                    q.push(n);
                }
            }
        }

        return ss.str();
    }

    vector<Node*> shortestCycle(string source) {
        vector<Node*> result;
        unordered_map<Node*, Node*> parents;
        queue<Node*> q;
        Node* sourceNode = map[source];

        q.push(sourceNode);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            for (auto ch : cur->children) {
                if (parents.find(ch) == parents.end()) {
                    parents[ch] = cur;
                    q.push(ch);
                }
            }
        }

        Node* cur = map[source];
        do {
            result.push_back(cur);
            cur = parents[cur];
        } while (cur != nullptr && cur != sourceNode);
        if (cur != nullptr) result.push_back(cur);
        if (result.size() == 1) result.clear();

        return result;
    }
};

class ShortestCycleInDAG
{
public:
    static void test()
    {
        Graph g;
        assert(g.add("1", "2"));
        assert(g.add("1", "3"));
        assert(g.add("2", "4"));
        assert(g.add("3", "5"));
        assert(g.add("4", "5"));
        assert(g.add("4", "6"));
        assert(g.add("5", "1"));

        cout << g.to_string() << endl;

        vector<Node*> paths = g.shortestCycle("3");
        for (auto path : paths) {
            cout << path->label << ", ";
        }
        cout << endl;
    }
};