#include "../Header.h"

/*
Given a string with only parenthesis. Check if the string is balanced.
ex -
1) "<({()})[]> is balanced
2) "<({([)})[]> is not balanced
*/

bool isOpen(char ch)
{
    return ch == '(' || ch == '{' || ch == '[';
}

bool isClose(char ch)
{
    return ch == ')' || ch == '}' || ch == ']';
}

bool isPair(char s, char e)
{
    return (
        (s == '(' && e == ')') ||
        (s == '{' && e == '}') ||
        (s == '[' && e == ']'));
}

bool isValid(string str)
{
    stack<char> st;
    for (auto ch : str)
    {
        if (isOpen(ch))
            st.push(ch);
        else if (isClose(ch))
        {
            auto t = st.top();
            st.pop();
            if (!isPair(t, ch))
                return false;
        }
    }

    return true;
}

def check_bracket(str):
    stack = list()
    for char in str:
        if char == '<' or char == '(' or char == '{' or\
           char == '[':
            stack.append(char)
        else:
            bracket = stack.pop()
            if char == '>' and bracket != '<' or\
               char == '}' and bracket != '{' or\
               char == ')' and bracket != '(' or\
               char == ']' and bracket != '[':
                return False
    return True