#pragma once
#include "../Header.h"

/*
You're given an array of integers(eg [3,4,7,1,2,9,8]) Find the index of values that satisfy A+B = C + D,
where A,B,C & D are integers values in the array.

Eg: Given [3,4,7,1,2,9,8] array
The following
3+7 = 1+ 9 satisfies A+B=C+D
so print (0,2,3,5)
*/
struct Node
{
    int x;
    int y;
    Node(int a = 0, int b = 0) :x(a), y(b) {};
};
vector<int> Print4Sum(vector<int> A) {
    int tsum, l = A.size();
    vector<int> ans;
    if (l < 4) return ans;

    map<int, Node> hashmap;
    for (int i = 0; i < l - 1; ++i)
        for (int j = i + 1; j < l; ++j)
        {
            tsum = A[i] + A[j];
            if (hashmap.find(tsum) == hashmap.end()) {
                Node tnode = Node(i, j);
                hashmap[tsum] = tnode;
            }
            else {
                Node tnode = hashmap[tsum];
                int x = tnode.x, y = tnode.y;
                if (x != i && x != j && y != i && y != j)
                {
                    ans.push_back(i);
                    ans.push_back(j);
                    ans.push_back(x);
                    ans.push_back(y);
                    sort(ans.begin(), ans.end());
                    return ans;
                }
            }
        }
    return ans;
}