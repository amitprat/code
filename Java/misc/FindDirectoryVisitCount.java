package programs.misc;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class FindDirectoryVisitCount {
    public static void test() {
        FindDirectoryVisitCount obj = new FindDirectoryVisitCount();
        String str = "a/b/../c/d/e/../../";
        Map<String, Integer> counts = null;
        try {
            counts = obj.findCount(str);
            counts.forEach((k, v) -> {
                System.out.println(k + ":" + v);
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    Map<String, Integer> findCount(String str) throws Exception {
        Map<String, Integer> result = new HashMap<>();
        Stack<String> stringStack = new Stack<>();
        String[] splits = str.split("/");
        for (String part : splits) {
            if (part.equals(".")) continue;
            else if (part.equals("..")) {
                if (stringStack.empty()) throw new Exception("Invalid Path");
                else {
                    stringStack.pop();
                    String oldPath = stringStack.peek();
                    result.put(oldPath, result.get(oldPath) + 1);
                }
            } else {
                result.put(part, 1);
                stringStack.push(part);
            }
        }
        System.out.println("Final Path: " + stringStack.peek());
        return result;
    }
}
