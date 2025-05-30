/*
Write code to rotate a square matrix:
Input:
1 2 3
4 5 6
7 8 9

Output:
4 1 2
7 5 3
8 9 6
*/

#include <iostream>

using namespace std;
const int N = 3;

void cyclicRotate(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
void rotate(int a[][N]) {
    for (int layer = 0; layer < N / 2; layer++) {
        int j = layer;

        int tmp = a[layer][j];

        // top row
        int i = layer;
        for (j = layer + 1; j < N - layer; j++) {
            cyclicRotate(a[i][j], tmp);
        }

        // right column
        j = N - layer - 1;
        for (i = layer + 1; i < N - layer; i++) {
            cyclicRotate(a[i][j], tmp);
        }

        // bottom row
        i = N - layer - 1;
        for (j = N - layer - 2; j >= 0; j--) {
            cyclicRotate(a[i][j], tmp);
        }

        // left column
        j = layer;
        for (i = N - layer - 2; i >= 0; i--) {
            cyclicRotate(a[i][j], tmp);
        }
    }
}
/*
void rotate(int** m, int n)
{
        for (auto l = n; l > 1; l-=2) // l is the layer number: e.g. 5,3... 4,2
        {
                auto v = m[l-1][l-1];
                for (auto j = l-2; j >= n-l; --j) // bottom row
                {
                        auto v_tmp = m[l-1][j];
                        m[l-1][j] = v;
                        v = v_tmp;
                }
                for (auto i = l-2; i >= n-l; --i) // left col
                {
                        auto v_tmp = m[i][n-l];
                        m[i][n-l] = v;
                        v = v_tmp;
                }
                for (auto j = n-l+1; j <= l-1; ++j) // top row
                {
                        auto v_tmp = m[n-l][j];
                        m[n-l][j] = v;
                        v = v_tmp;
                }
                for (auto i = n-l+1; i <= l-1; ++i) // right col
                {
                        auto v_tmp = m[i][l-1];
                        m[i][l-1] = v;
                        v = v_tmp;
                }
        }
}
*/
int main() {
    int a[][N] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    rotate(a);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
