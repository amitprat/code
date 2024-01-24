#include "../header.h"

class EvaluateSpecialExpression {
   public:
    static void test() {
        EvaluateSpecialExpression obj;
        string str = "[8, 3, 2, [5, 6, [9]], 6]";
        auto res = obj.evaluate(str);

        cout << "Result: " << res << endl;
    }

   public:
    int evaluate(string& str) {
        vector<string> res = parseStr(str, {'[', ']', ',', ' '});
        res = filter(res, {" ", ","});

        stack<string> st;
        int mul = 0;
        int sum = 0;
        for (auto& s : res) {
            // converting to char here to use switch
            // otherwise, we should use if..else
            char ch = s[0];
            switch (ch) {
                case '[':
                    st.push(string(1, ch));
                    mul++;
                    break;
                case ']':
                    while (!st.empty() && st.top() != "[") {
                        sum += stoi(st.top());
                        st.pop();
                    }
                    st.pop();
                    sum *= mul;
                    st.push(to_string(sum));
                    mul--;
                    sum = 0;
                    break;
                default:
                    st.push(string(1, ch));
                    break;
            }
        }

        return stoi(st.top());
    }

   private:
    vector<string> parseStr(string str, vector<char> delimiters) {
        vector<string> values;
        values.push_back(str);

        for (auto delim : delimiters) {
            vector<string> newValues;
            for (auto val : values) {
                vector<string> cur = parseStr(val, delim);
                newValues.insert(newValues.end(), cur.begin(), cur.end());
            }

            values = newValues;
        }

        return values;
    }

    vector<string> parseStr(string val, char delim) {
        vector<string> out;
        size_t prev = 0, pos = string::npos;
        while ((pos = val.find_first_of(delim, prev)) != string::npos) {
            if (pos > prev) out.push_back(val.substr(prev, pos - prev));
            out.push_back(string(1, delim));
            prev = pos + 1;
        }
        if (prev < val.size()) out.push_back(val.substr(prev));

        return out;
    }

    vector<string> filter(vector<string>& values, vector<string> filters) {
        vector<string> result;
        unordered_set<string> s;
        for (auto f : filters) s.insert(f);

        for (auto& val : values) {
            if (s.find(val) == s.end()) result.push_back(val);
        }

        return result;
    }
};