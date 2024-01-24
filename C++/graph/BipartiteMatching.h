#pragma once
#include "../Header.h"

constexpr auto M = 6;
constexpr auto N = 6;

class BipartiteMatching {
public:
    static void test() {
        BipartiteMatching obj;
        bool bpGraph[M][N] = { {0, 1, 1, 0, 0, 0},
                      {1, 0, 0, 1, 0, 0},
                      {0, 0, 1, 0, 0, 0},
                      {0, 0, 1, 1, 0, 0},
                      {0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 1} };

        auto res = obj.maxBPM(bpGraph);
        cout << "Maximum number of applicants that can get job is "
            << res;
    }

    int maxBPM(bool graph[M][N]) {
        unordered_set<int> jobAssigned;
        int res = 0;
        for (int appl = 0; appl < M; appl++) {
            if (canGetJob(appl, graph, jobAssigned)) res++;
        }
        return res;
    }

private:
    bool canGetJob(int applicant, bool graph[M][N], unordered_set<int>& jobAssigned) {
        for (int v = 0; v < N; v++) {
            if (graph[applicant][v]) {
                if (jobAssigned.find(v) == jobAssigned.end()) {
                    jobAssigned.insert(v);
                    return true;
                }
            }
        }
        return false;
    }
};