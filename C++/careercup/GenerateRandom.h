#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=6065702117048320

Implement below function.
int getRandom(int N, int K[])

Constraints:
->K is sorted and contains elements in range [0,N)
->Output should be a random number between [0,N) excuding elements from K
->probability of generated number should be 1/(N-K.length) and not 1/N
-->int uniform(int N) is given which returns random number [0,N) with 1/N probability for each number.
->No more than O(1) memory
->No more than O(N) time

Below is my solution but it uses O(N) space.


public int randomNumber(int N, int[] K) { // K is sorted

	//assumed size of K is less than N
	int remains[] = new int[N-K.length];
	//i is index [0,N-1], j is an index of K, k is an index of remainings
	//Fill remaining array
	for (int i=0,j=0,k=0;i<N;i++){
		if (i!=K[j]){
			remainings[k++]=i;
		}else{
			j++;
		}
	}
	int index = uniform(remainings.length);
	return remainings[index];
}

Time complexity: O(N)
Space Complexity: O(N)
*/
class GenerateRandom
{
public:
	GenerateRandom() {
		srand(time(nullptr));
	}

	static void test() {
		vector<int> excludeElements = { 1,3,4,5 };
		int n = 6;

		cout << randomNumber(n, excludeElements) << endl;

		cout << randomNumber2(n, excludeElements) << endl;
	}

	static int randomNumber(int n, vector<int> excludeArr) {
		int m = n - excludeArr.size();
		int* remains = new int[n];
		for (int i = 0, j = 0, k = 0; i < n; i++) {
			if (i != excludeArr[j]) {
				remains[k++] = i;
			}
			else {
				j++;
			}
		}
		int index = rand() % m;;
		return remains[index];
	}

	/*
	I'm assuming numbers between 1 and N.
	Generate a random number X in the range 1..N-K.length. Then, process the K array while we haven't seen X numbers.

	runtime O(K), O(1) space
	*/
	static int randomNumber2(int n, vector<int> excludeArr) {
		int m = n - excludeArr.size();
		int x = rand() % m;
		int last = 0, i;
		for (i = 0; i < excludeArr.size(); i++) {
			if (excludeArr[i] - last > x)
				return x + last;
			x -= (excludeArr[i] - last - 1);
			last = excludeArr[i];
		}
		return x + excludeArr[excludeArr.size() - 1];
	}
};