/*
https://neetcode.io/problems/network-delay-time

Network Delay Time
You are given a network of n directed nodes, labeled from 1 to n. You are also given times, a list of directed edges where times[i] = (ui, vi, ti).

ui is the source node (an integer from 1 to n)
vi is the target node (an integer from 1 to n)
ti is the time it takes for a signal to travel from the source to the target node (an integer greater than or equal to 0).
You are also given an integer k, representing the node that we will send a signal from.

Return the minimum time it takes for all of the n nodes to receive the signal. If it is impossible for all the nodes to receive the signal, return -1 instead.
*/

#include "../header.h"

class NetworkDelay {
   public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int, int>>> adjGraph;
        for (auto& time : times) {
            adjGraph[time[0]].push_back({time[1], time[2]});
        }

        vector<bool> visisted(n + 1, false);
        vector<int> dist(n);
        dfs(adjGraph, k, dist, 0);

        int res = *max_element(dist.begin() + 1, dist.end());

        return res;
    }

    void dfs(const unordered_map<int, vector<pair<int, int>>> adjGraph, int src, vector<int>& dist, int time) {
        dist[src] = time;

        for (const auto& [v, w] : adjGraph.at(src)) {
            if (dist[v] > dist[src] + w) {
                dfs(adjGraph, v, dist, dist[src] + w);
            }
        }
    }
};