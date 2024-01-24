#include "../Header.h"

/*
Given a list of arrays of time intervals, write a function that calculates the total amount of time covered by the intervals.
For example:
input = [(1,4), (2,3)]
return 3
input = [(4,6), (1,2)]
return 3
input = {{1,4}, {6,8}, {2,4}, {7,9}, {10, 15}}
return 11
*/

static int mergeSegments(int[][] segments)
{
    Arrays.sort(segments, (x, y)->x[0] - y[0]);

    int result = 0;
    int last = 0;
    for (int[] seg : segments)
    {
        result += Math.max(seg[1] - Math.max(last, seg[0]), 0);
        last = Math.max(last, seg[1]);
    }
    return result;
}