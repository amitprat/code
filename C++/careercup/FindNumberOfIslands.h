#include "../header.h"

class FindNumberOfIslands {
   public:
    static void test() {
        vector<vector<int>> matrix = {
            {1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1},
            {1, 0, 0, 1, 1},
            {0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1}};

        FindNumberOfIslands obj;
        cout << "Number of islands is: " << obj.countIslands(matrix);
    }

   private:
    int countIslands(vector<vector<int>> &matrix) {
        int n = matrix.size();
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        int islands = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1 && !visited[i][j]) {
                    dfs(matrix, i, j, visited);
                    islands++;
                }
            }
        }

        return islands;
    }

    void dfs(vector<vector<int>> &matrix, int r, int c, vector<vector<bool>> &visited) {
        visited[r][c] = true;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (!(i == 0 && j == 0)) {
                    int nr = r + i;
                    int nc = c + j;
                    if (safe(matrix, nr, nc, visited)) {
                        dfs(matrix, nr, nc, visited);
                    }
                }
            }
        }
    }

    bool safe(vector<vector<int>> &matrix, int r, int c, vector<vector<bool>> &visited) {
        if (r < 0 || c < 0)
            return false;
        if (r >= matrix.size() || c >= matrix.size())
            return false;
        if (visited[r][c])
            return false;
        if (matrix[r][c] == 0)
            return false;

        return true;
    }
};