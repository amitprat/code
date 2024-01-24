#include "../Header.h"

/*
A program stores total order numbers arrived at different time. For example, at 1.15 pm the program got 15 order,
 at 1.30 pm, the program got 20 order and so on.Now we need to design the data structure so that we can query the
  total orders we got in a time range efficiently. For this example, we can query as How many orders we have got 
  between 1 and 2 pm? Ans will be 15+ 20 = 35
*/

/*
You need a binary tree or equivalent representation that stores the total number of orders before the point in time.
 Then you simply do a binary search to find the node just before the time range and a binary search to find the node
  before the end of the time range and subtract the start from the beginning. Total time is O(log n).

You should do cumulative sum array and take the diff. You can do it by recording the sum at every given moment or just by
 attaching the new cumulative sum and the time. In the latter case you also need a binary search so it becomes logn, in the
  first case you get constant time complexity.
*/