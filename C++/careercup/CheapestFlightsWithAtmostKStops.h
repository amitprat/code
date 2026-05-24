#pragma once
#include "../header.h"

/*
* There are n cities connected by m flights. Each flight starts from city u and arrives at v with a price w.
* Now given all the cities and flights, together with starting city src and the destination dst, your task is
* to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

* Example 1:
* Input:
* n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
* src = 0, dst = 2, k = 1
* Output: 200
* Explanation:
* The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
* Example 2:
* Input:
* n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
* src = 0, dst = 2, k = 0
* Output: 500
* Explanation:
* The graph is like this:
* The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
*
* This is weighted graph problem. We can use Dijkstra's algorithm to solve this problem. We will use a min-heap
* to keep track of the minimum cost to reach each city. We will also keep track of the number of stops made to reach each city.
* We will only add a city to the min-heap. if the number of stops made to reach that city is less than or equal to k.
* We will continue this process until we reach the destination city or the min-heap is empty.
* Time complexity: O(E log V), where E is the number of edges and V is the number of vertices.
* Space complexity: O(V + E), where V is the number of vertices and E is the number of edges.
* Note: Dijkstra's algorithm is not the most efficient algorithm for this problem, but it is a valid solution.
*
* We can also use Bellman-Ford algorithm to solve this problem in O(V * E) time complexity.

For this specific problem, Bellman-Ford is arguably BETTER than Dijkstra. Here's why:

Bellman-Ford Advantages for K-Stops Problem
Aspect	Bellman-Ford	Dijkstra
Time Complexity	O(k·E) when k < V	O(E log V)
K-stops handling	Naturally models constraint (k+1 iterations = k stops)	Requires tracking stops in data structure
Logic clarity	Simple: relax edges k+1 times	Complex: manage heap with (cost, city, stops) tuples
Worst case	O(V·E) if k ≥ V	O(E log V) always

Why Bellman-Ford Fits Better
Direct constraint modeling - The k-stops requirement maps directly to "relax edges k+1 times"


This is elegant and intuitive.

Practical efficiency - If k is small (which is common), it's O(k·E) ≈ O(E) instead of O(E log V)

Simpler code - No need to track stops in heap; just iterate the constraint number of times

Correct by design - The algorithm's structure enforces the k-stop limit automatically

When Dijkstra Wins
When k is very large (close to V), making k·E worse than E log V
When you need guaranteed optimal exploration order
Bottom Line
Use Bellman-Ford for this problem. It's not just simpler—it's more efficient for the typical case where k << V,
and it naturally expresses the constraint. Your current implementation is the cleanest approach for this specific problem.
*/

class CheapestFlightsWithAtmostKStops {
   public:
    static void test() {
        CheapestFlightsWithAtmostKStops obj;
        int n = 3;
        vector<vector<int>> edges = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
        int src = 0;
        int dst = 2;
        int k = 1;

        auto res = obj.findCheapestPriceUsingDijkastra(n, edges, src, dst, k);

        println("Cheapest price: {}", res);
    }

   private:
    int findCheapestPriceUsingDijkastra(int n, vector<vector<int>>& edges, int src, int dst, int k) {
        // Build the graph
        // {u -> {v, w}, ...}
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }

        // Min-heap to store (cost, city, stops)
        // We use a tuple to store the cost, city, and number of stops. The min-heap will prioritize the lowest cost.
        // it uses the first element of the tuple (cost) to compare and sort the elements in the min-heap.
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minHeap;
        minHeap.push({0, src, 0});

        while (!minHeap.empty()) {
            auto [cost, city, stops] = minHeap.top();
            minHeap.pop();

            // If we reached the destination city
            if (city == dst) {
                return cost;
            }

            // If we have made more than k stops, skip this path
            if (stops > k) {
                continue;
            }

            // Explore the neighbors
            for (auto& neighbor : graph[city]) {
                int nextCity = neighbor.first;
                int price = neighbor.second;

                minHeap.push({cost + price, nextCity, stops + 1});
            }
        }

        return -1;  // No such route exists
    }

   private:
    int cheapestPriceUsingBellmanFord(int n, vector<vector<int>>& edges, int src, int dst, int k) {
        // Initialize distances to all cities as infinity
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        // Relax edges up to k + 1 times to all the destinations reachable within k stops
        // After k stops, we can only reach cities that are at most k + 1 edges away from the source.
        // We use a temporary distance array to store the updated distances for each iteration, so that
        // we don't overwrite the distances of the current iteration.
        for (int i = 0; i <= k; i++) {
            vector<int> tempDist = dist;  // Create a temporary copy of distances

            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                if (dist[u] != INT_MAX && dist[u] + w < tempDist[v]) {
                    tempDist[v] = dist[u] + w;
                }
            }

            dist = tempDist;  // Update distances after each iteration
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];  // Return -1 if no such route exists
    }

   private:
    int findCheapestPriceUsingShortestPathFasterAlgorithm(int n, vector<vector<int>>& edges, int src, int dst, int k) {
        // Build the graph
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }

        // Queue to store (city, cost, stops)
        queue<tuple<int, int, int>> q;
        q.push({src, 0, 0});

        while (!q.empty()) {
            auto [city, cost, stops] = q.front();
            q.pop();

            // If we reached the destination city
            if (city == dst) {
                return cost;
            }

            // If we have made more than k stops, skip this path
            if (stops > k) {
                continue;
            }

            // Explore the neighbors
            for (auto& neighbor : graph[city]) {
                int nextCity = neighbor.first;
                int price = neighbor.second;

                q.push({nextCity, cost + price, stops + 1});
            }
        }

        return -1;  // No such route exists
    }
};