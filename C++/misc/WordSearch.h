#pragma once
#include "../header.h"

class WordSearch {
private:
    unordered_map<char, vector<pair<int, int>>> map;

public:
    static void test() {
        WordSearch obj;
        vector<string> board = {
          {"ABCE"} ,
          {"SFCS"},
          {"ADEE"}
        };

        vector<string> tests = {
            "ABCCED", "SEE", "ABCB"
        };

        obj.preProcessBoard(board);
        for (auto& test : tests) {
            cout << obj.findWordWithPreprocessing(board, test) << endl;
        }
    }

    bool findWord(vector<string>& board, string& word) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == word[0] && dfs(board, word, i, j, 1)) return true;
            }
        }
        return false;
    }

    bool findWordWithPreprocessing(vector<string>& board, string& word) {
        int k = 0;
        pair<int, int> p = { -1,-1 };
        unordered_set<string> set;

        return findWordWithPreprocessing(board, word, k, p, set);
    }

private:
    bool dfs(vector<string>& board, string& word, int i, int j, int k) {
        if (k == word.size()) return true;
        char tmp = board[i][j];
        board[i][j] = '$';
        for (auto& neighbour : getNeighbours(board, i, j, word[k])) {
            if (dfs(board, word, neighbour.first, neighbour.second, k + 1)) {
                board[i][j] = tmp;
                return true;
            }
        }
        board[i][j] = tmp;
        return false;
    }

    vector<pair<int, int>> getNeighbours(vector<string>& board, int i, int j, char ch) {
        vector<pair<int, int>> result;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (abs(x) != abs(y)) {
                    int dx = i + x;
                    int dy = j + y;
                    if (isValid(board, dx, dy) && board[dx][dy] == ch) result.push_back({ dx, dy });
                }
            }
        }

        return result;
    }

    bool findWordWithPreprocessing(vector<string>& board, string& word, int k, pair<int, int> p, unordered_set<string>& set) {
        if (k == word.length()) return true;
        for (auto& pos : map[word[k]]) {
            if (isNeighbour(board, p, pos) && set.insert(to_string(pos)).second) {
                if (findWordWithPreprocessing(board, word, k + 1, pos, set)) return true;
            }
        }
        return false;
    }

    bool isNeighbour(vector<string>& board, pair<int, int> parent, pair<int, int> child) {
        if (parent.first == -1 && parent.second == -1) return true;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (abs(x) != abs(y)) {
                    int dx = x + parent.first;
                    int dy = y + parent.second;
                    if (isValid(board, dx, dy) && child.first == dx && child.second == dy) return true;
                }
            }
        }
        return false;
    }

    void preProcessBoard(vector<string>& board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                map[board[i][j]].push_back({ i,j });
            }
        }
    }

    bool isValid(vector<string>& board, int i, int j) {
        return i >= 0 && j >= 0 && i < board.size() && j < board[i].size();
    }

    string to_string(pair<int, int> p) {
        return "{" + std::to_string(p.first) + "," + std::to_string(p.second) + "}";
    }
};