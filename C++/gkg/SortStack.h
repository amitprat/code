#pragma once
#include "../Header.h"

class SortStack {
public:
    static void test() {
        {
            stack<char> st;
            string str = "amitpratapsingh";
            for (auto ch : str) st.push(ch);

            reverse(st);

            string res;
            while (!st.empty()) { res += st.top(); st.pop(); }
            cout << "Reversed string: " << res << endl;
        }

        {
            stack<char> st;
            string str = "amitpratapsingh";
            for (auto ch : str) st.push(ch);

            sort(st);

            string res;
            while (!st.empty()) { res += st.top(); st.pop(); }
            cout << "Sorted string: " << res << endl;
        }
    }

    static void sort(stack<char>& st) {
        if (st.empty()) return;

        char ch = st.top(); st.pop();
        reverse(st);

        insertAtCorrectPlace(st, ch);
    }

    static void reverse(stack<char>& st) {
        if (st.empty()) return;

        char ch = st.top(); st.pop();
        reverse(st);

        insertAtBottom(st, ch);
    }

    static void insertAtBottom(stack<char>& st, char ch) {
        if (st.empty()) {
            st.push(ch);
            return;
        }

        char cur = st.top(); st.pop();
        insertAtBottom(st, ch);

        st.push(cur);
    }

    static void insertAtCorrectPlace(stack<char>& st, char ch) {
        if (st.empty() || ch <= st.top()) {
            st.push(ch);
            return;
        }

        char cur = st.top(); st.pop();
        insertAtCorrectPlace(st, ch);

        st.push(cur);
    }
};