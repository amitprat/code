#pragma once
#include "../Header.h"

class FindMissingNumber {
public:
	static void test() {
		{
			string str = "9799";
			int num = findMissingNumber(str);
			cout << format("Find missing number in {} is {}", str, num) << endl;
		}

		{
			string str = "9799100101102";
			int num = findMissingNumber(str);
			cout << format("Find missing number in {} is {}", str, num) << endl;
		}

		{
			string str = "979899100101102";
			int num = findMissingNumber(str);
			cout << format("Find missing number in {} is {}", str, num) << endl;
		}

		{
			string str = "979899100101103";
			int num = findMissingNumber(str);
			cout << format("Find missing number in {} is {}", str, num) << endl;
		}
	}

	static int findMissingNumber(string str) {
		int n = str.size();
		for (int i = 1; i <= n && i <= 7; i++) {
			int num = stoi(str.substr(0, i));

			int missingNum = -1;

			int j = i;
			for (; j + len(num + 1) <= n; j += len(num)) {
				int nextNum = stoi(str.substr(j, len(num + 1)));

				if (nextNum == num + 1) {
					num = nextNum;
				}
				else if (nextNum == num + 2 && missingNum == -1) {
					missingNum = num + 1;
					num = nextNum;
				}
				else {
					break;
				}
			}

			if (j == n) return missingNum == -1 ? (num + 1) : missingNum;
		}

		return -1;
	}

	static int len(int num) {
		return (int)(log10(num)) + 1;
	}
};