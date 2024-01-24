package programs.misc;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class TaskScheduler {
    public static void test() {
        TaskScheduler obj = new TaskScheduler();

        {
            int[] servers = {8, 16, 8, 32};
            int[] tasks = {18, 4, 8, 4, 6, 6, 8, 8};

            Map<Integer, Stack<Integer>> response = new HashMap<>();
            var res = obj.canBeScheduled(servers, tasks, 0, response);
            System.out.println("Can be scheduled? " + res);
            System.out.println(response);
        }

        {
            int[] servers = {1, 3};
            int[] tasks = {4};

            Map<Integer, Stack<Integer>> response = new HashMap<>();
            var res = obj.canBeScheduled(servers, tasks, 0, response);
            System.out.println("Can be scheduled? " + res);
            System.out.println(response);
        }
    }

    private boolean canBeScheduled(int[] servers, int[] tasks, int index, Map<Integer, Stack<Integer>> response) {
        if (index == tasks.length) return true;
        for (int i = 0; i < servers.length; i++) {
            if (tasks[index] <= servers[i]) {
                servers[i] -= tasks[index];
                if (!response.containsKey(i)) response.put(i, new Stack<>());
                response.get(i).add(tasks[index]);
                if (canBeScheduled(servers, tasks, index + 1, response)) return true;
                servers[i] += tasks[index];
                response.get(i).pop();
            }
        }
        return false;
    }
}
