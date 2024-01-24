#pragma once
#include "../Header.h"

class ReverseBits {
public:
	static void test() {
		for (int i = 0; i < 25; i++) {
			cout << "Binary for " << i << endl;
			cout << to_bin(i) << endl << endl;

			cout << "Binary for reverse of " << i << endl;
			int rev1 = reversedBits1(i);
			int rev2 = reversedBits2(i);
			//int rev3 = reversedBits3(i);

			assert(rev1 == rev2);
			//assert(rev1 == rev3);
			cout << to_bin(rev1) << endl << endl;
		}
	}

	static int reversedBits1(int num) {
		int n = 32;
		int rev = 0;

		for (int i = 0; i < n; i++) {
			if (num & (1 << i)) rev |= (1 << (n - i - 1));
		}

		return rev;
	}

	static int reversedBits2(int num) {
		int n = 32 - 1;
		int rev = num;

		while (num) {
			rev |= (num & 1);
			num >>= 1;
			rev <<= 1;
			n--;
		}

		rev <<= n;

		return rev;
	}

	// reverse bits only in set bits range
	static int reversedBits3(int num) {
		int rev = 0;
		while (num) {
			rev <<= 1;
			rev |= num & 1;
			num >>= 1;
		}

		return rev;
	}
};