#pragma once
#include "../Header.h"

class EditDistanceBetween2Arr {
public:
    static void test() {
        vector<int> arr1 = { 1,3,4,2,5,6 };
        vector<int> arr2 = { 3,4,6,5,7 };

        int n = arr1.size(), m = arr2.size();
        int dist = editDistanceRec(arr1, n, arr2, m);
        cout << "Distance = " << dist << endl;
    }

    static int editDistanceRec(vector<int>& arr1, int n, vector<int>& arr2, int m) {
        if (n == 0) return m;
        if (m == 0) return n;
        if (arr1[n - 1] == arr2[m - 1]) return editDistanceRec(arr1, n - 1, arr2, m - 1);
        else return 1 + min(editDistanceRec(arr1, n - 1, arr2, m), editDistanceRec(arr1, n, arr2, m - 1));
    }

    static int editDistance(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        int m = arr2.size();
        vector<vector<int>> table(n + 1, vector<int>(m + 1));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) table[i][j] = 0;
                else if (i == 0) table[i][j] = table[i][j - 1] + 1;
                else if (j == 0) table[i][j] = table[i - 1][j] + 1;
                else {
                    if (arr1[i - 1] == arr2[j - 1]) table[i][j] = table[i - 1][j - 1];
                    else table[i][j] = min(table[i - 1][j], table[i][j - 1]) + 1;
                }
            }
        }

        return table[n][m];
    }
};