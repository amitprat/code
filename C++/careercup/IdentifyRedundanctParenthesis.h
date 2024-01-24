#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=6276805505843200

Find if the given expression contains redundant parantheses. ex :if expr = a+(b*c) , print false, if expr = a+((b*c)), print true.

We maintain a stack. We traverse the expression, and we push either a bracket, or a value. If the top of stack contains a value, we don't push another value,
just leave it as is. If we encounter a right bracket, we expect a value on top to pop. We then pop the value and pop a bracket. If we don't get a value on top
when we encounter a right bracket, then we have redundant brackets.

We ignore operators.

code would look something like
*/
class IdentifyRedundanctParenthesis
{
public:
	static void test() {
		vector<string> strs = { "a+(b*c)","a+((b*c))", "a+(((b*c)+(e+f)))(n*m+c)","a+((b*c)+(e+f))(n*m+c)" };

		for (auto str : strs) {
			if (isValid(str)) {
				cout << str << " is valid" << endl;
			}
			else {
				cout << str << " is not valid" << endl;
			}
		}
	}

	static bool isValid(string str) {
		stack<char> st;

		for (auto ch : str) {
			if (ch == '(') st.push(ch);
			else if (ch == ')') {
				if (st.empty() || st.top() == '(') return false;
				st.pop();

				if (st.empty() || st.top() != '(') return false;
				st.pop();
			}
			else {
				if (st.empty() || st.top() == '(') st.push(ch);
			}
		}

		return true;
	}
};