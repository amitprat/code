#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=4834279194361856

You are given an array of integers 'a' that can fit in a memory. Write a method that retuns an array of the same lenght
such that each element 'i' of this array is a sum of 'a' except the element a[i]. You are not allowed to use '-' operator.

I get an idea:
first , fill the new array like this:
arr[i] = sum(a[0,i-1])
This can be done in O(n) in a for loop
Then, reversely do the operation, and add result to the previous arr.
I'll try program this out,, but have to say,, always easier to think than do it for me..

Simple code:
from random import randint

a = []
for i in xrange(randint(5,10), randint(50,60)):
    a.append(randint(1,100))

res = [0] * len(a)

sm = a[0]

for i in xrange(1, len(res)):
    res[i] = sm
    sm += a[i]

sm = a[len(a)-1]
for i in xrange(len(res)-2, -1, -1):
    res[i] += sm
    sm += a[i]

print sum(a)
print a
print res
*/

class SumOfAllElementsExceptItSelf {
};