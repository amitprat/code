#include "../header.h"

/*
https://www.careercup.com/question?id=19286669

Given life time of different animals. Find period when maximum number of animals lived. ex [5, 11], [6, 18], [2, 5],[3,12] etc. year in which max no animals exists.

Input intervals (or lifetimes): [5, 11], [6, 18], [2, 5], [3,12]

1. Put the end and start times of the intervals in one array. Sort it!. Always put the start time before end time in case they are equal. Maintain flags to identify a start/end interval. For above input I'll do something like:
2S, 3S, 5S, 5E, 6S, 11E, 12E, 18E

2. Now scan the array from left to right keeping track of how many intervals we are in. (This would be equal to total numbers of start intervals - total number of end intervals encountered so far). For above input I'll get something like:
1, 2, 3, 2, 3, 2, 1, 0

3. Now pick the maxima points from step 2. All the maxima points will be Start intervals and the point next to a maxima point will always be an end interval (which will be the end of the maxima start interval). So we'll get:
[5S,5E] and [6S,11E].

Hence the result is [5,5], [6,11]

Time complexity = O(nLogn), because of sorting in step 1.
Space complexity = O(n)
*/
class MaximumAnimalLivedPeriod {
};