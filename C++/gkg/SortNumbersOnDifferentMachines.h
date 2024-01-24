#pragma once
#include "../Header.h"

class SortNumbersOnDifferentMachines {
    class Machine {
        vector<int> l;
        string id;
    public:
        Machine(string id) :id(id) {}
        void add(int num) {
            cout << "Pushing num " << num << " to machine " << id << endl;
            l.push_back(num);
        }
        void sortList() {
            sort(l.begin(), l.end());
        }
        bool hasNext() {
            return !l.empty();
        }
        int next() {
            auto num = *l.begin();
            cout << "Popping num " << num << " from machine " << id << endl;

            l.erase(l.begin());

            return num;
        }
        int size() {
            return l.size();
        }
    };
public:
    static void test() {
        srand(time(nullptr));
        vector<Machine> machines;
        machines.push_back(Machine("First"));
        machines.push_back(Machine("Second"));
        machines.push_back(Machine("Third"));
        for (auto& machine : machines) {
            int l = rand() % 10;
            for (int i = 0; i < l; i++) {
                machine.add(rand() % 100);
            }
            machine.sortList();
        }
        cout << endl;

        printSorted(machines);
    }

    static void printSorted(vector<Machine> machines) {
        vector<int> result;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int total = 0;
        for (int i = 0; i < machines.size(); i++) {
            total += machines[i].size();
            if (machines[i].hasNext()) {
                pq.push({ machines[i].next(), i });
            }
        }

        bool done = false;
        while (!pq.empty()) {
            pair<int, int> f = pq.top(); pq.pop();
            result.push_back(f.first);

            if (machines[f.second].hasNext()) {
                pq.push({ machines[f.second].next(), f.second });
            }
        }
        cout << "\n Result: ";
        cout << result << endl;

        assert(result.size() == total);
    }
};