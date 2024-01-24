package programs.misc;

import java.util.HashMap;
import java.util.Map;

public class SpaceTasks {
    public static void test() {
        SpaceTasks obj = new SpaceTasks();
        String str = "ABCACBDA";
        int k = 4;

        var res = obj.spaceTasks(str, k);
        System.out.println(res);
    }

    private String spaceTasks(String str, int k) {
        Map<Character, Integer> map = new HashMap<>();
        int current = 0;
        String response = "";
        for (var ch : str.toCharArray()) {
            if (map.containsKey(ch)) {
                int prev = map.get(ch);
                int desired = prev + k + 1;
                while (current < desired) {
                    response += "_";
                    current++;
                }
            }
            map.put(ch, current++);
            response += ch;
        }
        return response;
    }
}
