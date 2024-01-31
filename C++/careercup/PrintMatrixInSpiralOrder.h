#include "../Header.h"

class PrintMatrixInSpiralOrder {
   public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int left = 0, right = matrix[0].size() - 1;
        int top = 0, bot = matrix.size() - 1;
        while (true) {
            if (left > right || top > bot)
                break;
            if (left == right) {
                for (int i = top; i <= bot; i++)
                    ans.push_back(matrix[i][left]);
                break;
            }
            if (top == bot) {
                for (int i = left; i <= right; i++)
                    ans.push_back(matrix[top][i]);
                break;
            }
            for (int i = left; i <= right; i++) {
                ans.push_back(matrix[top][i]);
            }
            for (int i = top + 1; i <= bot; i++) {
                ans.push_back(matrix[i][right]);
            }
            for (int i = right - 1; i >= left; i--) {
                ans.push_back(matrix[bot][i]);
            }
            for (int i = bot - 1; i >= top + 1; i--) {
                ans.push_back(matrix[i][left]);
            }
            left++, right--;
            top++, bot--;
        }
        return ans;
    }

   public:
    void spiralOrder2(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        int i = 0, j = 0;
        while (i < n && j < m) {
            // first row (left->right)
            for (int k = j; k < m; k++) cout << matrix[i][k] << " ";
            i++;

            // last column
            for (int k = i; k < n - 1; k++) cout << matrix[k][m - 1] << " ";
            m--;

            // last row
            if (j < m) {
                for (int k = n - 1; k >= j; k--) cout << matrix[n - 1][k] << " ";
                n--;
            }

            // first column
            if (i < n) {
                for (int k = n - 1; k >= i; k--) cout < matrix[k][j] << " ";
                j++;
            }
        }
    }

   private:
    void spiral(vector<vector<int>>& mat) {
        int N = mat.size();
        int k = (N - 1) / 2;

        for (int layer = 0; layer <= k; layer++) {
            for (int i = layer; i < N - layer - 1; i++) {
                cout << mat[i][layer] << " ";
            }
            for (int j = layer; j < N - layer - 1; j++) {
                cout << mat[N - layer - 1][j] << " ";
            }
            for (int i = N - layer - 1; i > layer; i--) {
                cout << mat[i][N - layer - 1] << " ";
            }
            for (int j = N - layer - 1; j > layer; j--) {
                cout << mat[layer][j] << " ";
            }
        }
    }
};