#include "../header.h"
using namespace std;

const int N = 5;
class CountPath
{
public:
    using Point = pair<int, int>;
    const vector<Point> nb = { {-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1} };
    static void test()
    {
        CountPath obj;
        bool matrix[N][N] = {
            {1,0,1,1,1},
            {0,1,0,1,1},
            {0,0,1,1,1},
            {1,0,1,0,1},
            {0,1,1,1,1}
        };

        auto res = obj.getPath(matrix, N, { 0,0 }, { 4,4 });
        for (auto i : res) {
            cout << "{" << i.first << ", " << i.second << "}, ";
        }
        cout << endl;

        pair<Point, int> dist = obj.minDistByTogglingCell(matrix, N, { 0,0 }, { 4,4 });
        cout << "Point toggled = " << to_string(dist.first) << ", distance = " << dist.second << endl;
    }

    static string to_string(Point p) {
        return "{" + std::to_string(p.first) + ", " + std::to_string(p.second) + "}";
    }

    pair<Point, int> minDistByTogglingCell(bool matrix[][N], int N, Point start, Point end) {
        vector<vector<pair<int, int>>> distMatrix(N, vector<pair<int, int>>(N, { INT_MAX,INT_MAX }));
        // distance to all nodes from start point
        {
            queue<pair<Point, int>> q;
            q.push({ start,0 });
            unordered_set<string> visited;
            visited.insert(to_string(start));

            while (!q.empty()) {
                auto u = q.front(); q.pop();
                for (auto v : getChildren(u.first)) {
                    distMatrix[v.first][v.second].first = min(distMatrix[v.first][v.second].first, u.second + 1);
                    if (visited.find(to_string(v)) == visited.end()) {
                        visited.insert(to_string(v));

                        if (matrix[v.first][v.second] == 1) {
                            q.push({ v, u.second + 1 });
                        }
                    }
                }
            }
        }
        // distance to all nodes from end point
        {
            queue<pair<Point, int>> q;
            q.push({ end,0 });
            unordered_set<string> visited;
            visited.insert(to_string(end));

            while (!q.empty()) {
                auto u = q.front(); q.pop();
                for (auto v : getChildren(u.first)) {
                    distMatrix[v.first][v.second].second = min(distMatrix[v.first][v.second].second, u.second + 1);
                    if (visited.find(to_string(v)) == visited.end()) {
                        visited.insert(to_string(v));

                        if (matrix[v.first][v.second] == 1) {
                            q.push({ v, u.second + 1 });
                        }
                    }
                }
            }
        }

        int shortest = INT_MAX;
        Point shorted;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (distMatrix[i][j].first != INT_MAX &&
                    distMatrix[i][j].second != INT_MAX &&
                    distMatrix[i][j].first + distMatrix[i][j].second < shortest) {
                    shortest = distMatrix[i][j].first + distMatrix[i][j].second;
                    shorted = { i,j };
                }
            }
        }

        return { shorted,shortest };
    }

    struct hash_pair {
        template <class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const
        {
            auto hash1 = hash<T1>{}(p.first);
            auto hash2 = hash<T2>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    vector<Point> getPath(bool matrix[][N], int N, Point start, Point end)
    {
        vector<Point> result;
        unordered_set <Point, hash_pair> set;

        queue<pair<Point, vector<Point>>> q;
        q.push({ start, {start} });
        set.insert(start);

        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (u.first == end) return u.second;
            for (auto v : getChildren(u.first)) {
                if (set.find(v) == set.end() && matrix[v.first][v.second] == 1) {
                    auto p = u.second;
                    p.push_back(v);
                    q.push({ v, p });
                    set.insert(v);
                }
            }
        }

        return {};
    }

    vector<Point> getChildren(Point u)
    {
        vector<Point> res;
        for (auto n : nb) {
            Point  p = { u.first + n.first, u.second + n.second };
            if (valid(p)) res.push_back(p);
        }

        return res;
    }

    bool valid(Point p) {
        return p.first >= 0 && p.second >= 0 && p.first < N&& p.second < N;
    }
};