#pragma once
#include "../header.h"

class MinimumSumInTraingle {
public:
    static void test() {
        MinimumSumInTraingle obj;
        vector<vector<int>> traingle = {
            {2} ,
            {2, 4},
            {2, 5, 7},
            {10, 5, 1, 2}
        };
        cout << "Minimum Sum of traingle = " << obj.getMinimumSumDFSLimitedStackSpace(traingle) << endl;
    }

    int getMinimumSumDFS(vector<vector<int>>& traingle)
    {
        stack<pair<int, pair<int, int>>> st;
        int i = 0;
        int n = traingle.size() - 1;
        for (int j = 0; j < traingle[0].size(); j++) st.push({ traingle[0][j],{0,j} });
        int mnSum = INT_MAX;
        while (!st.empty()) {
            auto cur = st.top(); st.pop();
            //cout << "{" << cur.second.first << "," << cur.second.second << "}" << endl;
            if (isEnd(cur.second, n)) { mnSum = min(mnSum, cur.first); continue; }
            auto neighbours = getNeighbours(cur.second, n, traingle[cur.second.first + 1].size());
            for (auto& neighbour : neighbours) {
                auto curSum = cur.first + traingle[neighbour.first][neighbour.second];
                st.push({ curSum, neighbour });
            }
        }
        return mnSum;
    }

    int getMinimumSumBFS(vector<vector<int>>& traingle)
    {
        queue<pair<int, pair<int, int>>> q;
        int i = 0;
        int n = traingle.size() - 1;
        for (int j = 0; j < traingle[0].size(); j++) q.push({ traingle[0][j],{0,j} });
        int mnSum = INT_MAX;
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            //cout << "{" << cur.second.first << "," << cur.second.second << "}" << endl;
            if (isEnd(cur.second, n)) { mnSum = min(mnSum, cur.first); continue; }
            auto neighbours = getNeighbours(cur.second, n, traingle[cur.second.first + 1].size());
            for (auto& neighbour : neighbours) {
                auto curSum = cur.first + traingle[neighbour.first][neighbour.second];
                q.push({ curSum, neighbour });
            }
        }
        return mnSum;
    }

    int getMinimumSumDFSLimitedStackSpace(vector<vector<int>>& traingle)
    {
        stack<pair<int, pair<int, int>>> st;
        int n = traingle.size() - 1;
        int prevSum = 0;
        for (int i = 0; i <= n; i++) {
            st.push({ prevSum + traingle[i][0],{i,0} }); prevSum += traingle[i][0];
        }
        pair<int, pair<int, int>> cur;
        int mnSum = INT_MAX;
        while (!st.empty()) {
            cur = st.top(); st.pop();
            pair<int, int> next;
            if (hasNext(cur.second, next, traingle[cur.second.first].size(), st.top().second)) st.push({ traingle[next.first][next.second],next });
            if (isEnd(cur.second, n)) mnSum = min(mnSum, cur.first);
        }

        return mnSum;
    }

private:
    bool isEnd(pair<int, int> p, int n) {
        return p.first == n;
    }
    vector<pair<int, int>> getNeighbours(pair<int, int> p, int n, int m) {
        vector<pair<int, int>> result;
        if (p.first + 1 <= n) result.push_back({ p.first + 1,p.second });
        if (p.first + 1 <= n && p.second + 1 < m) result.push_back({ p.first + 1,p.second + 1 });
        return result;
    }

    bool hasNext(pair<int, int> cur, pair<int, int>& next, int m, pair<int, int> p)
    {
        next = nextRight(cur, m);
        if (next.first == -1 || next.second > p.second + 1) next = parent(cur, m);
        if (next.first == -1) return false;
        return true;
    }

    pair<int, int> nextRight(pair<int, int> p, int m) {
        if (p.second + 1 < m) return { p.first, p.second + 1 };
        return { -1,-1 };
    }
    pair<int, int> parent(pair<int, int> p, int m) {
        if (p.first > 0 && p.second < m - 1) return { p.first - 1, p.second };
        if (p.first > 0) return { p.first - 1, p.second - 1 };
        return { -1,-1 };
    }
};