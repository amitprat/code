package programs.arrays;

import java.util.HashMap;
import java.util.Map;

public class SpaceTasks {
    public static void test() {
        int[] tasks = {1, 1, 2, 1, 2};
        int k = 2;

        spaceTasks(tasks, 2);
    }

    private static void spaceTasks(int[] tasks, int k) {
        int current = 0;
        Map<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < tasks.length; i++) {
            if (!map.containsKey(tasks[i])) {
                System.out.print(tasks[i]);
                map.put(tasks[i], current++);
            } else {
                int next = map.get(tasks[i]) + k + 1;
                while (current++ < next) System.out.print("_");
                map.put(tasks[i], current++);
                System.out.print(tasks[i]);
            }
        }
        System.out.println();
    }
}
