#pragma once
#include "../Header.h"

class StoryTelling {
	struct Input {
		int person1;
		int person2;
		int time;
	};

	class Graph {
		unordered_set<int> vertices;
		unordered_map<int, unordered_set<int>> edges;
	public:
		void addEdge(int u, int v) {
			vertices.insert(u);
			vertices.insert(v);

			edges[u].insert(v);
			edges[v].insert(u);
		}

		vector<int> bfs(int s) {
			unordered_set<int> seen;
			vector<int> out;
			queue<int> q;

			q.push(s);
			seen.insert(s);

			while (!q.empty()) {
				auto u = q.front(); q.pop();
				out.push_back(u);

				for (auto v : edges[u]) {
					if (seen.count(v) == 0) {
						q.push(v);
						seen.insert(v);
					}
				}
			}

			return out;
		}
	};
public:
	static void test() {
		StoryTelling obj;
		vector<Input> inputs = { {1, 2, 100}, {2, 3, 100}, {4, 5, 100} };
		int s = 2;

		vector<int> res = obj.findOrder(inputs, 2);
		cout << to_string(res) << endl;

		res = obj.findOrderUsingGraph(inputs, 2);
		cout << to_string(res) << endl;
	}

	vector<int> findOrderUsingGraph(vector<Input> inputs, int s) {
		Graph g;
		sort(inputs.begin(), inputs.end(), [](const auto& f, const auto& s) {
			return f.time < s.time;
			});
		for (auto input : inputs) {
			g.addEdge(input.person1, input.person2);
		}

		return g.bfs(s);
	}

	vector<int> findOrder(vector<Input> inputs, int s) {
		sort(inputs.begin(), inputs.end(), [](const auto& f, const auto& s) {
			return f.time < s.time;
			});

		unordered_set<int> seen;
		vector<int> out;
		seen.insert(s);
		out.push_back(s);

		for (auto input : inputs) {
			if (seen.count(input.person1) != 0 || seen.count(input.person2) != 0) {
				if (seen.insert(input.person1).second) {
					out.push_back(input.person1);
				}
				if (seen.insert(input.person2).second) {
					out.push_back(input.person2);
				}
			}
		}

		return out;
	}
};