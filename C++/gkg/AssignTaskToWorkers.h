#pragma once
#include "../Header.h"

class AssignTask {
public:
    static void test() {
        AssignTask obj;
        vector<int> tasks = { 2,2,3,4,1,5,10 };
        int workers = 4;

        int res = obj.printAssignment1(tasks, workers);
        cout << "Min days = " << res << endl;
    }

    int printAssignment1(vector<int> tasks, int workers) {
        int mnDays = INT_MAX;
        vector<int> work(workers);
        findMinDiff(tasks, tasks.size(), workers, work, mnDays);

        return mnDays;
    }

    int printAssignment(vector<int> tasks, int workers) {
        int mnDays = INT_MAX;
        vector<vector<int>> result;
        result.resize(workers);
        printAssignment(tasks, workers, 0, mnDays, result);

        return mnDays;
    }

private:
    void printAssignment(vector<int> tasks, int workers, int index, int& mnDays, vector<vector<int>> result) {
        if (index == tasks.size()) {
            if (maxDays(result) < mnDays) {
                mnDays = maxDays(result);
                print(result);
            }
            return;
        }
        for (int i = 0; i < workers; i++) {
            result[i].push_back(tasks[index]);
            printAssignment(tasks, workers, index + 1, mnDays, result);
            result[i].pop_back();
        }
    }

    int maxDays(vector<vector<int>> result) {
        int mx = INT_MAX;
        for (auto e : result) {
            int cur = 0;
            for (auto i : e) cur += i;
            mx = max(mx, cur);
        }
        return mx;
    }

    void findMinDiff(vector<int> tasks, int n, int workers, vector<int> work, int& mnDays) {
        if (n == 0) {
            mnDays = min(mnDays, max(work));
            return;
        }
        for (int i = 0; i < workers; i++) {
            work[i] += tasks[n - 1];
            findMinDiff(tasks, n - 1, workers, work, mnDays);
            work[i] -= tasks[n - 1];
        }
    }
};