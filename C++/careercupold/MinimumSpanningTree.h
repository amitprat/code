#pragma once
#include "../Header.h"

class PrimsMSTMatrixGraph {
public:
	static void test() {
		PrimsMSTMatrixGraph obj;
		vector<vector<int>> g = {
			{ 0, 2, 0, 6, 0 },
			{ 2, 0, 3, 8, 5 },
			{ 0, 3, 0, 0, 7 },
			{ 6, 8, 0, 0, 9 },
			{ 0, 5, 7, 9, 0 }
		};

		int V = g.size();
		auto res = obj.mst(g);
		auto dist = res.first;
		auto parent = res.second;
		int minSpanningDist = 0;
		for (int v = 1; v < V; v++) {
			minSpanningDist += dist[v];
			auto u = parent[v];
			cout << format("({}->{},{})", u, v, dist[v]);
			if (v != V - 1) cout << "<--->";
		}
		cout << endl;
		cout << "Minimum spanning distance: " << minSpanningDist << endl << endl;
	}

	pair<vector<int>, vector<int>> mst(vector<vector<int>> g) {
		vector<int> dst(g.size(), INT_MAX);
		vector<int> parent(g.size(), -1);
		vector<bool> visited(g.size(), false);
		dst[0] = 0;

		for (int cnt = 0; cnt < g.size() - 1; cnt++) {
			int u = minVertex(dst, visited);
			visited[u] = true;
			for (int v = 0; v < g.size(); v++) {
				if (g[u][v] && !visited[v]) {
					if (g[u][v] < dst[v]) {
						dst[v] = g[u][v];
						parent[v] = u;
					}
				}
			}
		}

		return { dst,parent };
	}

private:
	int minVertex(vector<int> dst, vector<bool> visited) {
		int mn = INT_MAX;
		int mnIndex = -1;
		for (auto i = 0; i < dst.size(); i++) {
			if (!visited[i] && dst[i] < mn) {
				mn = dst[i];
				mnIndex = i;
			}
		}
		return mnIndex;
	}
};

class PrimsMSTAdjListGraph {
	struct Graph {
		int V;
		Graph(int v) :V(v) {}
		struct Edge {
			int v, w;
		};
		unordered_map<int, vector<Edge>> edges;
		void addEdge(int u, int v, int w) {
			edges[u].push_back({ v,w });
			edges[v].push_back({ u,w });
		}
	};
	class Minheap {
		vector<pair<int, int>> arr; // {w, u}
	public:
		void insert(pair<int, int> u) {
			arr.push_back(u);
			upHeapify(arr.size() - 1);
		}
		int size() { return arr.size(); }
		pair<int, int> pop() {
			auto res = arr[0];
			arr[0] = arr[arr.size() - 1];
			arr.pop_back();
			downHeapify(0);

			return res;
		}
	private:
		void downHeapify(int p) {
			int mn = p;
			int lp = left(p);
			if (lp < arr.size() && arr[lp].second < arr[mn].second) { mn = lp; }
			int rp = right(p);
			if (rp < arr.size() && arr[rp].second < arr[mn].second) { mn = rp; }

			if (mn != p) {
				swap(arr[mn], arr[p]);
				downHeapify(mn);
			}
		}
		void upHeapify(int u) {
			int p = parent(u);
			while (u != 0 && arr[p].second > arr[u].second) {
				swap(arr[p], arr[u]);
				u = p;
				p = parent(u);
			}
		}
		int parent(int u) {
			return (u - 1) / 2;
		}
		int left(int u) {
			return 2 * u + 1;
		}
		int right(int u) {
			return 2 * u + 2;
		}
	};
public:
	static void test() {
		PrimsMSTAdjListGraph obj;
		Graph g(9);
		g.addEdge(0, 1, 4);
		g.addEdge(0, 7, 8);
		g.addEdge(1, 2, 8);
		g.addEdge(1, 7, 11);
		g.addEdge(2, 3, 7);
		g.addEdge(2, 8, 2);
		g.addEdge(2, 5, 4);
		g.addEdge(3, 4, 9);
		g.addEdge(3, 5, 14);
		g.addEdge(4, 5, 10);
		g.addEdge(5, 6, 2);
		g.addEdge(6, 7, 1);
		g.addEdge(6, 8, 6);
		g.addEdge(7, 8, 7);

		auto res = obj.mstSTL(g);
		auto dist = res.first;
		auto parent = res.second;
		int minSpanningDist = 0;
		for (int v = 1; v < g.V; v++) {
			minSpanningDist += dist[v];
			auto u = parent[v];
			cout << format("({}->{},{})", u, v, dist[v]);
			if (v != g.V - 1) cout << "<--->";
		}
		cout << endl;
		cout << "Minimum spanning distance: " << minSpanningDist << endl << endl;
	}

	pair<vector<int>, vector<int>> mst(Graph g) {
		unordered_set<int> visited;
		vector<int> dist(g.V, INT_MAX);
		vector<int> parent(g.V, -1);
		int src = 0;

		Minheap mh;
		dist[src] = 0;
		mh.insert({ dist[src], src }); // {w,v}

		while (mh.size() != 0) {
			auto u = mh.pop();
			if (visited.count(u.second) != 0) continue;
			visited.insert(u.second);

			for (auto e : g.edges[u.second]) {
				if (visited.count(e.v) == 0 && e.w < dist[e.v]) {
					dist[e.v] = e.w;
					parent[e.v] = u.second;
					mh.insert({ dist[e.v], e.v });
				}
			}
		}

		return { dist, parent };
	}

	pair<vector<int>, vector<int>> mstSTL(Graph g) {
		unordered_set<int> visited;
		vector<int> dist(g.V, INT_MAX);
		vector<int> parent(g.V, -1);
		int src = 0;

		using  p = pair<int, int>; // {w,v}
		priority_queue<p, vector<p>, greater<p>> pq;
		dist[src] = 0;
		pq.push({ dist[src], src }); // {w,v}

		while (!pq.empty()) {
			auto u = pq.top(); pq.pop();
			if (visited.count(u.second) != 0) continue;
			visited.insert(u.second);

			for (auto e : g.edges[u.second]) {
				if (visited.count(e.v) == 0 && e.w < dist[e.v]) {
					dist[e.v] = e.w;
					parent[e.v] = u.second;
					pq.push({ dist[e.v], e.v });
				}
			}
		}

		return { dist, parent };
	}
};

class KrushkalsMSTInEdgeGraph {
	struct Edge {
		int u, v, w;
	};
	struct Graph {
		int V;
		vector<Edge> edges;
		Graph(int v) :V(v) {}
		void addEdge(int u, int v, int w) {
			edges.push_back({ u,v,w });
			edges.push_back({ v,u,w });
		}
	};
	struct UnionFind {
		vector<int> arr;
		vector<int> rank;
		UnionFind(int sz) {
			arr.resize(sz);
			rank.resize(sz);
			for (int i = 0; i < sz; i++) {
				arr[i] = i;
				rank[i] = 0;
			}
		}
		int find(int p) {
			while (arr[p] != p) {
				p = arr[p];
			}
			return p;
		}
		void Union(int p, int q) {
			auto pRoot = find(p);
			auto qRoot = find(q);

			if (rank[pRoot] == rank[qRoot]) rank[pRoot]++;
			if (rank[pRoot] < rank[qRoot]) {
				arr[pRoot] = qRoot;
			}
			else if (rank[qRoot] < rank[pRoot]) {
				arr[qRoot] = pRoot;
			}
		}

		bool connected(int p, int q) {
			return find(p) == find(q);
		}
	};
public:
	static void test() {
		KrushkalsMSTInEdgeGraph obj;
		Graph g(4);
		g.addEdge(0, 1, 10);
		g.addEdge(0, 2, 6);
		g.addEdge(0, 3, 5);
		g.addEdge(1, 3, 15);
		g.addEdge(2, 3, 4);

		vector<Edge> edges = obj.mst(g);
		int minSpanningDist = 0;
		int cnt = 0;
		for (auto e : edges) {
			minSpanningDist += e.w;
			cout << format("({}->{},{})", e.u, e.v, e.w);
			if (cnt != edges.size() - 1) cout << "<--->";
		}
		cout << endl;
		cout << "Minimum spanning distance: " << minSpanningDist << endl << endl;
	}

	vector<Edge> mst(Graph g) {
		sort(g.edges.begin(), g.edges.end(), [](auto f, auto s) {return f.w < s.w; });
		vector<Edge> edges;
		UnionFind uf(g.V);
		int e = 0;
		while (edges.size() < g.V - 1 && e < g.edges.size()) {
			auto edge = g.edges[e++]; // pick first edge
			if (!uf.connected(edge.u, edge.v)) {
				edges.push_back(edge);
				uf.Union(edge.u, edge.v);
			}
		}

		return edges;
	}
};

class MinimumSpanningTree {
public:
	static void test() {
		PrimsMSTMatrixGraph::test();
		PrimsMSTAdjListGraph::test();
		KrushkalsMSTInEdgeGraph::test();
	}
};