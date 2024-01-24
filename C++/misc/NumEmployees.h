#pragma once
#include "../header.h"

class NumEmployees {
public:
    static void test() {
        NumEmployees obj;
        unordered_map<string, string> dataSet;
        dataSet.insert({ "A", "C" });
        dataSet.insert({ "B", "C" });
        dataSet.insert({ "C", "E" });
        dataSet.insert({ "D", "E" });
        dataSet.insert({ "E", "F" });
        dataSet.insert({ "F", "F" });

        unordered_map<string, vector<string>> result = obj.count(dataSet);
        for (auto e : result) {
            cout << e.first << ": ";
            for (auto i : e.second) {
                cout << i << " ";
            }
            cout << endl;
        }
    }

    unordered_map < string, vector<string>> count(unordered_map<string, string> dataSet) {
        unordered_map<string, vector<string>> partResult;
        for (auto e : dataSet) {
            if (e.first != e.second) {
                partResult[e.second].push_back(e.first);
            }
        }

        unordered_map<string, vector<string>> result;
        for (auto e : partResult) {
            unordered_set<string> visited;
            auto employees = expand(partResult, e.second, visited);
            result.insert({ e.first, employees });
        }

        return result;
    }

    vector<string> expand(unordered_map<string, vector<string>> partResult, vector<string> cur, unordered_set<string>& visited) {
        vector<string> next;
        for (auto e : cur) {
            if (visited.find(e) == visited.end()) {
                visited.insert(e);
                if (partResult.find(e) != partResult.end()) {
                    next.insert(next.end(), partResult[e].begin(), partResult[e].end());
                }
            }
        }
        if (next.empty()) return cur;
        return expand(partResult, next, visited);
    }
};