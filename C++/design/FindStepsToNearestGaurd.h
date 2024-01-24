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
#include <map>
using namespace std;

class FindStepsToNearestGaurd
{
public:
    static void test()
    {
        FindStepsToNearestGaurd obj;
        vector<vector<char>> input = {
            {'0','B','0', '0'},
            {'0','0','0', 'B'},
            {'B','G','G', 'B'},
            {'B','0','0', '0'}
        };
        obj.populateNearestGaurdDistance(input);

        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].size(); j++) {
                cout << input[i][j] << " ";
            }
            cout << endl;
        }
    }

    void populateNearestGaurdDistance(vector<vector<char>>& input)
    {
        queue<pair<int, int>> q;
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].size(); j++) {
                if (input[i][j] == 'G') q.push({ i,j });
            }
        }

        while (!q.empty()) {
            pair<int, int> p = q.front(); q.pop();
            int curDistance = input[p.first][p.second] == 'G' ? 0 : input[p.first][p.second] - '0';
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i) != abs(j)) {
                        pair<int, int> tmp = { p.first + i, p.second + j };
                        if (isValid(input, tmp.first, tmp.second)) {
                            input[tmp.first][tmp.second] = '0' + curDistance + 1;
                            q.push(tmp);
                        }
                    }
                }
            }
        }
    }

    bool isValid(vector<vector<char>> input, int x, int y) {
        if (x < 0 || y < 0 || x >= input.size() || y >= input[0].size()) return false;
        if (input[x][y] == '0') return true;
        return false;
    }
};