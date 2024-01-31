#pragma once
#include "../header.h"
/*
https://careercup.com/question?id=4716965625069568
Given a 2-D matrix represents the room, obstacle and guard like the following (0 is room, B->obstacle, G-> Guard):
0 0 0
B G G
B 0 0

calculate the steps from a room to nearest Guard and set the matrix, like this
2 1 1
B G G
B 1 1
Write the algorithm, with optimal solution.
*/
class FindNearestGuardFromRoom {
   public:
    static void test() {
        FindNearestGuardFromRoom obj;

        // using seperate visited matrix
        {
            cout << "Find location to nearest guard to room using seperate visited matrix." << endl;
            vector<vector<char>> input = {
                {'0', '0', '0'},
                {'B', 'G', 'G'},
                {'B', '0', '0'}};

            cout << input << endl;

            vector<vector<int>> result = obj.findNearestRoom(input);
            cout << result << endl;
        }

        // using input matrix to store the visited state (1)
        {
            cout << "Find location to nearest guard to room using same visited matrix." << endl;
            vector<vector<char>> input = {
                {'0', '0', '0'},
                {'B', 'G', 'G'},
                {'B', '0', '0'}};

            cout << input << endl;

            obj.findNearestRoom2(input);

            for (int i = 0; i < input.size(); i++) {
                for (int j = 0; j < input[i].size(); j++) {
                    cout << setw(2) << (input[i][j] == '0' ? 'G' : input[i][j]) << " ";
                }
                cout << endl;
            }
        }

        // using input matrix to store the visited state (2)
        {
            cout << "Find location to nearest guard to room using same visited matrix(2)." << endl;
            vector<vector<char>> input = {
                {'0', 'B', '0', '0'},
                {'0', '0', '0', 'B'},
                {'B', 'G', 'G', 'B'},
                {'B', '0', '0', '0'}};

            cout << input << endl;

            obj.populateNearestGaurdDistance(input);

            for (int i = 0; i < input.size(); i++) {
                for (int j = 0; j < input[i].size(); j++) {
                    cout << input[i][j] << " ";
                }
                cout << endl;
            }
        }
    }

   private:
    vector<vector<int>> findNearestRoom(vector<vector<char>> &mat) {
        queue<pair<int, int>> q;
        vector<vector<int>> result(mat.size(), vector<int>(mat[0].size()));

        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[i].size(); j++) {
                result[i][j] = -1;

                if (mat[i][j] == 'G') {
                    q.push({i, j});
                    result[i][j] = 0;
                }
            }
        }

        // do bfs. Update distance from nearest guard.
        while (!q.empty()) {
            auto pos = q.front();
            q.pop();

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j) &&
                        pos.first + i >= 0 && pos.first + i < mat.size() &&
                        pos.second + j >= 0 && pos.second + j < mat[0].size()) {
                        // next location
                        pair<int, int> cur = {pos.first + i, pos.second + j};

                        // if this location isn't already visited and its room location.
                        // We have only 'R' or 'G', so if it is guard position then skip it.
                        if (result[cur.first][cur.second] == -1 && mat[cur.first][cur.second] == '0') {
                            result[cur.first][cur.second] = result[pos.first][pos.second] + 1;
                            q.push({cur.first, cur.second});
                        }
                    }
                }
            }
        }

        return result;
    }

   private:
    void findNearestRoom2(vector<vector<char>> &mat) {
        queue<pair<int, int>> q;

        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[i].size(); j++) {
                if (mat[i][j] == 'G') {
                    q.push({i, j});
                    mat[i][j] = '0';
                } else if (mat[i][j] == '0') {
                    mat[i][j] = 'R';
                }
            }
        }

        // do bfs. Update distance from nearest guard.
        while (!q.empty()) {
            auto pos = q.front();
            q.pop();

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j) &&
                        pos.first + i >= 0 && pos.first + i < mat.size() &&
                        pos.second + j >= 0 && pos.second + j < mat[0].size()) {
                        // next location
                        pair<int, int> cur = {pos.first + i, pos.second + j};

                        if (mat[cur.first][cur.second] == 'R') {
                            mat[cur.first][cur.second] = mat[pos.first][pos.second] + 1;
                            q.push({cur.first, cur.second});
                        }
                    }
                }
            }
        }
    }

   private:
    void populateNearestGaurdDistance(vector<vector<char>> &input) {
        queue<pair<int, int>> q;
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].size(); j++) {
                if (input[i][j] == 'G') q.push({i, j});
            }
        }

        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();

            int curDistance = input[p.first][p.second] == 'G' ? 0 : input[p.first][p.second] - '0';
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j)) {
                        pair<int, int> tmp = {p.first + i, p.second + j};
                        if (isValid(input, tmp.first, tmp.second)) {
                            input[tmp.first][tmp.second] = '0' + curDistance + 1;
                            q.push(tmp);
                        }
                    }
                }
            }
        }
    }

    bool isValid(vector<vector<char>> input, int x, int y) {
        if (x < 0 || y < 0 || x >= input.size() || y >= input[0].size()) return false;
        if (input[x][y] == '0') return true;
        return false;
    }
};