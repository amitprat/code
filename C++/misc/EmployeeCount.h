#pragma once
#include "../Header.h"

class EmployeeCount {
public:
    static void test() {
        EmployeeCount obj;
        vector<pair<string, string>> emps = {
            { "A", "C" },
            { "B", "C" },
            { "C", "F" },
            { "D", "E" },
            { "E", "F" },
            { "F", "F" }
        };
        obj.printEmpCount(emps);
    }

    void printEmpCount(vector<pair<string, string>>& emps) {
        unordered_map<string, vector<string>> empMap;
        for (auto emp : emps) {
            if (emp.first != emp.second) {
                empMap[emp.second].push_back(emp.first);
            }
        }

        unordered_map<string, int> counts;
        for (auto emp : emps) {
            counts[emp.first] = getCount(emp.first, empMap);
        }

        print("Employee Count", counts);
    }

    int getCount(string emp, unordered_map<string, vector<string>> empMap) {
        int count = 0;
        vector<string> tmp = { emp };
        while (!tmp.empty()) {
            auto cur = tmp.back();
            tmp.pop_back();
            if (empMap.find(cur) != empMap.end()) {
                count += empMap[cur].size();
                tmp.insert(tmp.end(), empMap[cur].begin(), empMap[cur].end());
            }
        }
        return count;
    }
};