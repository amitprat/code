#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <functional>
#include <future>
using namespace std;

class ShortestPath
{
public:
    static void test()
    {
        ShortestPath obj;
        int N = 4;
        int matrix[][5] = {
            {0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {1, 1, 0, 1, 0},
            {1, 1, 1, 1, 0}
        };

        int length = obj.shortestPath(matrix, N);
        cout << "Shortest Path: " << length << endl;

        //int length = obj.shortestPathWithToggle(matrix, N, M);
        //cout << "Shortest Path With Toggle: " << length << endl;
    }

    int shortestPath(int matrix[][5], int N)
    {
        int** table = new int* [4];
        for (int i = 0; i < 4; i++) table[i] = new int[5];
        table[0][0] = matrix[0][0] == 0 ? 0 : INT_MAX;

        for (int i = 1; i < 4; i++) {
            if (!matrix[i][0]) table[i][0] = table[i - 1][0] == INT_MAX ? INT_MAX : table[i - 1][0] + 1;
            else table[i][0] = INT_MAX;
        }
        for (int j = 1; j < 5; j++) {
            if (!matrix[0][j]) table[0][j] = table[0][j - 1] == INT_MAX ? INT_MAX : table[0][j - 1] + 1;
            else table[0][j] = INT_MAX;
        }

        for (int i = 1; i < 4; i++) {
            for (int j = 1; j < 5; j++) {
                if (matrix[i][j] == 0) {
                    int curMin = min(table[i - 1][j], table[i][j - 1]);
                    if (i < 3) curMin = min(curMin, table[i + 1][j]);
                    if (j < 4) curMin = min(curMin, table[i][j + 1]);
                    table[i][j] = curMin == INT_MAX ? INT_MAX : 1 + curMin;
                }
                else {
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