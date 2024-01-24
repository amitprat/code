package programs.careercup;

import java.util.Stack;

public class MakeAbsolutePath {
    public static void test() {
        String str = "../../../etc/xyz/../abc";
        String str1 = "/usr/bin/mail";
        String str2 = "a/b/c/../d/../e/../f/../../../g/h";

        System.out.println(absPath(str));
        System.out.println(absPath(str1));
        System.out.println(absPath(str2));
    }

    static String absPath(String str) {
        String[] parts = str.split("/");
        int strIndex = -1;
        int curIndex = 0;
        Stack<String> stack = new Stack<>();

        for (String part : parts) {
            curIndex++;
            if (part.isEmpty() || part.equals(".")) {
                continue;
            }
            if (part.equals("..")) {
                if (!stack.empty()) {
                    stack.pop();
                }
                continue;
            }
            if (strIndex == -1) strIndex = curIndex - 1;
            stack.push(part);
        }
        if (stack.empty()) return "";
        String result = stack.pop();

        while (!stack.empty()) {
            result = stack.pop() + "/" + result;
        }
        if (strIndex != 0) result = "/" + result;

        return result;
    }
}
