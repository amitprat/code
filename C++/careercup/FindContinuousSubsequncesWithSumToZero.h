#include "../header.h"

/*
https://careercup.com/question?id=5172027535130624

Given an array write a function to print all continuous subsequences in the array which sum of 0.
e.g:
Input:
Array = [-1, -3, 4, 5, 4]
output:
-1, -3, 4

There is another solution that works as following:

Array = [6, -1, -3, 4, 5, 4, -15, 7] then create another array that for position i - keeps the sum of all elements from [0, i] so that we get something like

SumArray = [6, 5, 2, 6, 11, 15, 0, 7]

Now by looking in the SumArray we can see that:
1) when 0 appears at i-position it means that from the begining of the array till i-th position we have a "zero sequence".
2) if there is a matching (two the same elements, like 6, 6 in our case) then we know that from [i+1,j], where i is the first and j is the second matching, the overall change was equall to zero, so we have a "zero sequence" again.
*/
class FindContinuousSubsequncesWithSumToZero {
};