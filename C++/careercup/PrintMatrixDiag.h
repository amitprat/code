#pragma once
#include "../Header.h"

/*
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

This is the question in the phone interview.
Please share more questions.
*/

class PrintMatrixDiag {
public:
    static void test() {
        PrintMatrixDiag obj;

        {
            vector<vector<int>> arr = {
                {1}
            };

            obj.printDiags(arr);
            obj.printDiags2(arr);
        }
        cout << endl;

        {
            vector<vector<int>> arr = {
                {1, 2},
                {4, 5}
            };

            obj.printDiags(arr);
            obj.printDiags2(arr);
        }
        cout << endl;

        {
            vector<vector<int>> arr = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            };

            obj.printDiags(arr);
            obj.printDiags2(arr);
        }
    }

    void printDiags(vector<vector<int>> arr) {
        int N = arr.size();
        for (int d = 0; d <= 2 * (N - 1); d++) {
            for (int i = 0; i <= d; i++) {
                if (i < N && (d - i) < N) {
                    cout << arr[i][d - i] << " ";
                }
            }
            cout << endl;
        }
    }

    void printDiags2(vector<vector<int>> arr) {
        int n = arr.size();
        Point start = { 0,0 };

        do {
            auto tmp = start;
            while (tmp.x < n && tmp.y >= 0) {
                cout << arr[tmp.x][tmp.y] << " ";
                tmp.x++; tmp.y--;
            }
            cout << endl;

            if (start.y == n - 1) start.x++;
            else start.y++;
        } while (start.x < n);
    }
};

/*
let i be row number (0 to N-1), and j be col number (O to N-1)

diagonal 1 has i+j =0
diagonal 2 has i+j =1
...


So define D = i+j

Loop with D from 0 to 2*(N-1)

Now if D = i+j then j=D-i
So we have reduced the problem to two variables: D and i (two loops)


for D from 0 to 2*(N-1)
{
   for i from 0 to D
       print(A[i][D-i])

  println();
}
Check for bugs. And thanks for posting this fun question.
You can think of the MxN case

for(int D=0;D<=2*(N-1);D++) {
            for (int i=0;i<=D;i++) {
                if(i<N && (D-i)<N)
                System.out.print(a[i][D-i]);
            }
            System.out.println();
        }
*/