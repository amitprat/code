#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=15072768

We define C(n) as the number of ways to take n identical objects out of a bucket, where objects may be taken 1, 2, or 3 at a time.

Example: C(4)=7, because you can take 4 objects in the following 7 ways:
1,1,1,1
2,1,1
1,2,1
1,1,2
2,2
3,1
1,3

Write a function for C(n) in the language of your choice.

C(0)=1
C(1)=1
C(2)=2
C(n)=C(n-3)+C(n-2)+C(n-1) (if n>2)

def C(n):
   L=[1,1,2]
   while n:
	   n-=1
	   new=L[0]+L[1]+L[2]
	   L[0]=L[1]
	   L[1]=L[2]
	   L[2]=new
   return L[0]
*/
class NumberOfWaysToSelectNIdenticalObjectsOutOfBucket
{
public:
	static void test() {
		int res = numberOfWays(4);
		cout << res << endl;
	}

	static int numberOfWays(int n)
	{
		int res[] = { 1,1,2 };
		while (n) {
			int tmp = res[0] + res[1] + res[2];
			res[0] = res[1];
			res[1] = res[2];
			res[2] = tmp;
			n--;
		}
		return res[0];
	}
};