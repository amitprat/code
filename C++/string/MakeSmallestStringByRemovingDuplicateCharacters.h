#pragma once
#include "../header.h"

class MakeSmallestStringByRemovingDuplicateCharacters {
   public:
    static void test() {
        MakeSmallestStringByRemovingDuplicateCharacters obj;
        std::vector<std::string> inputs = {"bcsbc", "cbacdcbc"};
        for (const auto& input : inputs) {
            std::string res = obj.findSmallest(input);
            std::cout << std::format("Smallest lexographic string for input={} is {}\n", input, res);
        }
    }

    std::string findSmallest(const std::string& str) {
        std::array<int, 26> lastPos{};
        lastPos.fill(-1);

        int len = static_cast<int>(str.length());
        for (int i = 0; i < len; ++i) {
            lastPos[str[i] - 'a'] = i;  // last occurrence of each character
        }

        std::array<bool, 26> visited{};
        visited.fill(false);

        std::string res;
        std::stack<char> st;

        for (int i = 0; i < len; ++i) {
            char c = str[i];
            int idx = c - 'a';
            if (visited[idx]) continue;

            while (!st.empty() && st.top() > c && lastPos[st.top() - 'a'] > i) {
                visited[st.top() - 'a'] = false;
                st.pop();
            }

            st.push(c);
            visited[idx] = true;
        }

        // Build the result from stack
        res.resize(st.size());
        for (int i = static_cast<int>(st.size()) - 1; i >= 0; --i) {
            res[i] = st.top();
            st.pop();
        }

        return res;
    }
};
