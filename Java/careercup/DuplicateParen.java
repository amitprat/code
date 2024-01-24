package programs.careercup;

import java.util.Stack;

public class DuplicateParen {
    public static void test() {
        String str = "(( a + b ) + (( c + d )))";
        boolean res = hasDuplicateParen(str);
        System.out.println(res);
    }

    private static boolean hasDuplicateParen(String str) {
        Stack<Character> st = new Stack<>();
        for (char ch : str.toCharArray()) {
            if (ch != ')') st.push(ch);
            else {
                char cur = st.pop();
                if (cur == '(') return true;

                while (cur != '(') {
                    cur = st.pop();
                }
            }
        }

        return false;
    }
}
