#pragma once
#include "../Header.h"

class CommonElementInRowwiseSortedMatrix {
    struct Node {
        int x, y, e;
        Node(int x, int y, int e) :x(x), y(y), e(e) {}
    };
    struct compare {
        bool operator ()(const Node& f, const Node& s) {
            return f.e > s.e;
        }
    };
public:
    static void test() {
        vector<vector<int>> mat = {
        { 1, 2, 3, 4, 5 },
        { 2, 4, 5, 8, 10 },
        { 3, 5, 7, 9, 11 },
        { 1, 3, 5, 7, 9 },
        };
        int result = findCommonUsingPQ(mat);
        if (result == -1)
            cout << "No common element";
        else
            cout << "Common element is " << result;
    }

    static int findCommonUsingPQ(vector<vector<int>>& mat) {
        unordered_map<int, int> elem;
        priority_queue<Node, vector<Node>, compare> pq;
        for (int i = 0; i < mat.size(); i++) {
            pq.push({ i,0,mat[i][0] });
            elem[mat[i][0]]++;
        }

        while (!pq.empty()) {
            auto f = pq.top(); pq.pop();

            if (elem.size() == 1 && elem[mat[f.x][f.y]] == mat.size())
                return mat[f.x][f.y];

            elem.erase(mat[f.x][f.y]);

            if (f.y + 1 < mat[f.x].size()) {
                pq.push({ f.x,f.y + 1,mat[f.x][f.y + 1] });
                elem[mat[f.x][f.y + 1]]++;
            }
        }

        return INT_MAX;
    }

    static int findCommon(vector<vector<int>>& mat) {
        unordered_map<int, int> elem;
        vector<int> minPos(mat.size());
        for (int i = 0; i < mat.size(); i++) {
            minPos[i] = 0;
            elem[mat[i][0]]++;
        }

        while (true) {
            int minRow = getMinRow(minPos, mat);
            if (minRow == -1) break;

            int mnCol = minPos[minRow];
            elem.erase(mat[minRow][mnCol]);
            elem[mat[minRow][mnCol + 1]]++;
            if (elem.size() == 1 && elem[mat[minRow][mnCol + 1]] == mat.size())
                return mat[minRow][mnCol + 1];
            minPos[minRow] += 1;
        }

        return INT_MAX;
    }

    static int getMinRow(vector<int>& minPos, vector<vector<int>>& mat) {
        int mnElem = INT_MAX;
        int mnRow = -1;
        for (int i = 0; i < minPos.size(); i++) {
            int j = minPos[i];
            if (j < mat[i].size() && mat[i][j] < mnElem) {
                mnElem = mat[i][j];
                mnRow = i;
            }
        }

        return mnRow;
    }
};