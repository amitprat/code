#include "../header.h"

class CheckWordExistsInBoard {
   public:
    static void test() {
        CheckWordExistsInBoard obj;
        {
            vector<vector<char>> board = {
                {'A', 'B', 'C', 'E'},
                {'S', 'F', 'C', 'S'},
                {'A', 'D', 'E', 'E'}};

            string word = "ABCCED";

            auto res = obj.isExists(board, word);
            cout << "word exists: " << res << endl;
        }
        {
            vector<vector<char>> board = {
                {'S', 'M', 'E', 'F'},
                {'R', 'A', 'T', 'D'},
                {'L', 'O', 'N', 'I'},
                {'K', 'A', 'F', 'B'}};

            vector<string> words = {"STAR", "TONE", "NOTE", "SAND"};
            for (auto& word : words) {
                auto res = obj.isExists(board, word);
                cout << "word exists: " << res << endl;
            }
        }
    }

   private:
    bool isExists(vector<vector<char>>& board, string& word) {
        if (word.empty()) return true;
        if (board.empty()) return false;

        int n = board.size();
        int m = board[0].size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == word[0] && dfs(board, i, j, word, 0)) return true;
            }
        }

        return false;
    }

    bool dfs(vector<vector<char>>& board, int x, int y, string& word, int pos) {
        if (pos == word.size() - 1) return true;
        if (pos >= word.size()) return false;

        char tmp = board[x][y];
        board[x][y] = '#';

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (!(i == 0 && j == 0)) {
                    int nr = x + i;
                    int nc = y + j;
                    bool found = isValid(board, nr, nc, word[pos + 1]) && dfs(board, nr, nc, word, pos + 1);
                    if (found) {
                        board[x][y] = tmp;
                        return true;
                    }
                }
            }
        }

        board[x][y] = tmp;

        return false;
    }

    bool isValid(vector<vector<char>>& board, int x, int y, char ch) {
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size()) return false;
        return board[x][y] == ch;
    }

   private:
    bool isExistsOptimized(vector<vector<char>>& board, string& word) {
        if (word.empty()) return true;
        if (board.empty()) return false;

        unordered_map<char, vector<Point>> map = preprocess(board, word);
        auto startPositions = map[word[0]];
        for (auto startPos : startPositions) {
            if (searchWord(board, startPos, map, word, 0)) return true;
        }

        return false;
    }

    bool searchWord(vector<vector<char>>& board, Point startPos, unordered_map<char, vector<Point>>& map, string& word, int pos) {
        if (pos == word.size() - 1) return true;
        if (pos >= word.size()) return false;

        char tmp = board[startPos.x][startPos.y];
        board[startPos.x][startPos.y] = '#';

        bool found = false;
        auto neighbours = getNeighbours(board, startPos, map[word[pos + 1]]);
        for (auto& n : neighbours) {
            found = searchWord(baord, n, map, word, pos + 1);
            if (found) break;
        }

        board[startPos.x][startPos.y] = tmp;

        return found;
    }

    unordered_map<char, vector<Point>> preprocess(vector<vector<char>>& board) {
        unordered_map<char, vector<Point>> map;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                map[board[i][j]].push_back({i, j});
            }
        }

        return map;
    }
};