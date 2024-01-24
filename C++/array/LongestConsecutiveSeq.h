#include "../header.h"
/*
* Given an int array which might contain duplicates, find the largest subset of it which form a sequence.
Eg. {1,6,10,4,7,9,5}
then ans is 4,5,6,7

Sorting is an obvious solution. Can this be done in O(n) time

"""Given an int array which might contain duplicates, find the largest subset of it which form a sequence.
Eg. {1,6,10,4,7,9,5}
then ans is 4,5,6,7
Sorting is an obvious solution. Can this be done in O(n) time"""
def find(arr):
    table = {}
    first = 0
    last = 0
    for i in arr:
        beg = end = i
        if i in table:
            continue
        table[i] = 'EXISTED'
        if i - 1 in table:
            beg = table[i-1]
        if i + 1 in table:
            end = table[i+1]
        table[beg] = end
        table[end] = beg
        if end - beg > last - first:
            first = beg
            last = end
    return list(range(first, last + 1))

arr = [1,6,10,4,7,9,5, 5,8]

print(find(arr))
*/

class LongestConsecutiveSeq {
   public:
    static void test() {
        vector<int> arr = {1, 6, 10, 4, 7, 9, 5};
        LongestConsecutiveSeq obj;
        pair<int, int> res = obj.findLongestSeq(arr);
        for (int i = res.first; i <= res.second; i++) {
            cout << i << " ";
        }
        cout << endl;
    }

    pair<int, int> findLongestSeq(vector<int> arr) {
        unordered_map<int, int> map;
        int first = 0, last = 0;
        for (auto i : arr) {
            int beg, end;
            beg = end = i;
            if (map.find(i - 1) != map.end()) {
                beg = map[i - 1];
            }
            if (map.find(i + 1) != map.end()) {
                end = map[i + 1];
            }
            map[beg] = end;
            map[end] = beg;
            cout << beg << "->" << end << endl;
            cout << end << "->" << beg << endl;

            if (end - beg > last - first) {
                first = beg;
                last = end;
            }
            cout << "[" << first << ", " << last << "]" << endl;
        }
        return {first, last};
    }

   private:
    vector<int> longestConsecutive(vector<int>& nums) {
        unordered_set<int> hashSet;
        for (int num : nums) {
            hashSet.insert(num);
        }

        vector<int> longestSeq;
        for (int num : nums) {
            // If there is no element with lesser value
            if (hashSet.find(num - 1) == hashSet.end()) {
                vector<int> currentSeq;
                int j = num;
                // Then check for next elements in the sequence
                while (hashSet.find(j) != hashSet.end()) {
                    currentSeq.push_back(j);
                    j++;
                }

                // Update longest sequence if necessary
                if (currentSeq.size() > longestSeq.size()) {
                    longestSeq = currentSeq;
                }
            }
        }
        return longestSeq;
    }
};