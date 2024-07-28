#include "../header.h"
using namespace std;

const int N = 5;
class CountPath {
   public:
    const vector<Point> nb = {{-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}};
    static void test() {
        CountPath obj;
        bool matrix[N][N] = {
            {1, 0, 1, 1, 1},
            {0, 1, 0, 1, 1},
            {0, 0, 1, 1, 1},
            {1, 0, 1, 0, 1},
            {0, 1, 1, 1, 1}};

        auto res = obj.getShortestPathFromSourceToDestination(matrix, N, {0, 0}, {4, 4});
        cout << res << endl;

        pair<Point, int> dist = obj.minDistByTogglingCell(matrix, N, {0, 0}, {4, 4});
        cout << "Point toggled = " << dist.first << ", distance = " << dist.second << endl;
    }

   public:
    struct hash_pair {
        template <class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const {
            auto hash1 = hash<T1>{}(p.first);
            auto hash2 = hash<T2>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    vector<Point> getShortestPathFromSourceToDestination(bool matrix[][N], int N, Point start, Point end) {
        vector<Point> result;
        unordered_set<Point, hash_pair> set;

        queue<pair<Point, vector<Point>>> q;
        q.push({start, {start}});
        set.insert(start);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            if (u.first == end) return u.second;

            for (auto v : getChildren(u.first)) {
                if (set.find(v) == set.end() && matrix[v.x][v.y] == 1) {
                    auto p = u.second;
                    p.push_back(v);

                    q.push({v, p});
                    set.insert(v);
                }
            }
        }

        return {};
    }

    vector<Point> getChildren(Point u) {
        vector<Point> res;
        for (auto n : nb) {
            Point p = {u.x + n.x, u.y + n.y};
            if (valid(p)) res.push_back(p);
        }

        return res;
    }

    bool valid(Point p) {
        return p.x >= 0 && p.x >= 0 && p.y < N && p.y < N;
    }

   public:
    pair<Point, int> minDistByTogglingCell(bool matrix[][N], int N, Point start, Point end) {
        vector<vector<pair<int, int>>> distMatrix(N, vector<pair<int, int>>(N, {INT_MAX, INT_MAX}));
        // distance to all nodes from start point
        {
            queue<pair<Point, int>> q;
            q.push({start, 0});
            unordered_set<string> visited;
            visited.insert(start.to_string());

            while (!q.empty()) {
                auto u = q.front();
                q.pop();

                for (auto v : getChildren(u.first)) {
                    distMatrix[v.x][v.y].first = std::min(distMatrix[v.x][v.y].first, u.second + 1);
                    
                    if (visited.find(v.to_string()) == visited.end()) {
                        visited.insert(v.to_string());

                        if (matrix[v.x][v.y] == 1) {
                            q.push({v, u.second + 1});
                        }
                    }
                }
            }
        }

        // distance to all nodes from end point
        {
            queue<pair<Point, int>> q;
            q.push({end, 0});
            unordered_set<string> visited;
            visited.insert(end.to_string());

            while (!q.empty()) {
                auto u = q.front();
                q.pop();
                
                for (auto v : getChildren(u.first)) {
                    distMatrix[v.first][v.second].second = min(distMatrix[v.first][v.second].second, u.second + 1);
                    if (visited.find(to_string(v)) == visited.end()) {
                        visited.insert(to_string(v));

                        if (matrix[v.first][v.second] == 1) {
                            q.push({v, u.second + 1});
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
                    shorted = {i, j};
                }
            }
        }

        return {shorted, shortest};
    }

   public:
    int shortestPath(int matrix[][5], int N) {
        int** table = new int*[4];
        for (int i = 0; i < 4; i++) table[i] = new int[5];
        table[0][0] = matrix[0][0] == 0 ? 0 : INT_MAX;

        for (int i = 1; i < 4; i++) {
            if (!matrix[i][0])
                table[i][0] = table[i - 1][0] == INT_MAX ? INT_MAX : table[i - 1][0] + 1;
            else
                table[i][0] = INT_MAX;
        }
        for (int j = 1; j < 5; j++) {
            if (!matrix[0][j])
                table[0][j] = table[0][j - 1] == INT_MAX ? INT_MAX : table[0][j - 1] + 1;
            else
                table[0][j] = INT_MAX;
        }

        for (int i = 1; i < 4; i++) {
            for (int j = 1; j < 5; j++) {
                if (matrix[i][j] == 0) {
                    int curMin = min(table[i - 1][j], table[i][j - 1]);
                    if (i < 3) curMin = min(curMin, table[i + 1][j]);
                    if (j < 4) curMin = min(curMin, table[i][j + 1]);
                    table[i][j] = curMin == INT_MAX ? INT_MAX : 1 + curMin;
                } else {
                    table[i][j] = INT_MAX;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }

        return table[3][4];
    }
};