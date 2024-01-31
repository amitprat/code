#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=6282171643854848

There are at most eight servers in a data center. Each server has got a capacity/memory limit. There can be at most 8 tasks that need to be scheduled on those servers. Each task requires certain capacity/memory to run, and each server can handle multiple tasks as long as the capacity limit is not hit. Write a program to see if all of the given tasks can be scheduled or not on the servers?

Ex:
Servers capacity limits: 8, 16, 8, 32
Tasks capacity needs: 18, 4, 8, 4, 6, 6, 8, 8
For this example, the program should say 'true'.

Ex2:
Server capacity limits: 1, 3
Task capacity needs: 4
For this example, program should return false.
*/
class AllocateTasksOnGivenServers {
   public:
    static void test() {
        AllocateTasksOnGivenServers obj;

        {
            vector<int> servers = {8, 16, 8, 32};
            vector<int> tasks = {18, 4, 8, 4, 6, 6, 8, 8};
            auto result1 = obj.canArrange1(servers, tasks);
            auto result2 = obj.canArrange2(servers, tasks);
            assert(result1 == result2);

            cout << format("Can rearrange tasks={} in servers={}, result={}", to_string(tasks), to_string(servers), result1) << endl;
        }

        {
            vector<int> servers = {1, 3};
            vector<int> tasks = {4};
            auto result1 = obj.canArrange1(servers, tasks);
            auto result2 = obj.canArrange2(servers, tasks);
            assert(result1 == result2);

            cout << format("Can rearrange tasks={} in servers={}, result={}", to_string(tasks), to_string(servers), result1) << endl;
        }
    }

   public:
    bool canArrange1(vector<int> servers, vector<int> tasks) {
        int length = tasks.size();
        vector<bool> used(length, false);

        return canArrangeRecursive1(servers, tasks, used);
    }

    bool canArrangeRecursive1(vector<int>& servers, vector<int>& tasks, vector<bool>& used) {
        bool allUsed = true;
        for (int i = 0; i < tasks.size(); i++) {
            allUsed &= used[i];
        }
        if (allUsed) return true;

        for (int i = 0; i < tasks.size(); i++) {  // find an unassigned task
            if (!used[i]) {
                used[i] = true;
                for (int j = 0; j < servers.size(); j++) {  // find server with availability to place this task
                    if (servers[j] >= tasks[i]) {
                        servers[j] = servers[j] - tasks[i];
                        if (canArrangeRecursive1(servers, tasks, used)) {
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

   private:
    bool canArrange2(vector<int> servers, vector<int> tasks) {
        return canArrangeRecursive2(servers, tasks, tasks.size());
    }

    bool canArrangeRecursive2(vector<int>& servers, vector<int>& tasks, int length) {
        if (length == 0) return true;

        // find placement for last task on all servers if they have capacity
        for (auto& server : servers) {
            if (server >= tasks[length]) {
                server -= tasks[length];
                if (canArrangeRecursive2(servers, tasks, length - 1)) return true;
                server += tasks[length];
            }
        }

        return false;
    }
};