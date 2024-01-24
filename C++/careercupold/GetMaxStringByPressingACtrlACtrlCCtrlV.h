#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=7184083

1. A
2. Ctrl+A
3. Ctrl+C
4. Ctrl+V

If you can only press the keyboard for N times (with the above four keys), please write a program to produce maximum numbers of A. If possible, please also print out the sequence of keys.

So the input parameter is N (No. of keys that you can press), the output is M (No. of As that you can produce).


One more thing that came to my mind ...

#1: We know the first few solutions (for n=1 through n=9).

#2: We know what the k-cycles do (they multiply number of A's by (k-2).

#3: 10-cycle would multiply by 8 but 2 5-cycles would multiply by 3*3=9. Similarly for any k > 10. So we don't have to consider any cycle for k bigger than 10.

#4: 1-cycle, 2-cycle don't make sense, 3-cycle gets us to where we were 3 strokes ago. So these can be ignored.

#5: 4-cycle doubles NumAs so it can be included, but it won't be used because it's inefficient.

#6: Now we can use DP to find the optimum solution for n using the following function:


f(n) = max (
 2*f(n-4),
 3*f(n-5),
 4*f(n-6),
 5*f(n-7),
 6*f(n-8),
 7*f(n-9)
)
So here we go, a DP solution at last :-)

It should give the same answers as my non-DP solution above. Why?

Because:


3*3 > 4*2    5-cycle + 5-cycle gives more A's than 6-cycle + 4-cycle
4*4 > 5*3    6-cycle + 6-cycle gives more A's than 7-cycle + 5-cycle
5*4 > 6*3    7-cycle + 6-cycle gives more A's than 8-cycle + 5-cycle
6*4 > 7*3    8-cycle + 6-cycle gives more A's than 9-cycle + 5-cycle
Think about it :-)

*/
class GetMaxStringByPressingACtrlACtrlCCtrlV
{

};