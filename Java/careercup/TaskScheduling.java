package programs.careercup;

import com.google.gson.Gson;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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

public class TaskScheduling {
    public static void test() {
        TaskScheduling obj = new TaskScheduling();
        int[] tasks = new int[] {18, 4, 8, 4, 6, 6, 8, 8};
        int[] servers = new int[] {8, 16, 8, 32};

        Map<Integer, List<Integer>> result = new HashMap<>();
        boolean ans = obj.scheduleTasks(tasks, 0, servers, result);

        if(ans) {
            System.out.println((new Gson()).toJson(result));
        } else {
            System.out.println("Can't be scheduled.");
        }
    }

    private boolean scheduleTasks(int[] tasks, int index, int[] servers, Map<Integer, List<Integer>> result) {
        if(index == tasks.length) return true;

        for(int i=0;i<servers.length;i++) {
            if(tasks[index] <= servers[i]) {
                servers[i] -= tasks[index];
                if (!result.containsKey(i)) result.put(i, new ArrayList<>());
                result.get(i).add(tasks[index]);
                boolean curRes = scheduleTasks(tasks, index + 1, servers, result);
                if (curRes) return true;
                servers[i] += tasks[index];
                result.get(i).remove(result.get(i).size() - 1);
            }
        }

        return false;
    }
}
