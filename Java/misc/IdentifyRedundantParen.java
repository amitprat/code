package programs.misc;

import java.util.Stack;

/*

amazon-interview-questions4
of 4 votes
41
Answers
give an algorithm for finding duplicate parenthesis in a expression.

example :


(( a + b ) + (( c + d )))
 */
public class IdentifyRedundantParen {
    public static void test() {
        String s = "(( a + b ) + ()( c + d ))";
        System.out.println("Has Redundant Paren? " + dupParen(s));
    }

    static boolean dupParen(String s) {
        Stack<Character> st = new Stack<>();
        for (char ch : s.toCharArray()) {
            if (ch != ')') st.push(ch);
            else {
                var cur = st.pop();
                if (cur == '(') return true;
                else {
                    while (st.pop() != '(') ;
                }
            }
        }
        return false;
    }
}
