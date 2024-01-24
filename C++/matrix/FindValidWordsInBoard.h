#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <algorithm>
#include "MemoryEfficientTrie.h"
using namespace std;

class FindValidWords
{
public:
    static void test()
    {
        FindValidWords obj;
        vector<vector<char>> board =
        {
                {'o', 'a', 'a', 'n'},
                {'e', 't', 'a', 'e'},
                {'i', 'h', 'k', 'r'},
                {'i', 'f', 'l', 'v'}
        };
        vector<string> words = { "valid", "set", "of", "words", "oath", "pea", "eat", "rain","abondon","ability","hello","hi","this","that","what","is" };

        auto result = obj.findWords(board, words);
        cout << "Words present in board: ";
        for (auto& s : result) cout << s << " ";
        cout << endl;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
    {
        vector<string> result;
        MemoryEfficientTrie trie;
        for (auto& word : words) trie.insert(word);

        int n = board.size();
        int m = board[0].size();
        unordered_set<string> visited;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dfs(board, i, j, result, "", trie, visited);
            }
        }

        return result;
    }

private:
    void dfs(vector<vector<char>>& board, int i, int j, vector<string>& result, string cur, MemoryEfficientTrie& trie, unordered_set<string>& visited)
    {
        int n = board.size();
        int m = board[0].size();
        visited.insert(key(i, j));

        cur += board[i][j];
        if (trie.startsWith(cur).empty()) return;
        if (trie.search(cur)) { result.push_back(cur); }

        for (auto& neighbour : getNeighbours(board, i, j, visited))
        {
            dfs(board, neighbour.first, neighbour.second, result, cur, trie, visited);
        }
    }

    vector<pair<int, int>> getNeighbours(vector<vector<char>>& board, int row, int col, unordered_set<string>& visited)
    {
        vector<pair<int, int>> result;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) != abs(j)) {
                    int ni = row + i;
                    int nc = col + j;
                    if (ni >= 0 && ni < board.size() && nc >= 0 && nc < board[0].size() && (visited.find(key(i, j)) == visited.end())) {
                        result.push_back({ ni,nc });
                    }
                }
            }
        }

        return result;
    }

    string key(int i, int j)
    {
        return "{" + to_string(i) + "," + to_string(j) + "}";
    }
};