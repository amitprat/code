package programs.misc;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class PathConversion {
    public static void test()
    {
        PathConversion obj = new PathConversion();
        String input = "AABCB";
        Map<String, String> map = new HashMap<>();
        map.put("AB", "C");
        map.put("AC", "B");
        map.put("BC","A");

        String res = obj.getFinalPath(input, map);
        System.out.println("Final Path: " + res);
    }

    String getFinalPath(String input, Map<String, String> map)
    {
        Stack<Character> stack = new Stack<>();
        for(char ch : input.toCharArray()) {
            stack.push(ch);
            evalStack(stack, map);
        }

        return stack.toString();
    }

    void evalStack(Stack<Character> st,Map<String, String> map)
    {
        StringBuilder sb = new StringBuilder();
        while(!st.empty()) {
            sb.append(st.pop());
            String reversedPath = sb.reverse().toString();
            if(map.containsKey(reversedPath)) {
                String val = map.get(reversedPath);
                st.push(val.charAt(0));
                sb = new StringBuilder();
            }
        }
        for(Character ch : sb.reverse().toString().toCharArray()) {
            st.push(ch);
        }
    }
}
