#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=6282171643854848
There are at most eight servers in a data center. Each server has got a capacity/memory limit. There can be at most 8 tasks that need to be scheduled on those servers. Each task requires certain capacity/memory to run, and each server can handle multiple tasks as long as the capacity limit is not hit. Write a program to see if all of the given tasks can be scheduled or not on the servers?

Ex:
Servers capacity limits: 8, 16, 8, 32
Tasks capacity needs: 18, 4, 8, 4, 6, 6, 8, 8
For this example, the program should say 'true'.

Ex2:
Server capacity limits: 1, 3
Task capacity needs: 4
For this example, program should return false.

Got some idea that this needs to be solved using dynamic programming concept, but could not figure out exact solution.
*/

class ScheduleTaksOnGivenServers {
   public:
    static void test() {
        ScheduleTaksOnGivenServers obj;

        {
            vector<int> servers = {8, 16, 8, 32};
            vector<int> needs = {18, 4, 8, 4, 6, 6, 8, 8};
            bool res1 = obj.canBeArrangedRecursive(servers, needs);
            bool res2 = obj.canArrangeRecursiveUsingMemo(servers, needs);
            assert(res1 == res2);
            cout << "Result? " << res1 << endl;
        }

        {
            vector<int> servers = {1, 3};
            vector<int> needs = {4};
            bool res1 = obj.canBeArrangedRecursive(servers, needs);
            bool res2 = obj.canArrangeRecursiveUsingMemo(servers, needs);
            assert(res1 == res2);
            cout << "Result? " << res1 << endl;
        }
    }

    bool canBeArrangedRecursive(vector<int> servers, vector<int> needs) {
        int s = 0;
        return canBeArrangedRecursive(servers, needs, s);
    }

    bool canBeArrangedRecursive(vector<int>& servers, vector<int> needs, int s) {
        if (s == needs.size()) return true;

        for (auto& server : servers) {
            if (needs[s] <= server) {
                server -= needs[s];
                if (canBeArrangedRecursive(servers, needs, s + 1)) return true;
                server += needs[s];
            }
        }

        return false;
    }

    bool canArrangeRecursiveUsingMemo(vector<int> servers, vector<int> tasks) {
        vector<bool> used(tasks.size());
        return canArrangeRecursiveUsingMemo(servers, tasks, used);
    }

    bool canArrangeRecursiveUsingMemo(vector<int> servers, vector<int> tasks, vector<bool> used) {
        bool allUsed = true;
        for (bool b : used) {
            allUsed &= b;
        }
        if (allUsed) {
            return true;
        }
        for (int i = 0; i < tasks.size(); i++) {
            if (!used[i]) {
                used[i] = true;
                for (int j = 0; j < servers.size(); j++) {
                    if (servers[j] >= tasks[i]) {
                        servers[j] = servers[j] - tasks[i];
                        if (canArrangeRecursiveUsingMemo(servers, tasks, used)) {
                            return true;
                        }
                        servers[j] = servers[j] + tasks[i];
                    }
                }
                used[i] = false;
            }
        }
        return false;
    }
};