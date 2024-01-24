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

Got some idea that this needs to be solved using dynamic programming concept, but could not figure out exact solution.
*/

class AllocateTasks {
   public:
    bool canArrange(int servers[], int tasks[], int length) {
        bool *used = new bool[length];
        memset(used, false, length * sizeof(bool));

        return canArrangeRecursive(servers, tasks, used, length);
    }

   public:
    bool canArrangeRecursive(int servers[], int tasks[], bool used[], int length) {
        bool allUsed = true;
        for (int i = 0; i < length; i++) {
            allUsed &= used[i];
        }
        if (allUsed) return true;

        for (int i = 0; i < length; i++) {  // find an unassigned task
            if (!used[i]) {
                used[i] = true;
                for (int j = 0; j < length; j++) {  // find server with availability to place this task
                    if (servers[j] >= tasks[i]) {
                        servers[j] = servers[j] - tasks[i];
                        if (canArrangeRecursive(servers, tasks, used, length)) {
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

   public:
    bool canArrangeRecursive2(int servers[], int tasks[], bool used[], int length) {
        if (length == 0) return true;

        // find placement for last task on all servers if they have capacity
        for (int i = 0; i < length; i++) {
            if (servers[i] >= tasks[length]) {
                servers[i] -= tasks[length];
                if (canArrangeRecursive2(servers, tasks, used, length - 1)) return true;
                servers[i] += tasks[length];
            }
        }

        return false;
    }
};