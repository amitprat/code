#pragma once
#include "../Header.h"

class FindIternerary {
    class Graph {
        unordered_map<string, vector<string>> edges;
        unordered_set<string> vertices;
    public:
        void add(string src, string dst) {
            edges[src].push_back(dst);
            vertices.insert(src);
            vertices.insert(dst);
        }

        vector<string> order() {
            stack<string> st;
            unordered_set<string> visited;
            for (auto v : vertices) {
                if (visited.count(v) == 0) {
                    dfs(v, visited, st);
                }
            }
            vector<string> result;
            while (!st.empty()) {
                result.push_back(st.top());
                st.pop();
            }

            return result;
        }

        void dfs(string u, unordered_set<string>& visited, stack<string>& st) {
            visited.insert(u);

            for (auto v : edges[u]) {
                if (visited.count(v) == 0) {
                    dfs(v, visited, st);
                }
            }

            st.push(u);
        }
    };
public:
    static void test() {
        unordered_map<string, string> dataSet;
        dataSet["Chennai"] = "Banglore";
        dataSet["Bombay"] = "Delhi";
        dataSet["Goa"] = "Chennai";
        dataSet["Delhi"] = "Goa";

        printIterUsingToposort(dataSet);
    }

    static void printIterUsingToposort(unordered_map<string, string> dataset) {
        Graph g;
        for (auto e : dataset) {
            g.add(e.first, e.second);
        }

        cout << g.order() << endl;
    }

    static void printItinerary(unordered_map<string, string> dataset) {
        unordered_map<string, string> revMap;
        for (auto e : dataset) revMap.insert({ e.second,e.first });

        string start;
        for (auto e : dataset) {
            if (revMap.find(e.first) == revMap.end()) {
                start = e.first;
                break;
            }
        }

        do {
            cout << start << "->";
            start = dataset[start];
        } while (dataset.find(start) != dataset.end());
        cout << start << endl;
    }
};