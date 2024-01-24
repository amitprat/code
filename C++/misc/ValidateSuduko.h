#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <sstream>
#include <future>
using namespace std;

class ValidateSuduko {
public:
    static void test() {
        ValidateSuduko obj;
        vector<vector<char>> board = {
            {'.','1','3','.','.','8','.','2','5'},
            {'.','9','.','7','.','.','1','3','.'},
            {'5','.','6','.','.','.','9','.','.'},
            {'.','.','2','.','.','.','8','9','1'},
            {'8','.','1','6','.','.','5','.','3'},
            {'.','6','1','.','.','.','.','.','.'},
            {'1','2','8','.','.','.','3','.','.'},
            {'.','.','.','.','.','.','4','1','.'},
            {'9','3','.','.','.','.','2','8','7'},
        };
        cout << obj.isValidSudoku(board) << endl;
    }
    bool isValidSudoku(vector<vector<char>> board) {
        unordered_set<string> seen;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char number = board[i][j];
                if (number != '.') {
                    string key = to_string(number - '0') + " in row " + to_string(i);
                    if (!seen.insert(key).second) {
                        cout << "Failed to insert: " << key << endl;
                        return false;
                    }

                    key = to_string(number - '0') + " in column " + to_string(j);
                    if (!seen.insert(key).second) {
                        cout << "Failed to insert: " << key << endl;
                        return false;
                    }

                    key = to_string(number - '0') + " in block " + to_string(i / 3) + "-" + to_string(j / 3);
                    if (!seen.insert(key).second) {
                        cout << "Failed to insert: " << key << endl;
                        return false;
                    }
                }
            }
        }
        return true;
    }
};