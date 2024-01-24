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
using namespace std;

class Graph
{
private:
    int V, E;
    vector<int> vertices;
    unordered_map<int, unordered_set<int>> map;

    void dfsUtil(int u, unordered_set<int>& set, vector<int>& res)
    {
        res.push_back(u);
        set.insert(u);

        for (auto v : map[u])
        {
            if (set.find(v) == set.end())
            {
                dfsUtil(v, set, res);
            }
        }
    }

    void topoUtil(int u, unordered_set<int>& set, stack<int>& res)
    {
        set.insert(u);

        for (auto v : map[u])
        {
            if (set.find(v) == set.end())
            {
                topoUtil(v, set, res);
            }
        }
        res.push(u);
    }

public:
    Graph(int V = 0, int E = 0) : V(V), E(E) {}
    void addEdge(int src, int dst)
    {
        if (map.find(src) == map.end()) {
            vertices.push_back(src);
            V++;
        }
        auto res = map[src].insert(dst);
        if (res.second) {
            vertices.push_back(dst);
            V++;
            E++;
        }
    }

    vector<int> dfs()
    {
        unordered_set<int> set;
        vector<int> res;
        for (auto u : vertices)
        {
            if (set.find(u) == set.end())
            {
                dfsUtil(u, set, res);
            }
        }

        return res;
    }

    stack<int> topo()
    {
        unordered_set<int> set;
        stack<int> res;
        for (auto u : vertices)
        {
            if (set.find(u) == set.end())
            {
                topoUtil(u, set, res);
            }
        }

        return res;
    }

    int getV() { return V; }
    int getE() { return E; }

    class Iterator
    {
    private:
        Graph* g;
        queue<int> q;
        unordered_set<int> set;

    public:
        Iterator(Graph* g) : g(g) {
            q.push(g->vertices[0]);
        }

        Iterator& operator=(Graph* g)
        {
            this->g = g;
            this->q.push(g->vertices[0]);

            return *this;
        }
        Iterator& operator++()
        {
            queue<int> next;
            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (auto v : g->map[u]) {
                    if (set.find(v) == set.end()) {
                        next.push(v);
                    }
                }
            }

            q = next;

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator iter = *this;
            ++* this;

            return iter;
        }

        bool operator!=(const Iterator& iter)
        {
            return true;
        }

        vector<int> operator*()
        {
            queue<int> tmp = q;
            vector<int> res;
            while (!tmp.empty()) {
                res.push_back(tmp.front());
                tmp.pop();
            }

            return res;
        }
    };

private:
    Iterator* iter = nullptr;

public:
    Iterator& begin()
    {
        iter = new Iterator(this);
        return *iter;
    }

    Iterator& end()
    {
        return *iter++;
    }
};
class PrintOverallSeq
{
private:
    Graph g;

public:
    static void test()
    {
        PrintOverallSeq obj;
        vector<vector<int>> seqs = {
            {1,3,5},{1,3,9},{9,5},{2,3},{4,3},{1,2}
        };

        auto res = obj.generate(seqs);
        while (!res.empty()) {
            cout << res.top() << " ";
            res.pop();
        }
        cout << endl;
    }

    stack<int> generate(vector<vector<int>> seqs)
    {
        for (auto seq : seqs)
        {
            for (int i = 0; i < seq.size() - 1; i++) {
                g.addEdge(seq[i], seq[i + 1]);
            }
        }

        //auto dfs = g.dfs();
        //for (auto i : dfs) cout << i << " ";
        //cout << endl;

        for (auto iter = g.begin(); iter != g.end(); iter++)
        {
            for (auto i : *iter) { cout << i << " "; } cout << endl;
        }

        auto topo = g.topo();

        return topo;
    }
};