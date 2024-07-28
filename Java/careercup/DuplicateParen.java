package programs.careercup;

import java.util.Stack;

/*
 * https://www.careercup.com/question?id=5978736570662912
 * give an algorithm for finding duplicate parenthesis in a expression.
 * example :
 * (( a + b ) + (( c + d )))
 */
public class DuplicateParen {
    public static void test() {
        String str = "(( a + b ) + (( c + d )))";
        boolean res = hasDuplicateParen(str);
        System.out.println(res);
    }

    private static boolean hasDuplicateParen(String str) {
        Stack<Character> st = new Stack<>();
        for (char ch : str.toCharArray()) {
            if (ch != ')')
                st.push(ch); // if it is anything other than closing paren
            else {
                char top = st.pop();
                if (top == '(')
                    return true; // duplicate found

                // remove all until last char remove isn't start paren.
                while (cur != '(') {
                    cur = st.pop();
                }
            }
        }

        return false;
    }
}
