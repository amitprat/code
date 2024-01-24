#include "../header.h"

/*
https://careercup.com/question?id=21630672
Given a list of integers, find out the biggest interval that has all its members in the given list. e.g. given list 1, 7, 4, 6, 3, 10, 2 then answer would be [1, 4]. Develop algorithm and write code for this

static int[] largestRange(int[] array) {
    int[] range = {0, -1};
    HashSet<int> set = new HashSet<int>();
    foreach (int i in array)  // O(n)
        set.Add(i);

    while (set.Count > 0)  // each element gets tested once.  Misses happen at most 2 times per entry (when there are no contiguous numbers) so the worst case is O(3n) for this part when largest range is length 1.
    {
        int j = set.First();
        set.Remove(j);
        int a, b;
        // iterate backwards and forwards from j
        for (a = j; set.Count > 0; a--) {
            if (!set.Contains(a - 1))
                break;
            set.Remove(a - 1);
        }
        for (b = j; set.Count > 0; b++) {
            if (!set.Contains(b + 1))
                break;
            set.Remove(b + 1);
        }
        if (b - a > range[1] - range[0]) {
            range[0] = a;
            range[1] = b;
        }
    }
    return range;
}
*/

class FindBiggestIntervalContainingAllElementsOfList {
};