#pragma once
#include "../Header.h"

class FindCommonElement {
public:
    static void test() {
        FindCommonElement obj;
        vector<vector<int>> mat = { {1, 2, 3, 4, 5},
                    {2, 3, 5, 8, 10},
                    {3, 5, 7, 9, 11},
                    {1, 3, 5, 7, 9},
        };

        obj.printCommon(mat);
    }

    void printCommon(vector<vector<int>> mat) {
        int n = mat.size();
        vector<int> indices(n, 0);
        while (true) {
            auto res = findMin(mat, indices);
            if (res.first == -1) break;

            if (res.second) {
                cout << mat[res.first][indices[res.first]] << " ";
                for (int i = 0; i < n; i++) indices[i]++;
            }
            else {
                indices[res.first]++;
            }
        }
    }

    pair<int, bool> findMin(vector<vector<int>>& mat, vector<int>& indices) {
        int eqCount = 1;
        pair<int, bool> res = { -1, false };
        for (int i = 0; i < indices.size(); i++) {
            if (indices[i] == mat[i].size()) break;
            if (res.first == -1) res.first = i;
            else {
                int x = indices[res.first];
                int y = indices[i];

                if (mat[res.first][x] == mat[i][y]) eqCount++;
                else if (mat[i][y] < mat[res.first][x]) res.first = i;
            }
        }
        if (res.first != -1) res.second = (eqCount == indices.size()) ? true : false;
        return res;
    }
};