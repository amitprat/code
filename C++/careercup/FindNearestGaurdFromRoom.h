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

class FindNearestGaurdFromRoom {
   public:
    static void test() {
        vector<vector<char>> mat = {
            {'0', '0', '0'},
            {'B', 'G', 'G'},
            {'B', '0', '0'}};

        FindNearestGaurdFromRoom obj;
        // vector<vector<int>> result = obj.findNearestRoom(mat);
        obj.findNearestRoom2(mat);

        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[i].size(); j++) {
                cout << setw(2) << (mat[i][j] == '0' ? 'G' : mat[i][j]) << " ";
            }
            cout << endl;
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

        while (!q.empty()) {
            auto pos = q.front();
            q.pop();

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j) &&
                        pos.first + i >= 0 && pos.first + i < mat.size() &&
                        pos.second + j >= 0 && pos.second + j < mat[0].size()) {
                        pair<int, int> cur = {pos.first + i, pos.second + j};

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

        while (!q.empty()) {
            auto pos = q.front();
            q.pop();

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j) &&
                        pos.first + i >= 0 && pos.first + i < mat.size() &&
                        pos.second + j >= 0 && pos.second + j < mat[0].size()) {
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
};