#pragma once
#include "../header.h"

class ReverseStack {
   public:
    static void test() {
        stack<char> st;
        string str = "amitpratapsingh";
        for (auto ch : str) st.push(ch);

        reverseRecursive(st);

        string res;
        while (!st.empty()) {
            res += st.top();
            st.pop();
        }
        cout << "Reversed string: " << res << endl;
    }

   private:
    static void reverseRecursive(stack<char>& st) {
        if (st.empty()) return;

        char ch = st.top();
        st.pop();

        reverseRecursive(st);

        insertAtBottom(st, ch);
    }

    static void insertAtBottom(stack<char>& st, char ch) {
        if (st.empty()) {
            st.push(ch);
            return;
        }

        char cur = st.top();
        st.pop();
        insertAtBottom(st, ch);

        st.push(cur);
    }
};