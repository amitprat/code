#include "../header.h"

/*
https://careercup.com/question?id=5706911210012672

Evaluate infix expression: 2 + 3 * 5
*/
class InfixToPostfix {
   public:
    static void test() {
        InfixToPostfix obj;
        string infixExpression = "a + b * c - d";
        auto postfix1 = obj.infixtoPostfix(infixExpression);
        cout << format("Postfix of infix='{}' is '{}'", infixExpression, postfix1) << endl;

        auto postfix2 = obj.infixToPostfix2(infixExpression);
        cout << "postfix2: " << postfix2 << endl;

        cout << obj.evaluateExpression("3 * 4 + 12 + 23 * 2 / 23") << endl;
        cout << obj.evaluateExpression("3 * 4 + 12") << endl;
        cout << obj.evaluateExpression("3 * 4 * 12") << endl;
        cout << obj.evaluateExpression("3 + 4 * 12 /2") << endl;
    }

   private:
    string infixtoPostfix(string str) {
        string postfix;
        stack<char> op;
        for (auto ch : str) {
            if (isspace(ch)) continue;

            if (isalnum(ch)) {
                postfix += ch;
            } else if (ch == '(') {
                op.push(ch);
            } else if (ch == ')') {
                while (!op.empty() && op.top() != '(') {
                    postfix += op.top();
                    op.pop();
                }
                op.pop();
            } else {
                while (!op.empty() && op.top() != '(' && prec(ch) <= prec(op.top())) {
                    postfix += op.top();
                    op.pop();
                }
                op.push(ch);
            }
        }
        while (!op.empty()) {
            postfix += op.top();
            op.pop();
        }

        return postfix;
    }

   private:
    vector<string> infixToPostfix2(string infix) {
        vector<string> postfix;
        stack<char> st;

        string cur;
        for (auto ch : infix) {
            if (isspace(ch)) continue;

            if (isalnum(ch)) {
                cur += ch;
            } else if (ch == '(') {
                st.push(ch);
            } else if (ch == ')') {
                postfix.push_back(cur);
                cur.clear();

                while (!st.empty() && st.top() != '(') {
                    postfix.push_back(string(1, st.top()));
                    st.pop();
                }
                st.pop();
            } else {
                postfix.push_back(cur);
                cur.clear();

                while (!st.empty() && st.top() != '(' && prec(ch) <= prec(st.top())) {
                    postfix.push_back(string(1, st.top()));
                    st.pop();
                }

                st.push(ch);
            }
        }
        if (!cur.empty()) postfix.push_back(cur);

        while (!st.empty()) {
            postfix.push_back(string(1, st.top()));
            st.pop();
        }
        return postfix;
    }

    int prec(char ch) {
        if (ch == '+' || ch == '-') return 1;
        if (ch == '*' || ch == '/') return 2;

        return 0;
    }

   private:
    double evaluateExpression(string infix) {
        double val = 0;
        stack<double> operand;
        stack<char> operators;

        string cur;
        for (auto ch : infix) {
            if (isspace(ch)) continue;

            if (isalnum(ch))
                cur += ch;
            else if (ch == '(')
                operators.push(ch);
            else if (ch == ')') {
                operand.push(stoi(cur));
                cur.clear();

                while (!operators.empty() && operators.top() != '(') {
                    operand.push(applyTop(operand, operators));
                }
                operators.pop();
            } else {
                operand.push(stoi(cur));
                cur.clear();

                while (!operators.empty() && operators.top() != '(' && prec(ch) <= prec(operators.top())) {
                    operand.push(applyTop(operand, operators));
                }
                operators.push(ch);
            }
        }
        if (!cur.empty()) operand.push(stoi(cur));

        while (!operators.empty()) {
            operand.push(applyTop(operand, operators));
        }

        return operand.top();
    }

    double applyTop(stack<double>& operand, stack<char>& operators) {
        auto op2 = operand.top();
        operand.pop();
        auto op1 = operand.top();
        operand.pop();

        auto op = operators.top();
        operators.pop();

        switch (op) {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
        }

        return INT_MIN;
    }
};