#pragma once
#include "../header.h"
/*
https://careercup.com/question?id=5706911210012672
Evaluate infix expression: 2 + 3 * 5
*/
class InfixToPostfix {
   public:
    static void test() {
        InfixToPostfix obj;
        vector<string> expressions = {
            "a + b * c - d",
            "a+b*(c^d-e)^(f+g*h)-i",
            "1^2+3^(4-5)*6",
            "2^(2+3^(4-5)*6)",
            "(a+(b*c))",
            "((a+b)*(z+x))",
            "((a+t)*((b+(a+c))^(c+d)))",
            "a+b*(c*d-e)-i"};
        for (const auto& expression : expressions) {
            auto postfix1 = obj.infixtoPostfix(expression);

            string postfix2;
            {
                auto postfix = obj.infixToPostfix2(expression);
                for (auto str : postfix) postfix2 += str;
            }
            assert(postfix1 == postfix2);

            cout << format("Postfix of infix='{}' is '{}'", expression, postfix1) << endl;
        }

        expressions = {
            "3 * 4 + 12 + 23 * 2 / 23",
            "3 * 4 + 12",
            "3 + 4 * 12",
            "3 + 4 * 12 /2",
            "1^2+3^(4-5)*6",
            "2^(2+3^(4-5)*6)"};
        for (const auto& expression : expressions) {
            double value = obj.evaluateExpression(expression);
            cout << format("Value of infix='{}' is '{}'", expression, value) << endl;
        }
    }

   private:
    // this assumes that all operands are single digit long only.
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
                // pop all the operators till '('
                while (!op.empty() && op.top() != '(') {
                    postfix += op.top();
                    op.pop();
                }
                op.pop();  // pop '('
            } else {
                // pop all operators on stack with prec higher than current element and add to postfix string.
                while (!op.empty() && prec(op.top()) >= prec(ch)) {
                    postfix += op.top();
                    op.pop();
                }

                // push the current operator on stack
                op.push(ch);
            }
        }

        // put all the remaining operators on postfix.
        while (!op.empty()) {
            postfix += op.top();
            op.pop();
        }

        return postfix;
    }

   private:
    // This handles the case operand is longer than single character/digit.
    vector<string> infixToPostfix2(string infix) {
        vector<string> postfix;
        stack<char> st;

        string cur;
        for (auto ch : infix) {
            // operand like 12 23 is invalid. All operand should be seperated by operators only.
            // we aren't doing that validation here.
            if (isspace(ch)) continue;

            if (isalnum(ch))  // operand
            {
                cur += ch;
            } else  // operator
            {
                // add operand calculated so far to postfix string.
                if (!cur.empty()) {
                    postfix.push_back(cur);
                    cur.clear();
                }

                if (ch == '(')
                    st.push('(');
                else if (ch == ')') {
                    while (st.top() != '(') {
                        postfix.push_back(string(1, st.top()));  // push the current operator.
                        st.pop();
                    }

                    st.pop();  // pop '('
                } else {
                    // extract all the operators with higher priority.
                    // for example: a+b*c => abc*+
                    // for example: a*b+c => ab*c+
                    while (!st.empty() && prec(st.top()) >= prec(ch)) {
                        postfix.push_back(string(1, st.top()));
                        st.pop();
                    }
                    st.push(ch);  // push current operator.
                }
            }
        }
        if (!cur.empty()) postfix.push_back(cur);

        while (!st.empty()) {
            postfix.push_back(string(1, st.top()));
            st.pop();
        }

        return postfix;
    }

   private:
    double evaluateExpression(string infix) {
        double val = 0;
        stack<double> operands;
        stack<char> operators;

        string cur;
        for (auto ch : infix) {
            if (isspace(ch)) continue;

            if (isalnum(ch)) {  // if is operand
                cur += ch;
            } else {  // operator
                if (ch != '(' && cur.empty()) throw runtime_error("Invalid expression.");

                if (!cur.empty()) {
                    operands.push(stoi(cur));
                    cur.clear();
                }

                if (ch == '(') {
                    operators.push(ch);
                } else if (ch == ')') {
                    while (ch != '(') {
                        auto second = operands.top();
                        operands.pop();
                        auto first = operands.top();
                        operands.pop();
                        auto op = operators.top();
                        operators.pop();

                        operands.push(apply(first, second, op));
                    }

                    operators.pop();  // pop '('
                } else {
                    while (!operators.empty() && prec(operators.top()) >= prec(ch)) {
                        auto second = operands.top();
                        operands.pop();
                        auto first = operands.top();
                        operands.pop();
                        auto op = operators.top();
                        operators.pop();

                        operands.push(apply(first, second, op));
                    }

                    operators.push(ch);
                }
            }
        }
        if (!cur.empty()) operands.push(stoi(cur));

        while (!operators.empty()) {
            auto second = operands.top();
            operands.pop();
            auto first = operands.top();
            operands.pop();
            auto op = operators.top();
            operators.pop();

            operands.push(apply(first, second, op));
        }

        return operands.top();
    }

   private:
    int prec(char ch) {
        if (ch == '(') return 0;
        if (ch == '+' || ch == '-') return 1;
        if (ch == '*' || ch == '/') return 2;
        if (ch == '^') return 3;
        if (ch == ')') return 999;

        return 0;
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

    double apply(double first, double second, char op) {
        switch (op) {
            case '+':
                return first + second;
            case '-':
                return first - second;
            case '*':
                return first * second;
            case '/':
                return first / second;
            case '^':
                return pow(first, second);
        }

        throw runtime_error("invalid operator");
    }
};