#include <bits/stdc++.h>
using namespace std;

/*
https://www.careercup.com/question?id=5435425459011584

Given a list of input tasks to run, and the cooldown interval, output the minimum number of time slots required to run them.
// Tasks: 1, 1, 2, 1, 2
// Recovery interval (cooldown): 2
// Output: 8 (order is 1 _ _ 1 2 _ 1 2 )
Whats the time and space complexity ? What's the ideal case of space complexity ?

Time is O(n). Space is O(k) k is the number tasks

public void print_min_intervals(int[] task, int cooldown) {
        int currentPos = 0;
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < task.length; i++) {
            if (map.containsKey(task[i])) {
                int pos = map.get(task[i]);
                if (pos + cooldown + 1 - currentPos > 0) {
                    for (int k = 0; k < pos + cooldown + 1 - currentPos; k++) {
                        System.out.print("_ ");
                    }
                    currentPos = currentPos + cooldown - 1;
                }
            }
            System.out.print(task[i] + " ");
            map.put(task[i], currentPos);
            currentPos++;
        }
        System.out.println();
    }
*/

int spaceTasks(vector<int> &v, int k)
{
    int current = 0;
    unordered_map<int, int> posMap;

    for (auto e : v)
    {
        if (posMap.find(e) == posMap.end())
        {
            cout << e << " ";
            posMap[e] = current++;
        }
        else
        {
            int old = posMap[e];
            int next = old + k + 1;
            while (next > current)
            {
                cout << "_";
                current++;
            }
            cout << e << " ";
            current++;
        }
    }
    cout << endl;
    return current;
}

int main()
{
    vector<int> tasks = {1, 1, 2, 1, 2};
    int k = 2;
    auto res = spaceTasks(tasks, k);
    cout << "Required = " << res << endl;
    return 0;
}
