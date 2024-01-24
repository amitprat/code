#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=13394663

Given a dictionary of strings [ strings are in sorted order] you have to find the precedence of characters according to the dictionary..
eat
bxy
e is ranked above b according to the dictionary.
*/
class FindOrderInSortedWordsFromAlienDictionary
{
    class Graph
    {
        unordered_map<char, vector<char>> edges;
        unordered_set<char> vertices;
    public:
        void addEdge(char s, char d) {
            vertices.insert(s);
            vertices.insert(d);
            edges[s].push_back(d);
        }
        vector<char> get_vertices() {
            return { vertices.begin(), vertices.end() };
        }

        vector<char> get_edges(char u) {
            return edges[u];
        }
    };
public:
    static void test()
    {
        vector<string> words = { "eat", "bxy" };
        vector<char> res = findSortedChars(words);
        cout << to_string(res) << endl;
    }

    static vector<char> findSortedChars(vector<string>& words)
    {
        Graph g;
        for (int i = 1; i < words.size(); i++) {
            for (int j = 0; j < min(words[i - 1].length(), words[i].length()); j++)
            {
                if (words[i - 1][j] != words[i][j]) {
                    g.addEdge(words[i - 1][j], words[i][j]);
                    break;
                }
            }
        }

        vector<char> result = topologicalSort(g);

        return result;
    }

    static vector<char> topologicalSort(Graph g) {
        unordered_set<char> visited;
        stack<char> st;

        for (auto u : g.get_vertices()) {
            if (visited.find(u) == visited.end()) {
                dfs(g, u, visited, st);
            }
        }

        vector<char> result;
        while (!st.empty()) {
            result.push_back(st.top()); st.pop();
        }

        return result;
    }

    static void dfs(Graph g, char u, unordered_set<char>& visited, stack<char>& st)
    {
        visited.insert(u);

        for (auto v : g.get_edges(u)) {
            if (visited.find(v) == visited.end()) {
                dfs(g, v, visited, st);
            }
        }
        st.push(u);
    }
};