#include "../header.h"

class PrintMatrixInSpiralOrder {
   public:
    static vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> result;
        if (matrix.empty() || matrix[0].empty()) return result;

        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j)
                result.push_back(matrix[top][j]);
            ++top;

            for (int i = top; i <= bottom; ++i)
                result.push_back(matrix[i][right]);
            --right;

            if (top <= bottom) {
                for (int j = right; j >= left; --j)
                    result.push_back(matrix[bottom][j]);
                --bottom;
            }

            if (left <= right) {
                for (int i = bottom; i >= top; --i)
                    result.push_back(matrix[i][left]);
                ++left;
            }
        }
        return result;
    }

   public:
    static void printSpiralMatrix(const vector<vector<int>>& matrix) {
        if (matrix.empty()) return;

        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            // Top row
            for (int j = left; j <= right; ++j)
                cout << matrix[top][j] << ' ';
            ++top;

            // Right column
            for (int i = top; i <= bottom; ++i)
                cout << matrix[i][right] << ' ';
            --right;

            // Bottom row
            if (top <= bottom) {
                for (int j = right; j >= left; --j)
                    cout << matrix[bottom][j] << ' ';
                --bottom;
            }

            // Left column
            if (left <= right) {
                for (int i = bottom; i >= top; --i)
                    cout << matrix[i][left] << ' ';
                ++left;
            }
        }

        cout << '\n';
    }

   private:
    static void printSquareSpiralMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int k = (n - 1) / 2;

        for (int layer = 0; layer <= k; layer++) {
            for (int i = layer; i < n - layer - 1; i++) {
                cout << mat[i][layer] << " ";
            }
            for (int j = layer; j < n - layer - 1; j++) {
                cout << mat[n - layer - 1][j] << " ";
            }
            for (int i = n - layer - 1; i > layer; i--) {
                cout << mat[i][n - layer - 1] << " ";
            }
            for (int j = n - layer - 1; j > layer; j--) {
                cout << mat[layer][j] << " ";
            }
        }
    }

   public:
    static vector<vector<int>> makeSquareSpiralMatrix(int n) {
        int layer = (n - 1) / 2;
        int s = 1;

        vector<vector<int>> result(n, vector<int>(n));

        for (int l = 0; l <= layer; l++) {
            // single entry
            if (l == 1 && n - l - 1 == 1) {
                result[l][l] = s++;
                break;
            }

            // first row
            for (int j = l; j < n - l - 1; j++) result[l][j] = s++;

            // last col
            for (int i = l; i < n - l - 1; i++) result[i][n - l - 1] = s++;

            // last row
            for (int j = n - l - 1; j > l; j--) result[n - l - 1][j] = s++;

            // first col
            for (int i = n - l - 1; i > l; i--) result[i][l] = s++;
        }

        return result;
    }

   public:
    static void test() {
        for (int i = 0; i < 5; i++) {
            cout << "Make square spiral matrix of size: " << i << endl;
            auto res = makeSquareSpiralMatrix(i);
            cout << res << endl;
        }

        vector<vector<vector<int>>> testCases = {
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},  // square 3x3
            {{1, 2, 3, 4}},                     // 1x4
            {{1}, {2}, {3}, {4}},               // 4x1
            {{1, 2}, {3, 4}},                   // 2x2
            {{1, 2, 3}, {4, 5, 6}},             // 2x3
            {{1, 2}, {3, 4}, {5, 6}},           // 3x2
            {}                                  // empty
        };

        for (const auto& matrix : testCases) {
            cout << "Matrix:\n";
            for (const auto& row : matrix) {
                for (int val : row) cout << val << ' ';
                cout << '\n';
            }
            cout << "Spiral Order: ";
            printSpiralMatrix(matrix);
            cout << "------\n";
        }
    }
};