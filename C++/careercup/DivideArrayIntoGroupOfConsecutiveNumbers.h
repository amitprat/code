#include "../header.h"

/*
https://careercup.com/question?id=65732

Divide a list of numbers into group of consecutive numbers but their original order should be preserved?
e.g.
8,2,4,7,1,0,3,6

2,4,1,0,3 and 8,7,6

obviously in shortest time and space.
*/
class DivideArrayIntoGroupOfConsecutiveNumbers {
   public:
    static void test() {
        DivideArrayIntoGroupOfConsecutiveNumbers obj;
        vector<int> arr = {8, 2, 4, 7, 1, 0, 3, 6};
        obj.divideArray(arr);
    }

   private:
    void divideArray(vector<int>& arr) {
        unordered_map<int, int> elemToGroup;
        unordered_map<int, vector<int>> groupToElements;

        int grp = 1;
        for (auto& e : arr) {
            if (elemToGroup.find(e - 1) != elemToGroup.end()) {
                elemToGroup.insert({e, elemToGroup[e - 1]});
                groupToElements[elemToGroup[e]].push_back(e);
            } else if (elemToGroup.find(e + 1) != elemToGroup.end()) {
                elemToGroup.insert({e, elemToGroup[e + 1]});
                groupToElements[elemToGroup[e]].push_back(e);
            } else if (elemToGroup.find(e) == elemToGroup.end()) {
                elemToGroup[e] = grp++;
                groupToElements[elemToGroup[e]].push_back(e);
            }
        }

        for (auto group : groupToElements) {
            cout << group.first << " ";
            for (auto e : group.second) cout << e << " ";
            cout << endl;
        }
    }
};