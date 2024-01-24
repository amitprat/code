#pragma once
#include "../Header.h"

class PrintEvenOddNumbersUsing2Threads {
	mutex m;
	condition_variable cv;
	int pos = 0;

public:
	static void test() {
		PrintEvenOddNumbersUsing2Threads obj;

		int arr[] = { 3,1 ,2, 5, 6, 7, 8, 10, 9 };
		int n = sizeof(arr) / sizeof(int);

		obj.printNumbers(arr, n);
	}

	void printNumbers(int arr[], int n) {
		thread t1(&PrintEvenOddNumbersUsing2Threads::printEvenNumbers, this, arr, n);
		thread t2(&PrintEvenOddNumbersUsing2Threads::printOddNumbers, this, arr, n);

		// another way of calling it
		//thread t1([arr, n, this]() {printEvenNumbers(arr, n);});
		//thread t1([arr, n, this]() {printOddNumbers(arr, n);});

		t1.join();
		t2.join();
	}

	void printEvenNumbers(int arr[], int n) {
		while (true) {
			unique_lock<mutex> lock(m);
			cv.wait(lock, [this, arr, n]() {return pos >= n || (arr[pos] & 1) == 0; });
			if (pos >= n) break;

			cout << "Even thread: " << arr[pos++] << endl;

			cv.notify_all();
		}
	}

	void printOddNumbers(int arr[], int n) {
		while (true) {
			unique_lock<mutex> lock(m);
			cv.wait(lock, [this, arr, n]() { return pos >= n || (arr[pos] & 1) == 1; });
			if (pos >= n) break;

			cout << "Odd thread: " << arr[pos++] << endl;

			cv.notify_all();
		}
	}
};