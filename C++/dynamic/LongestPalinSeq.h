#pragma once
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <cassert>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

class LongestPalinSeq
{
public:
    static void test()
    {
        LongestPalinSeq lis;
        vector <string> contexts =
        { "GEEKS FOR GEEKS" };
        for (auto context : contexts)
        {
            cout << "Input:" << context << endl;
            auto res = lis.longestPalinSeqDP(context, 0, context.size() - 1);
            cout << "Result:" << res << endl;
        }
    }

    int longestPalinSeq(string str, int s, int e)
    {
        if (s > e) return 0;
        if (s == e) return 1;
        if (str[s] == str[e]) return 2 + longestPalinSeq(str, s + 1, e - 1);
        else return max(longestPalinSeq(str, s + 1, e), longestPalinSeq(str, s, e - 1));
    }

    int longestPalinSeqDP(string str, int s, int e)
    {
        int n = e - s + 1;
        int** table = new int* [n];
        for (int i = 0; i < n; i++) table[i] = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) table[i][j] = 1;
                else table[i][j] = 0;
            }
        }
        print(table, n);

        for (int cl = 2; cl < n; cl++) {
            for (int i = 0; i < n - cl + 1; i++) {
                int j = i + cl - 1;
                if (str[i] == str[j]) table[i][j] = 2 + table[i + 1][j - 1];
                else table[i][j] = max(table[i + 1][j], table[i][j - 1]);
            }
            print(table, n);
        }

        return table[n - 1][n - 1];
    }

    void print(int** table, int n) {
        cout << "-------------------------" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
        cout << "-------------------------" << endl << endl;
    }
};