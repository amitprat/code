#include "../header.h"

/*
https://careercup.com/question?id=19300678

If a=1, b=2, c=3,....z=26. Given a string, find all possible codes that string can generate. Give a count as well as print the strings.

For example:
Input: "1123". You need to general all valid alphabet codes from this string.

Output List
aabc //a = 1, a = 1, b = 2, c = 3
kbc // since k is 11, b = 2, c= 3
alc // a = 1, l = 12, c = 3
aaw // a= 1, a =1, w= 23
kw // k = 11, w = 23
*/
class CountDecodings {
   public:
    static void test() {
        string str = "1123";
        CountDecodings obj;
        unordered_set<string> col;
        cout << obj.count(str, 0, col, "") << endl;
        for (auto s : col) cout << s << " ";
        cout << endl;
    }

    int count(string str, int index, unordered_set<string>& col, string prefix) {
        if (idx > str.length()) return 0;
        if (index == str.size()) {
            col.insert(prefix);
            return 1;
        }
        if (str[index] == '0') return 0;

        int res = count(str, index + 1, col, prefix + string(1, str[index] + 'a' - '1'));
        if (index + 1 < str.size()) {
            if (str[index] == '1') {
                res += count(str, index + 2, col, prefix + string(1, 10 + str[index + 1] + 'a' - '1'));
            }
            if (str[index] == '2' && str[index + 1] <= '6') {
                res += count(str, index + 2, col, prefix + string(1, 20 + str[index + 1] + 'a' - '1'));
            }
        }

        return res;
    }
};