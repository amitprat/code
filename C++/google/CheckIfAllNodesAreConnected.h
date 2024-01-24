#include "../Header.h"

/*
https://www.careercup.com/question?id=5713002834165760

Given a Start Node and an End Node in a graph report if they are “necessarily connected”. This means that all paths from 
the start node lead to the end node. Report true all paths from start node lead to end node and false if at least one path 
does not lead to the end node. This is a directed graph which can have cycles


Does anyone know how to solve this? I had it in my interview at Google in CA and I still cant solve it
*/

def helper(adj, visited, start, end):
	if start == end:
		return True
	if len(adj[start])==0:
		return False
	visited[start] = True
	return all([helper(adj, visited, child, end) for child in adj[start] if not visited[child]])

def allPathsConnect(adj, start, end):
	v = {node:False for node in adj}
	return helper(adj, v, start, end)

/*
You need to find a path from start that does not end in the end node. You can brute force all paths for from start.
You can optimize if you store for a given node if it has a path to end so you do not redo the same work over and over.
Recursive solution should be straight forward.
*/

#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

class Graph
{
public:
    unordered_map<char, vector<char>> adjList;
    void addEdge(char u, char v)
    {
        adjList[u].push_back(v);
    }
};
bool allConnected(Graph g, char s, char d, unordered_map<char, bool> &memo)
{
    if (s == d)
        return true;

    if (memo.find(s) != memo.end())
        return memo[s];

    bool conn = !g.adjList[s].empty();
    for (auto v : g.adjList[s])
    {
        conn &= allConnected(g, v, d, memo);
        if (!conn)
            break;
    }
    memo[s] = conn;

    return memo[s];
}

bool allConnected(Graph g, char s, char d)
{
    unordered_map<char, bool> memo;

    return allConnected(g, s, d, memo);
}

int main()
{
    Graph g;
    char a = 'a';
    char b = 'b';
    char c = 'c';
    char d = 'd';
    char e = 'e';
    char f = 'f';
    char g1 = 'g';
    char h = 'h';
    char i = 'i';
    char s = 's';
    char l = 'l';
    g.addEdge(s, b);
    g.addEdge(s, c);
    g.addEdge(s, d);
    g.addEdge(b, e);
    g.addEdge(c, e);
    g.addEdge(d, e);
    g.addEdge(e, f);
    g.addEdge(e, g1);
    g.addEdge(e, h);
    g.addEdge(f, i);
    g.addEdge(g1, i);
    g.addEdge(i, l);
    //g.addEdge(h,l);

    auto res = allConnected(g, s, l);
    cout << res << endl;

    return 0;
}
