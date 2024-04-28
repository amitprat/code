#pragma once
#include "../header.h"

class IterativeDFSTraversal {
   public:
    void iterativeTraversal(Graph g, int s) {
        stack<int> st;
        st.push(s);

        unordered_set<int> visited;

        while (!st.empty()) {
            auto top = st.top();
            st.pop();
            visited.insert(top);

            cout << top << " ";

            for (auto v : g.getAdjMap()[top]) {
                if (visited.find(v) == visited.end()) {
                    st.push(v);
                }
            }
        }
    }
};