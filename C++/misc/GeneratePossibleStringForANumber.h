#pragma once
#include "../header.h"

/*
* If a=1, b=2, c=3,....z=26. Given a string, find all possible codes that string can generate. Give a count as well as print the strings.

For example:
Input: "1123". You need to general all valid alphabet codes from this string.

Output List
aabc //a = 1, a = 1, b = 2, c = 3
kbc // since k is 11, b = 2, c= 3
alc // a = 1, l = 12, c = 3
aaw // a= 1, a =1, w= 23
kw // k = 11, w = 23


decode("", "1123");

public Set<String> decode(String prefix, String code) {
        Set<String> set = new HashSet<String>();
        if (code.length() == 0) {
            set.add(prefix);
            return set;
        }

        if (code.charAt(0) == '0')
            return set;

        set.addAll(decode(prefix + (char) (code.charAt(0) - '1' + 'a'),
                code.substring(1)));
        if (code.length() >= 2 && code.charAt(0) == '1') {
            set.addAll(decode(
                    prefix + (char) (10 + code.charAt(1) - '1' + 'a'),
                    code.substring(2)));
        }
        if (code.length() >= 2 && code.charAt(0) == '2'
                && code.charAt(1) <= '6') {
            set.addAll(decode(
                    prefix + (char) (20 + code.charAt(1) - '1' + 'a'),
                    code.substring(2)));
        }
        return set;
}
*/

class DecodeString {
public:
    static void test() {
        DecodeString obj;
        string input = "1103";
        vector<string> output;
        obj.decode(input, output, 0, "");
        for (auto s : output) cout << s << " ";
        cout << endl;
    }

    void decode(string input, vector<string>& output, int s, string cur) {
        if (s > input.length()) return;
        if (s == input.length()) {
            output.push_back(cur);
            return;
        }
        int num = toInt(input, s, 1);
        decode(input, output, s + 1, cur + toStr(num));

        num = toInt(input, s, 2);
        if (num != 0) decode(input, output, s + 2, cur + toStr(num));
    }

    int toInt(string in, int s, int len) {
        string sub = in.substr(s, len);
        return stoi(sub);
    }

    string toStr(int num) {
        if (num <= 0 || num > 26) return "";
        return string(1, 'a' + num - 1);
    }
};