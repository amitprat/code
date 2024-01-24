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
#include <functional>
#include <future>
using namespace std;

class PossiblePermutations
{
public:
    static void test()
    {
        PossiblePermutations obj;
        vector<pair<string, string>> inputs{
            {"ab","de"}
        };

        for (auto input : inputs) {
            vector<string> out = obj.possiblePermutations(input.first, input.second);
            for (auto sub : out) {
                cout << sub << " ";
            }
            cout << endl;
        }
    }

    vector<string> possiblePermutations(string first, string second)
    {
        vector<string> res;
        possiblePermutations(first, 0, second, 0, "", res);

        return res;
    }

    void possiblePermutations(string first, int i, string second, int j, string cur, vector<string>& res)
    {
        if (i == first.size() && j == second.size()) {
            res.push_back(cur);
        }
        if (i > first.size() && j > second.size()) return;

        if (i < first.size()) possiblePermutations(first, i + 1, second, j, cur + first[i], res);
        if (j < second.size()) possiblePermutations(first, i, second, j + 1, cur + second[j], res);
    }
};