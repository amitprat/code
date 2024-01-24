#include "../header.h"

/*
https://careercup.com/question?id=5681516425248768

Given: sorted array of integers
Return: sorted array of squares of those integers
Ex: [1,3,5] -> [1,9,25]

Integers can be negative.

1 approach

1) sort array by abs(x) as key (e.g. [1,2,3,-4,5,-6])
2) return [x**2 for x in array]

O(n log n) time
O(1) additional space

2 approach

1) do sqr for all negative and reverse list, do sqr for positive
2) merge 2 arrays like in merge sort but only 1 iteration needed

O(n) time
O(n) additional space (because of merge)

Actually it IS possible to do merge in linear time and constant extra space. By algorithm is not trivial :)

Google for it: Bing-Chao Huang, Michael A. Langston, “Practical In-Place Merging” (1988).

So best solution will be:
O(n) time
O(1) extra space
*/
class SquareOfSortedArray {
};