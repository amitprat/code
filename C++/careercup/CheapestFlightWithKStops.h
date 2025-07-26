#pragma once
#include "../header.h"

class CheapestFlightWithKStops {
    struct Edge {
        int v, w;
    };
    struct EdgeWithDist {
        Edge e;
        int steps;
        int dist;
    };

   public:
    static void test() {
        int n = 4;
        vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
        int src = 0, dst = 3, k = 1;

        CheapestFlightWithKStops obj;
        auto cost = obj.findCheapestPriceBFS(n, flights, src, dst, k);
        cout << "Cost = " << cost << endl;
    }

   public:
    int findCheapestPriceBFS(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int, vector<Edge>> adjMap;
        for (auto& flight : flights) {
            auto u = flight[0];
            auto v = flight[1];
            auto w = flight[2];
            adjMap[u].push_back({v, w});
        }

        queue<pair<int, int>> q;
        q.push({src, 0});

        vector<int> minCost(n, INT_MAX);

        int cost = INT_MAX;

        while (!q.empty() && k-- >= 0) {
            auto sz = q.size();
            while (sz--) {
                auto& [u, cost] = q.front();
                q.pop();

                for (auto& [v, w] : adjMap[u]) {
                    if (minCost[v] > w + cost) {
                        minCost[v] = w + cost;
                        q.push({v, minCost[v]});
                    }
                }
            }
        }

        return minCost[dst];
    }

   public:
    int findCheapestPriceWithDijkastra(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int, vector<Edge>> adjMap;
        for (auto& flight : flights) {
            auto u = flight[0];
            auto v = flight[1];
            auto w = flight[2];
            adjMap[u].push_back({v, w});
        }

        auto cmp = [](const auto& f, const auto& s) { return f.e.w < s.e.w; };
        priority_queue<EdgeWithDist, vector<EdgeWithDist>, decltype(cmp)> pq(cmp);
        pq.push({{src, 0}, 0, 0});

        vector<int> dist(flights.size(), INT_MAX);
        dist[src] = 0;

        int cost = INT_MAX;
        while (!pq.empty()) {
            auto t = pq.top();
            pq.pop();
            auto u = t.e.v;

            if (u == dst) return t.dist;
            if (t.steps > k) continue;

            for (auto& [v, w] : adjMap[u]) {
                if (dist[v] > t.dist + w) {
                    dist[v] = t.dist + w;
                    pq.push({{v, dist[v]}, t.steps + 1, t.dist + w});
                }
            }
        }

        return cost;
    }
};