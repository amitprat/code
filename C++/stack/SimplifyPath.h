#pragma once
#include "../header.h"

class SimplifyPath {
public:
    static void test() {
        SimplifyPath obj;
        vector<pair<string, string>> tests = {
            {"/home/","/home"},
            {"/a/./b/../../c/","/c"},
            {"/../","/"},
            {"/home//foo/","/home/foo"}
        };
        for (auto& test : tests) {
            auto res = obj.simplifyPath(test.first);
            cout << "Input : " << test.first << " Result :" << res << endl;
            assert(test.second == res);
        }
    }

    string simplifyPath(string& path) {
        stack<string> st;
        removeTrailingSpacesAndSlashes(path);
        int start = 0;
        for (int i = 0; i <= path.length(); i++) {
            string cur;
            if (i == path.length()) {
                cur = path.substr(start);
            }
            else if (path[i] == '/') {
                cur = path.substr(start, i - start);
                start = i + 1;
            }
            if (cur.empty()) continue;
            if (cur == ".") continue;
            if (cur == "..") { if (!st.empty()) st.pop(); }
            else st.push(cur);
        }

        string result;
        while (!st.empty()) {
            auto cur = st.top(); st.pop();
            if (result.empty()) result = cur;
            else result = cur + "/" + result;
        }
        result = "/" + result;
        return result;
    }

    void removeTrailingSpacesAndSlashes(string& str) {
        int i = str.length() - 1;
        while (str[i] == '/' || str[i] == ' ') i--;
        str = str.substr(0, i + 1);
    }
};