#pragma once
#include "../Header.h"

class CountIslands {
public:
    static void test() {
        vector<vector<char>> mat = {
            {'O', 'O', 'O'},
                      {'X', 'X', 'O'},
                      {'X', 'X', 'O'},
                      {'O', 'O', 'X'},
                      {'O', 'O', 'X'},
                      {'X', 'X', 'O'}
        };
        cout << "Number of rectangular islands is "
            << countIslands(mat);
    }

    static int countIslands(vector<vector<char>> mat) {
        int n = mat.size();
        int m = mat[0].size();
        int cnt = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 'X') {
                    if ((i == 0 || mat[i - 1][j] == 'O') &&
                        (j == 0 || mat[i][j - 1] == 'O')) {
                        cnt++;
                    }
                }
            }
        }

        return cnt;
    }
};