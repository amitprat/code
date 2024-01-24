package programs.graph;

import java.util.*;
import java.util.stream.Collectors;

public class PrintFriendsAtLevel {
    public static void test() {
        Map<String, List<String>> map = new HashMap<>();
        map.put("A", Arrays.asList("B", "C", "D"));
        map.put("D", Arrays.asList("B", "E", "F"));
        map.put("E", Arrays.asList("C", "F", "G"));

        /*
        DFS won't work here as it could print same friend at next level
         */
        System.out.println(friendsAtLevel(map, "A", 1));
        System.out.println(friendsAtLevel(map, "A", 2));
        System.out.println(friendsAtLevel(map, "A", 3));
        System.out.println(friendsAtLevel(map, "A", 4));
        System.out.println();

        System.out.println(friendsAtLevel(map, "B", 1));
        System.out.println(friendsAtLevel(map, "B", 2));
        System.out.println(friendsAtLevel(map, "B", 3));
        System.out.println(friendsAtLevel(map, "B", 4));
        System.out.println();

        System.out.println(friendsAtLevel(map, "C", 1));
        System.out.println(friendsAtLevel(map, "C", 2));
        System.out.println(friendsAtLevel(map, "C", 3));
        System.out.println(friendsAtLevel(map, "C", 4));
        System.out.println();

        System.out.println(friendsAtLevel(map, "D", 1));
        System.out.println(friendsAtLevel(map, "D", 2));
        System.out.println(friendsAtLevel(map, "D", 3));
        System.out.println(friendsAtLevel(map, "D", 4));
    }

    private static List<String> friendsAtLevel(Map<String, List<String>> map, String root, int level) {
        Queue<String> q = new LinkedList<>();
        q.add(root);
        Set<String> visited = new HashSet<>();
        visited.add(root);

        while (!q.isEmpty() && level-- != 0) {
            int sz = q.size();

            while (sz-- != 0) {
                var front = q.poll();
                if (!map.containsKey(front)) continue;
                for (var friend : map.get(front)) {
                    if (!visited.contains(friend)) {
                        q.add(friend);
                        visited.add(friend);
                    }
                }
            }
        }

        return q.stream().collect(Collectors.toList());
    }

    private static List<String> friendsAtLevelDFS(Map<String, List<String>> map, String root, int level) {
        List<String> result = new ArrayList<>();
        Set<String> visited = new HashSet<>();
        dfs(map, root, level, result, visited);

        return result;
    }

    private static void dfs(Map<String, List<String>> map, String root, int level, List<String> result,
                            Set<String> visited) {
        visited.add(root);
        if (level == 0) {
            result.add(root);
            return;
        }
        if (!map.containsKey(root)) return;
        for (var friend : map.get(root)) {
            if (!visited.contains(friend)) {
                dfs(map, friend, level - 1, result, visited);
            }
        }
    }
}
