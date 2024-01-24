#pragma once
#include "../Header.h"

class EmployessUnderEachManager {
public:
    static void test() {
        unordered_map<string, string> emps = {
            { "A", "C" },
            { "B", "C" },
            { "C", "F" },
            { "D", "E" },
            { "E", "F" },
            { "F", "F" }
        };

        printEmployeesUnderManager2(emps);
    }

    static void printEmployeesUnderManager2(unordered_map<string, string>& emps) {
        unordered_map<string, vector<string>> empMap;
        for (auto emp : emps) {
            if (emp.first != emp.second)
                empMap[emp.second].push_back(emp.first);
        }

        for (auto e : emps) {
            unordered_set<string> visited;
            print2(empMap, e.first, visited);
        }

        for (auto e : empMap) {
            cout << e.first << ":";
            for (auto v : e.second) cout << v << " ";
            cout << endl;
        }
    }

    static void print2(unordered_map<string, vector<string>>& empMap, string e, unordered_set<string>& visited) {
        if (visited.find(e) != visited.end()) return;
        visited.insert(e);
        if (empMap.count(e) == 0) {
            empMap[e] = {};
            return;
        }

        for (auto v : empMap[e]) {
            if (visited.find(v) == visited.end()) {
                print2(empMap, v, visited);
                for (auto q : empMap[v]) empMap[e].push_back(q);
            }
        }
    }

    static void printEmployeesUnderManager(unordered_map<string, string>& emps) {
        unordered_map<string, vector<string>> empMap;
        unordered_set<string> allEmps;
        for (auto emp : emps) {
            empMap[emp.second].push_back(emp.first);
            allEmps.insert(emp.first);
            allEmps.insert(emp.second);
        }

        for (auto e : allEmps) {
            cout << e << ":";
            unordered_set<string> visited;
            print(empMap, e, visited);
            cout << endl;
        }
    }

    static void print(unordered_map<string, vector<string>>& empMap, string e, unordered_set<string>& visited) {
        if (empMap.count(e) == 0) return;
        visited.insert(e);

        for (auto v : empMap[e]) {
            if (visited.count(v) == 0) {
                cout << v << " ";
                print(empMap, v, visited);
            }
        }
    }
};