#pragma once
#include "../header.h"
#include "../graph/MemoryEfficientTrie.h"
// TODO - fix me
class WordSearch2 {
private:
    MemoryEfficientTrie trie;

public:
    static void test() {
        WordSearch2 obj;
        vector<string> words = { "oath","pea","eat","rain" };
        vector<vector<char>> board = {
          {'o','a','a','n'},
          {'e','t','a','e'},
          {'i','h','k','r'},
          {'i','f','l','v'}
        };

        obj.preProcessBoard(words);
        auto res = obj.findWord(board);
        for (auto& word : res) cout << word << " ";
        cout << endl;
    }

    vector<string> findWord(vector<vector<char>>& board) {
        vector<string> result;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                dfs(board, i, j, result, string(board[i][j], 1));
            }
        }
        return result;
    }

private:
    void preProcessBoard(vector<string>& words) {
        for (auto& word : words) trie.insert(word);
    }

    void dfs(vector<vector<char>>& board, int i, int j, vector<string>& result, string prefix) {
        if (board[i][j] == '$') return;
        if (trie.startsWith(prefix).empty()) return;

        char tmp = board[i][j];
        board[i][j] = '$';

        if (trie.search(prefix)) result.push_back(prefix);

        for (auto& neighbour : getNeighbours(board, i, j)) {
            dfs(board, neighbour.first, neighbour.second, result, prefix + board[neighbour.first][neighbour.second]);
        }
        board[i][j] = tmp;
    }

    vector<pair<int, int>> getNeighbours(vector<vector<char>>& board, int i, int j) {
        vector<pair<int, int>> result;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (abs(x) != abs(y)) {
                    int dx = i + x;
                    int dy = j + y;
                    if (isValid(board, dx, dy)) result.push_back({ dx, dy });
                }
            }
        }

        return result;
    }

    bool isValid(vector<vector<char>>& board, int i, int j) {
        return i >= 0 && j >= 0 && i < board.size() && j < board[i].size();
    }
};