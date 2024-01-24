package programs.careercup;

import java.util.*;

public class GroupAnagrams {
    public static void test() {
        String[] input = {"trees", "bike", "cars", "steer", "arcs" };
        Map<String, List<String>> result = new HashMap<>();
        Arrays.stream(input).forEach(str -> {
            String key = sort(str);
            if (!result.containsKey(key)) result.put(key, new ArrayList<>());
            result.get(key).add(str);
        });

        System.out.println(result);
    }

    private static String sort(String str) {
        char[] arr = str.toCharArray();
        Arrays.sort(arr);

        return new String(arr);
    }
}
