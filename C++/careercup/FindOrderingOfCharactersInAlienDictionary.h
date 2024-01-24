#include "../header.h"

/*
https://www.careercup.com/question?id=13394663

Given a dictionary of strings [ strings are in sorted order] you have to find the precedence of characters according to the dictionary..
eat
bxy
e is ranked above b according to the dictionary.
*/
class FindOrderingOfCharactersInAlienDictionary {
   public:
    static void test() {
        FindOrderingOfCharactersInAlienDictionary obj;
        vector<string> words = {"baa", "abcd", "abca", "cab", "cad"};
        auto res1 = obj.getOrderUsingBFS(words);
        auto res2 = obj.getOrderUsingTopoSort(words);
        assert(res1 == res2);
        cout << "Order : " << res1 << endl;
    }

   private:
    vector<char> getOrderUsingBFS(vector<string>& words) {
        unordered_map<char, vector<char>> adjMap;
        unordered_map<char, int> inSize;
        for (int i = 0; i < words.size() - 1; i++) {
            auto prev = words[i];
            auto cur = words[i + 1];

            int j = 0, k = 0;
            for (; j < prev.size(), k < cur.size(); j++, k++) {
                if (prev[j] != cur[k]) break;
            }

            if (j != prev.size() && k != cur.size()) {
                adjMap[prev[j]].push_back(cur[k]);
                inSize[cur[k]]++;
            }
        }

        char start = '\0';
        for (auto& edge : adjMap) {
            if (inSize[edge.first] == 0) {
                start = edge.first;
                break;
            }
        }
        vector<char> order;
        queue<char> q;
        unordered_set<char> visited;
        q.push(start);
        visited.insert(start);
        while (!q.empty()) {
            start = q.front();
            q.pop();
            order.push_back(start);
            auto dsts = adjMap[start];
            for (auto ch : dsts) {
                if (visited.find(ch) == visited.end()) {
                    q.push(ch);
                    visited.insert(ch);
                }
            }
        }

        return order;
    }

   private:
    template <class T>
    class Graph {
       public:
        unordered_map<T, vector<T>> adjMap;
        unordered_set<T> vertices;
        void addEdge(T src, T dst) {
            adjMap[src].push_back(dst);
            vertices.insert(src);
            vertices.insert(dst);
        }
    };
    vector<char> getOrderUsingTopoSort(vector<string>& strs) {
        Graph<char> g;
        for (int i = 0; i < strs.size() - 1; i++) {
            auto cur = strs[i];
            auto next = strs[i + 1];

            int j = 0, k = 0;
            for (; j < cur.size(), k < next.size(); j++, k++) {
                if (cur[j] != next[k]) break;
            }

            if (j != cur.size() && k != next.size()) {
                g.addEdge(cur[j], next[k]);
            }
        }

        return topoOrder(g);
    }

    vector<char> topoOrder(Graph<char> g) {
        unordered_set<char> visited;
        stack<char> st;

        for (auto& ch : g.vertices) {
            if (visited.find(ch) == visited.end()) {
                dfs(g, ch, visited, st);
            }
        }

        vector<char> order;
        while (!st.empty()) {
            order.push_back(st.top());
            st.pop();
        }

        return order;
    }

    void dfs(Graph<char> g, char u, unordered_set<char>& visited, stack<char>& st) {
        visited.insert(u);

        for (auto& v : g.adjMap[u]) {
            if (visited.find(v) == visited.end()) {
                dfs(g, v, visited, st);
            }
        }

        st.push(u);
    }
};