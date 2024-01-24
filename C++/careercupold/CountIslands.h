#pragma once
#include "../Header.h"

class CountIslands {
public:
    static void test() {
        CountIslands obj;
        vector<vector<bool>> v = {
            {0,1,0,1,0},
            {1,0,1,0,1},
            {0,1,0,0,1},
            {1,1,1,0,1}
        };
        cout << obj.countIslands(v) << endl;
        cout << obj.countIslandsDP(v) << endl;
    }

    int countIslandsDP(vector<vector<bool>> v) {
        int count = 0;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                if (v[i][j]) {
                    if (i == 0 && j == 0) count++;
                    else if (i == 0) count += (v[i][j - 1] == 0);
                    else if (j == 0) count += (v[i - 1][j] == 0);
                    else if (v[i - 1][j] == 0 && v[i][j - 1] == 0) count++;
                }
            }
        }
        return count;
    }

    int countIslands(vector<vector<bool>> v) {
        int count = 0;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                if (v[i][j]) {
                    count++;
                    visit(v, i, j);
                }
            }
        }

        return count;
    }

    void visit(vector<vector<bool>>& v, int row, int col) {
        v[row][col] = 0;
        if (col + 1 < v[row].size() && v[row][col + 1]) visit(v, row, col + 1);
        if (row + 1 < v.size() && v[row + 1][col]) visit(v, row + 1, col);
    }
};