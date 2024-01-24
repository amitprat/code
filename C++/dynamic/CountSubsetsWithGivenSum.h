#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <mutex>
#include <cassert>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class CountSubsetsWithSum
{
public:
    struct Node {
        bool flag;
        vector<int> elements;
    };
    static void test()
    {
        CountSubsetsWithSum obj;
        int set[] = { 3, 34, 4, 12, 5, 2 };
        int sum = 30;

        for (int i = 5; i <= 5; i++) {
            int cnt = obj.CountSubsets(set, sizeof(set) / sizeof(int), i);
            cout << cnt << endl;
        }
    }

    int CountSubsets(int set[], int n, int sum)
    {
        vector<vector<Node>> memo(sum + 1, vector<Node>(n + 1));
        for (int s = 0; s <= sum; s++) {
            for (int e = 0; e <= n; e++) {
                if (s == 0) memo[s][e].flag = true;
                else if (e == 0) memo[s][e].flag = s == 0;
                else if (set[e - 1] > s) memo[s][e].flag = false;
                else ifAny(memo[s][e], memo[s - set[e - 1]], e - 1, set);
            }
        }

        for (int s = 1; s <= sum; s++) {
            cout << s << ":: ";
            for (int e = 0; e <= n; e++) {
                cout << memo[s][e].flag << " ";
            }
            cout << endl;
        }

        int cnt = 0;
        for (int i = 0; i <= n; i++) {
            if (memo[sum][i].flag) {
                cnt++;
                for (auto k : memo[sum][i].elements) cout << k << " ";
                cout << endl;
            }
        }
        return cnt;
    }

    void ifAny(Node& node, vector<Node> a, int n, int set[])
    {
        for (int i = 0; i <= n; i++) if (a[i].flag) {
            node.flag = true;
            node.elements.push_back(set[i - 1]);
            break;
        }
    }
};