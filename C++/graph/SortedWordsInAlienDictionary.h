#pragma once
#include "../Header.h"
using namespace std;

template <class T>
class Graph
{
private:
    using AdjList = unordered_map<T, vector<T>>;
    AdjList adjList;
    unordered_set<T> vertices;
public:
    int size() { return vertices.size(); }
    void addEdge(T from, T to)
    {
        vertices.insert(from);
        vertices.insert(to);
        adjList[from].push_back(to);
    }

    vector<T> topoSort()
    {
        cout << "Doing topological sorting: " << endl;
        vector<T> res;
        unordered_set<T> visited;
        for (auto v : adjList) {
            if (visited.find(v.first) == visited.end()) {
                dfs(v.first, visited, res);
            }
        }

        cout << "Topological sort result = " << to_string(res) << endl;
        return res;
    }

    void dfs(T u, unordered_set<T>& visited, vector<T>& res)
    {
        visited.insert(u);
        for (auto v : adjList[u]) {
            if (visited.find(v) == visited.end()) {
                dfs(v, visited, res);
            }
        }
        res.insert(res.begin(), u);
    }

    string to_string(vector<T> res) {
        stringstream ss;
        ss << "{";
        for (auto u : res) ss << (char)u << " ";
        ss << "}";
        return ss.str();
    }

    string to_string() {
        stringstream ss;
        ss << "{" << endl;
        for (auto u : adjList) {
            ss << setw(4) << u.first << ":";
            for (auto v : u.second) {
                ss << v << " ";
            }
            ss << endl;
        }
        ss << "}";

        return ss.str();
    }
};

class SortedWordsInAlienDictionary
{
public:
    static void test()
    {
        SortedWordsInAlienDictionary obj;
        vector<string> words = { "cc", "cb", "bb", "ac" };
        vector<char> order = obj.findOrdering(words);
        for (auto ch : order) {
            cout << ch << " ";
        }
        cout << endl;
    }

    vector<char> findOrdering(vector<string> words)
    {
        Graph<char> g;
        for (int i = 0; i < words.size() - 1; i++) {
            string f = words[i];
            string s = words[i + 1];
            int fl = f.length();
            int sl = s.length();
            for (int j = 0; j < min(fl, sl); j++) {
                if (f[j] == s[j]) continue;
                cout << "Adding ordering from " << f[j] << "->" << s[j] << endl;
                g.addEdge(f[j], s[j]);
                break;
            }
        }
        cout << "Graph:" << endl;
        cout << g.to_string() << endl;

        return g.topoSort();
    }
};