#pragma once
#include "../Header.h"

class NameMapping {
	class Graph {
	public:
		unordered_map<string, unordered_set<string>> vertices;
		void addEdge(string s, string e) {
			vertices[s].insert(e);
		}
	};
public:
	static void test() {
		NameMapping obj;
		unordered_map<string, int> freqMap = { {"John",10 },{ "Jon",3}, {"Davis",2}, {"Kari",3},{"Johnny",11},
			{"Carlton",8},{"Carleton",2},{"Jonathan",9},{"Carrie",5} };
		vector<pair<string, string>> nameMap = { {"Jonathan","John"},{"Jon","Johnny"},{"Johnny","John"},{"Kari","Carrie"}, {"Carleton","Carlton"} };

		cout << to_string(nameMap) << endl;
		cout << to_string(freqMap) << endl;

		auto res = obj.getNameMap(freqMap, nameMap);
		cout << "(Result) Frequency mapping: " << to_string(res) << endl;
	}

	unordered_map<string, int> getNameMap(unordered_map<string, int> freqMap, vector<pair<string, string>> nameMap) {
		Graph g = constructGraph(nameMap);
		unordered_map<string, string> revMap = getTrueMap(g);
		cout << "Name mapping after graph traversal: " << to_string(revMap) << endl;

		unordered_map<string, int> result;
		for (auto& f : freqMap) {
			auto& key = revMap[f.first];
			result[key] += f.second;
		}

		return result;
	}

private:
	Graph constructGraph(vector<pair<string, string>>& nameMap) {
		Graph g;
		for (auto& entry : nameMap) {
			g.addEdge(entry.first, entry.second);
		}
		return g;
	}

	unordered_map<string, string> getTrueMap(Graph g) {
		unordered_map<string, string> result;
		unordered_set<string> visited;

		for (auto& v : g.vertices) {
			if (visited.find(v.first) == visited.end()) {
				dfs(v.first, g, result, visited);
			}
		}

		return result;
	}

	string dfs(string u, Graph g, unordered_map<string, string>& result, unordered_set<string>& visited) {
		visited.insert(u);

		string p = u;
		for (auto& v : g.vertices[u]) {
			if (visited.find(v) == visited.end()) {
				p = dfs(v, g, result, visited);
			}
		}

		result[u] = p;

		return p;
	}
};