#include "../header.h"
/*
https://www.careercup.com/question?id=5723093194506240

Given an array of task and k wait time for which a repeated task needs to wait k time to execute again. return overall unit time it will take to complete all the task.
Example:
1. A B C D and k = 3
ans: 4 (execute order A B C D)
2. A B A D and k = 3
ans: 6 (execute order A B . . A D)
3. A A A A and k =3
ans: 13 (A . . . A . . . A . . . A)
4. A B C A C B D A and k = 4
ans: 11 (A B C . . A .C B D A )
*/
class SpaceTasksWithCooldownPeriod {
   public:
    static void test() {
        SpaceTasksWithCooldownPeriod obj;
        vector<pair<vector<char>, int>> inputs = {
            {{'A', 'B', 'C', 'D'}, 3},
            {{'A', 'B', 'A', 'D'}, 3},
            {{'A', 'A', 'A', 'A'}, 3},
            {{'A', 'B', 'C', 'A', 'C', 'B', 'D', 'A'}, 4},
            {{'A', 'A', 'A', 'B', 'B', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'}, 7}};
        for (auto& input : inputs) {
            auto tasks = input.first;
            int k = input.second;
            string result;
            int totalSpace = obj.spaceTasks(tasks, k, result);
            cout << format("Input={}, K={}, totalSpace={}, Spaced tasks={}", to_string(tasks), k, totalSpace, result) << endl;
        }
    }

    int spaceTasks(vector<char> tasks, int k, string& result) {
        vector<int> lastPos(256, -1);

        int curPos = 0;
        int totalSpace = 0;
        for (auto ch : tasks) {
            if (lastPos[ch] != -1 && curPos - lastPos[ch] < k + 1) {
                int spaces = (k + 1) - (curPos - lastPos[ch]);
                result += string(spaces, '_') + ch;

                totalSpace += spaces;
                curPos += spaces;
            } else {
                result += ch;
            }

            lastPos[ch] = curPos;

            curPos++;
            totalSpace++;
        }

        return totalSpace;
    }
};