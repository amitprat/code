#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5713002834165760
Given a Start Node and an End Node in a graph report if they are “necessarily connected”. This means that all paths from the start
node lead to the end node. Report true all paths from start node lead to end node and false if at least one path does not lead to
the end node. This is a directed graph which can have cycles.

You need to find a path from start that does not end in the end node. You can brute force all paths for from start.
You can optimize if you store for a given node if it has a path to end so you do not redo the same work over and over.
Recursive solution should be straight forward.
*/

class NecessarilyConnectedDirectedGraph
{
	class Graph {
		unordered_map<int, vector<int>> vertices;
	public:
		void add(int u, int v) {
			vertices[u].push_back(v);
		}

		string to_string()
		{
			stringstream ss;
			for (auto e : vertices)
			{
				ss << "{" << e.first << ":";
				ss << "{";
				for (auto u : e.second) ss << u << ",";
				ss << "}";
				ss << "}";
				ss << endl;
			}

			return ss.str();
		}

		vector<int> getNeighbours(int u) {
			return vertices[u];
		}
	};
public:
	static void test() {
		NecessarilyConnectedDirectedGraph obj;
		Graph g;
		g.add(0, 1);
		g.add(0, 2);
		g.add(1, 4);
		g.add(2, 4);
		g.add(2, 3);
		g.add(3, 5);
		g.add(4, 6);
		//g.add(5, 6);

		cout << "Input graph: " << endl;
		cout << g.to_string() << endl;

		unordered_set<int> visited;
		unordered_set<int> recStack;

		int src = 0, dst = 6;
		bool res = obj.isNecessarilyConnected(g, src, dst, visited, recStack);
		cout << format("Are all paths from source={} to destination={} are connected={}", src, dst, res) << endl;
	}

	bool isNecessarilyConnected(Graph g, int s, int e, unordered_set<int>& visited, unordered_set<int> recStack)
	{
		if (s == e) return true;
		visited.insert(s);
		recStack.insert(s);

		auto neighbours = getNeighbours(g, s);
		if (neighbours.empty()) return false;

		for (auto v : neighbours) {
			if (visited.find(v) == visited.end()) {
				if (!isNecessarilyConnected(g, v, e, visited, recStack)) return false;
			}
			else if (recStack.find(v) != recStack.end()) return false;
		}

		return true;
	}

	vector<int> getNeighbours(Graph g, int u)
	{
		return g.getNeighbours(u);
	}
};