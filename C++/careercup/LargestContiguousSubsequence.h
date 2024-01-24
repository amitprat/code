#include "../header.h"

/*
https://careercup.com/question?id=11070934

Given an int array which might contain duplicates, find the largest subset of it which form a sequence.
Eg. {1,6,10,4,7,9,5}
then ans is 4,5,6,7

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

class LargestContiguousSubsequence {
   public:
    static void test() {
        vector<int> input = {1, 6, 10, 4, 7, 9, 5};
        LargestContiguousSubsequence obj;

        auto output = obj.largestContiguousSequence(input);
        // cout << format("Largest contiguous sequence in {} is {}.", input, output) << endl;
        cout << output << endl;
    }

    vector<int> largestContiguousSequence(vector<int> &input) {
        unordered_map<int, int> map;
        int beg, end;
        int first = -1, last = -1;
        for (auto &e : input) {
            beg = end = e;
            if (map.find(e - 1) != map.end())
                beg = map[e - 1];
            if (map.find(e + 1) != map.end())
                end = map[e + 1];

            map[beg] = end;
            map[end] = beg;

            if (end - beg > last - first) {
                first = beg;
                last = end;
            }
        }

        vector<int> result;
        for (int i = first; i <= last; i++)
            result.push_back(i);

        return result;
    }
};