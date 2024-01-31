#pragma once
#include "../header.h"

/*
https://careercup.com/question?id=5661939564806144

Give a N*N matrix, print it out diagonally.
Follow up, if it is a M*N matrix, how to print it out.
Example:
1 2 3
4 5 6
7 8 9
print:
1
2 4
3 5 7
6 8
9
*/
class PrintMatrixDiagonally {
   public:
    static void test() {
        PrintMatrixDiagonally obj;

        vector<vector<vector<int>>> inputs = {
            {{1}},
            {{1, 2}, {4, 5}},
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};

        for (auto& input : inputs) {
            cout << "Print matrix diagonally for:" << endl;
            cout << input << endl;

            cout << "printDiags1:" << endl;
            obj.printDiags1(input);
            cout << endl;

            cout << "printDiags1:" << endl;
            obj.printDiags2(input);
            cout << endl;
        }
    }

   private:
    void printDiags1(const vector<vector<int>>& arr) {
        int N = arr.size();
        for (int d = 0; d <= 2 * (N - 1); d++) {
            for (int i = 0; i <= d; i++) {
                if (i < N && d - i < N) {
                    cout << arr[i][d - i] << " ";
                }
            }
            cout << endl;
        }
    }

    void printDiags2(const vector<vector<int>>& arr) {
        int n = arr.size();
        Point start = {0, 0};

        do {
            auto tmp = start;
            while (tmp.x < n && tmp.y >= 0) {
                cout << arr[tmp.x][tmp.y] << " ";
                tmp.x++;
                tmp.y--;
            }
            cout << endl;

            if (start.y == n - 1)
                start.x++;
            else
                start.y++;

        } while (start.x < n);
    }
};
