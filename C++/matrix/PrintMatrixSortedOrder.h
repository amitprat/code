#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class PrintMatrixSortedOrder {
private:
    static const int N = 4;
    static const int M = 4;
public:
    using Point = pair<int, int>;
    static void test() {
        PrintMatrixSortedOrder obj;
        int mat[N][N] = { {10, 20, 30, 40},
                          {15, 25, 35, 45},
                          {27, 29, 37, 48},
                          {32, 33, 39, 50},
        };
        obj.printSorted(mat);
        obj.spiral(mat);

        int a = 6, b = 7;
        char** matrix = new char* [a];
        for (int i = 0; i < a; i++) matrix[i] = new char[b];

        cout << endl;
        obj.fill(matrix, a, b);
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) cout << matrix[i][j] << " ";
            cout << endl;
        }
    }

    void spiral(int mat[][M])
    {
        int k = (N - 1) / 2;
        for (int layer = 0; layer <= k; layer++) {
            for (int i = layer; i < N - layer - 1; i++) {
                cout << mat[i][layer] << " ";
            }
            for (int j = layer; j < M - layer - 1; j++) {
                cout << mat[N - layer - 1][j] << " ";
            }
            for (int i = N - layer - 1; i > layer; i--) {
                cout << mat[i][M - layer - 1] << " ";
            }
            for (int j = M - layer - 1; j > layer; j--) {
                cout << mat[layer][j] << " ";
            }
        }
    }

    void fill(char** mat, int a, int b)
    {
        int k = (a - 1) / 2;
        char ch = 'X';
        for (int layer = 0; layer <= k; layer++) {
            for (int i = layer; i < a - layer - 1; i++) {
                mat[i][layer] = ch;
            }
            for (int j = layer; j < b - layer - 1; j++) {
                mat[a - layer - 1][j] = ch;
            }
            for (int i = a - layer - 1; i > layer; i--) {
                mat[i][b - layer - 1] = ch;
            }
            for (int j = b - layer - 1; j > layer; j--) {
                mat[layer][j] = ch;
            }

            ch = (ch == 'X' ? 'O' : 'X');
        }
    }

    void printSorted(int mat[][M])
    {
        int indices[N] = { 0 };
        int cnt = 0;
        while (cnt < N * M) {
            Point p = getMinIndex(indices, mat);
            cout << mat[p.first][p.second] << " ";
            cnt++;
        }
    }

    Point getMinIndex(int indices[], int mat[][M])
    {
        Point k = { 0,indices[0] };
        for (int i = 1; i < N; i++) {
            if (get(i, indices, mat) < get(k.first, indices, mat)) {
                k = { i, indices[i] };
            }
        }
        indices[k.first]++;

        return k;
    }

    int get(int i, int indices[], int mat[][M])
    {
        if (indices[i] >= M) return INT_MAX;
        return mat[i][indices[i]];
    }
};