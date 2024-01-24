package programs.stack;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class InfixToPostfix {
    private final Map<Character, Integer> precMap;

    InfixToPostfix() {
        precMap = new HashMap<>() {{
            put('(', 0);
            put('+', 1);
            put('-', 1);
            put('*', 2);
            put('/', 2);
            put('^', 3);
        }};
    }

    public static void test() {
        InfixToPostfix obj = new InfixToPostfix();
        String exp = "4+1*(2^3-5)^(1+2*1)-2";

        var postfix = obj.infixToPostfix(exp);
        System.out.println("Postfix = " + postfix);

        var out = obj.evaluate(postfix);
        System.out.println("Value = " + out);
    }

    public String infixToPostfix(String infix) {
        String result = "";
        Stack<Character> st = new Stack<>();
        for (var ch : infix.toCharArray()) {
            if (isOperand(ch)) result += ch;
            else {
                if (ch == '(') st.push(ch);
                else if (ch == ')') {
                    while (!st.empty() && st.peek() != '(') {
                        result += st.pop();
                    }
                    st.pop();
                } else {
                    while (!st.empty() && prec(ch) <= prec(st.peek())) {
                        result += st.pop();
                    }
                    st.push(ch);
                }
            }
        }
        while (!st.empty()) result += st.pop();
        return result;
    }

    public double evaluate(String postfix) {
        Stack<Double> st = new Stack<>();
        for (var ch : postfix.toCharArray()) {
            if (isOperand(ch)) st.push((double) (ch - '0'));
            else {
                if (st.size() == 1) return -1;
                var second = st.pop();
                var first = st.pop();
                st.push(eval(first, second, ch));
            }
        }
        return st.pop();
    }

    private boolean isOperand(char ch) {
        return ch >= '0' && ch <= '9';
    }

    private int prec(char ch) {
        return precMap.get(ch);
    }

    private double eval(double i, double j, char ch) {
        switch (ch) {
            case '+':
                return i + j;
            case '-':
                return i - j;
            case '*':
                return i * j;
            case '/':
                return i / j;
            case '^':
                return Math.pow(i, j);
            default:
                return 0.0;
        }
    }
}
