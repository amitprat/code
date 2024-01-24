#include "../header.h"

/*
https://careercup.com/question?id=5653583535013888

Finding biggest plus sign "+" in a sparse matrix(matrix with elements 0 and 1)
For example, the biggest plus sign for following matrix is located at (2,2), with length 1 for each edge(Yes, each edge should have same length)
0 0 1 0 0 1 0
1 0 1 0 1 0 1
1 1 1 1 1 1 1
0 0 1 0 0 0 0
0 0 0 0 0 0 0

Hint: use DFS/BFS

https://careercup.com/question?id=5678853664014336
Given a binary N X N matrix, return the size of the largest '+' of ones.

input:
0 0 0 0
1 1 0 1
1 1 1 1
1 1 1 0

output:
5
*/
class LargestPlusSignInMatrix {
   public:
    static void test() {
        LargestPlusSignInMatrix obj;
        vector<vector<int>> matrix = {
            {0, 0, 1, 0, 0, 1, 0},
            {1, 0, 1, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0}};

        auto res = obj.biggestPlusSign2(matrix);
        cout << res << endl;
    }

   private:
    int biggestPlusSign(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<Point>> leftTop(n, vector<Point>(m));
        vector<vector<Point>> rightBottom(n, vector<Point>(m));

        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[i].size(); j++) {
                if (mat[i][j] == 0)
                    leftTop[i][j] = {0, 0};
                else if (i == 0 && j == 0)
                    leftTop[i][j] = {1, 1};
                else if (i == 0)
                    leftTop[i][j] = {1, 1 + leftTop[i][j - 1].y};
                else if (j == 0)
                    leftTop[i][j] = {1 + leftTop[i - 1][j].x, 1};
                else
                    leftTop[i][j] = {1 + leftTop[i - 1][j].x, 1 + leftTop[i][j - 1].y};
            }
        }

        for (int i = mat.size() - 1; i >= 0; i--) {
            for (int j = mat[i].size() - 1; j >= 0; j--) {
                if (mat[i][j] == 0)
                    rightBottom[i][j] = {0, 0};
                else if (i == mat.size() - 1 && j == mat[i].size() - 1)
                    rightBottom[i][j] = {1, 1};
                else if (i == mat.size() - 1)
                    rightBottom[i][j] = {1, 1 + rightBottom[i][j + 1].y};
                else if (j == mat[i].size() - 1)
                    rightBottom[i][j] = {1 + rightBottom[i + 1][j].x, 1};
                else
                    rightBottom[i][j] = {1 + rightBottom[i + 1][j].x, 1 + rightBottom[i][j + 1].y};
            }
        }

        int mx = 0;
        for (int i = mat.size() - 1; i >= 0; i--) {
            for (int j = mat[i].size() - 1; j >= 0; j--) {
                int maxX = 2 * min(leftTop[i][j].x, rightBottom[i][j].x) - 1;
                int maxY = 2 * min(leftTop[i][j].y, rightBottom[i][j].y) - 1;
                int curSize = min(maxX, maxY);

                mx = max(mx, curSize);
            }
        }

        return mx;
    }

   private:
    // another approach, from each 1 traverse in all 4 directions
    int biggestPlusSign2(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        int mx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j]) {
                    mx = max(mx, getMax(mat, i, j, n, m));
                }
            }
        }

        return mx;
    }

    int getMax(vector<vector<int>>& mat, int x, int y, int n, int m) {
        int up = 0, down = 0, left = 0, right = 0;
        int orgX = x;
        while (x >= 0 && mat[x--][y]) up++;

        x = orgX;
        while (x < n && mat[x++][y]) down++;

        x = orgX;
        int orgY = y;
        while (y >= 0 && mat[x][y--]) left++;

        y = orgY;
        while (y < m && mat[x][y++]) right++;

        return 1 + min(min(left, right), min(up, down));
    }
};