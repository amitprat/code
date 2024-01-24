#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5176833186201600

You are given a positive integer number N. Return the minimum number K, such that N can be represented as K integer squares.
Examples:
9 --> 1 (9 = 3^2)
8 --> 2 (8 = 4^2 + 4^2)
15 --> 4 (15 = 3^2 + 2^2 + 1^2 + 1^2)
First reach a solution without any assumptions, then you can improve it using this mathematical lemma: For any positive integer N, there is at least one representation of N as 4 or less squares.
*/
class MinimumSquareSum
{
public:
	static void test() {
		vector<int> nums = { 9,8,15,1,43,5,2,4,6,234,35,2 };
		for (int num : nums) {
			int res = minSquareSum(num);
			cout << num << " = " << res << endl;
		}
	}

	static int minSquareSum(int num) {
		auto res1 = minSquareSumRecursive(num);
		auto res2 = minSquareSumDP(num);

		assert(res1 == res2);

		return res1;
	}

	static int minSquareSumRecursive(int num) {
		if (num == 0) return 0;

		int r = sqrt(num);
		int cnt = 999;
		for (int j = r; j >= 1; j--) {
			cnt = min(cnt, 1 + minSquareSumRecursive(num - j * j));
		}

		return cnt;
	}

	static int minSquareSumDP(int num) {
		vector<int> dp(num + 1);
		for (int i = 0; i <= num; i++) dp[i] = i;

		for (int i = 1; i * i <= num; i++) {
			for (int j = i * i; j <= num; j++) {
				dp[j] = min(dp[j], 1 + dp[j - i * i]);
			}
		}

		return dp[num];
	}

	/*
	Since nobody has solved the math portion, let me explain that to use the mathematical lemma that for any positive integer N there is at least one representation of N with at 4 or less squares, we can define nonnegative integers a, b, c, and d such that a>=b>=c>=d. Without proof I claim the following: a must lie in the range {floor(sqrt(N)),ceil(sqrt(N/4)}, b must lie in the range {floor(sqrt(N-a*a)),ceil(sqrt((N-a*a)/3)}, c must lie in the range {floor(sqrt(N-a*a-b*b)),ceil(sqrt((N-a*a-b*b)/2))}, and d must equal N-a*a-b*b-c*c. As a result this reduces our problem to finding values of a, b, and c within these given ranges to find the minimum solution. We already know it is possible to represent N with 4 squares so the goal is instead we can focus on finding values of a and b such that N-a*a-b*b is the square of an integer because if this is true then we can represent N as 3 or less squares. The time complexity of the algorithm becomes O(sqrt(N)*sqrt(N)) which is equivalent to O(N) because we only need to iterate over values of a and b. Also we can exit the function early if N is the square of an integer, otherwise we can exit early if there exist a and b such that N=a*a+b*b. If we use the Math.sqrt function then this might cause floating point errors, but to make things simpler I will assume we can ignore this for now. The following Java code implements this strategy:


	public static int minSquares(int N) {
		int K = 4;
		for (int a = (int)Math.sqrt(N); i >= (int)Math.sqrt(N/4.0); i--) {
			int aSquared = a*a;
			if (aSquared == N) {
				return 1;
			}
			for (int b = (int)Math.sqrt(N-aSquared); b >= (int)Math.sqrt((N-aSquared)/3.0); b--) {
				int bSquared = b*b;
				int currSum = aSquared + bSquared;
				if (currSum == N) {
					return 2;
				}
				int cSquared = N - currSum;
				double c = Math.sqrt(cSquared);
				if (c == Math.floor(c)) {
					K = 3;
				}
			}
		}
		return K;
	}
	*/
};