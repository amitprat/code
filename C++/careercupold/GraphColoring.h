#pragma once
#include "../Header.h"

class GraphColoring {
public:
	static void test() {
		GraphColoring obj;

		vector<vector<int>> graph = {
			{ 0, 1, 1, 1 },
			{ 1, 0, 1, 0 },
			{ 1, 1, 0, 1 },
			{ 1, 0, 1, 0 },
		};

		int m = 3;
		auto res = obj.color(graph, m);
		cout << format("Can graph be colored using {} colors? {}", m, to_string(res)) << endl;
	}

	bool color(vector<vector<int>> graph, int m) {
		vector<int> colors(graph.size(), 0);
		bool res = color(graph, 0, m, colors);
		if (res) {
			print("Colors ", colors); cout << endl;
		}
		return res;
	}

	bool color(vector<vector<int>> graph, int pos, int m, vector<int>& colors) {
		if (pos == graph.size()) return true;
		for (int c = 1; c <= m; c++) {
			if (isSafe(graph, pos, c, colors)) {
				colors[pos] = c;
				if (color(graph, pos + 1, m, colors)) return true;
				colors[pos] = 0;
			}
		}
		return false;
	}

private:
	bool isSafe(vector<vector<int>> graph, int u, int c, vector<int> colors) {
		for (int v = 0; v < graph.size(); v++)
		{
			if (graph[u][v] && c == colors[v]) return false;
		}
		return true;
	}
};