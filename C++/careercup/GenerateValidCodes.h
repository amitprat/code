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

class GenerateValidCodes {
   public:
    static void test() {
        string input = "1123";
        GenerateValidCodes obj;
        obj.generateCodes(input);
    }

   private:
    void generateCodes(string &input) {
        vector<string> result;
        generateCodes(input, 0, input.length(), "", result);
        cout << "Result = " << result << endl;
    }

    void generateCodes(string &input, int i, int n, string cur, vector<string> &result) {
        if (i >= n) {
            if (!cur.empty())
                result.push_back(cur);
            return;
        }
        if (input[i] == '0') {
            generateCodes(input, i + 1, n, cur, result);
        }

        generateCodes(input, i + 1, n, cur + string(1, ('a' + input[i] - '1')), result);

        if (i + 1 < n && input[i] <= '2' && input[i + 1] <= '6') {
            int val = (input[i] - '0') * 10 + (input[i + 1] - '0');
            generateCodes(input, i + 2, n, cur + string(1, ('a' + val - 1)), result);
        }
    }
};