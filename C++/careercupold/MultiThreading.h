#pragma once
#include "../Header.h"

class MultiThreading {
	class PrintEvenOdd {
		mutex m;
		condition_variable cv;
		int cnt = 0;

		void printEven(int mx) {
			while (cnt < mx) {
				unique_lock<mutex> lock(m);
				cv.wait(lock, [this]() { return (cnt & 1) == 0; });

				cout << cnt++ << " ";
				cv.notify_all();
			}
		}

		void printOdd(int mx) {
			while (cnt < mx) {
				unique_lock<mutex> lock(m);
				cv.wait(lock, [this]() { return (cnt & 1) == 1; });

				cout << cnt++ << " ";
				cv.notify_all();
			}
		}

	public:
		void printEvenOdd(int mx) {
			thread evenThread(&PrintEvenOdd::printEven, this, mx);
			thread oddThread(&PrintEvenOdd::printOdd, this, mx);

			evenThread.join();
			oddThread.join();
		}
	};

	class PrintEvenOddPredicate {
		int cnt = 0;
		mutex m;
		condition_variable cv;

		void printMethod(function<bool()> predicate, int mx) {
			while (cnt < mx) {
				unique_lock<mutex> lock(m);
				cv.wait(lock, [this, predicate]() {return predicate(); });

				cout << cnt++ << " ";
				cv.notify_all();
			}
		}
	public:
		void printEvenOdd(int mx) {
			auto evenPredicate = [this]() {return (cnt & 1) == 0; };
			auto oddPredicate = [this]() {return (cnt & 1) == 1; };

			thread evenThread(&PrintEvenOddPredicate::printMethod, this, evenPredicate, mx);
			thread oddThread(&PrintEvenOddPredicate::printMethod, this, oddPredicate, mx);

			evenThread.join();
			oddThread.join();
		}
	};

	class Print012WithPredicate {
		int mxcnt = 0;
		int cnt = 0;
		mutex m;
		condition_variable cv;

		void printMethod(function<bool()> predicate, int mx) {
			while (mxcnt < mx) {
				unique_lock<mutex> lock(m);
				cv.wait(lock, [this, predicate]() { return predicate(); });

				cout << cnt << " ";
				cnt = (cnt + 1) % 3;
				mxcnt++;

				cv.notify_all();
			}
		}
	public:
		void print012(int mx) {
			auto printZeroPredicate = [this]() {return cnt == 0; };
			auto printOnePredicate = [this]() {return cnt == 1; };
			auto printTwoPredicate = [this]() {return cnt == 2; };

			thread zeroThread(&Print012WithPredicate::printMethod, this, printZeroPredicate, mx);
			thread oneThread(&Print012WithPredicate::printMethod, this, printOnePredicate, mx);
			thread twoThread(&Print012WithPredicate::printMethod, this, printTwoPredicate, mx);

			zeroThread.join();
			oneThread.join();
			twoThread.join();
		}
	};

	class AccessArrayElementsInOrder {
		vector<int> arr1, arr2, arr3;
		bool printFirst = true;
		bool printSecond = false;
		bool printThird = false;
		int cur1 = 0, cur2 = 0, cur3 = 0, total = 0;

		mutex m;
		condition_variable cv;

		void printInorder(function<bool()> predicate, function<void()> action, function<void()> next)
		{
			while (total < 100) {
				unique_lock<mutex> lock(m);
				cv.wait(lock, [predicate]() { return predicate(); });

				action();
				next();

				cv.notify_all();
			}
		}

	public:
		void test() {
			for (int i = 0; i <= 102; i += 3) arr1.push_back(i);
			for (int i = 1; i <= 102; i += 3) arr2.push_back(i);
			for (int i = 2; i <= 102; i += 3) arr3.push_back(i);

			auto pred1 = [this]() { return printFirst; };
			auto pred2 = [this]() { return printSecond; };
			auto pred3 = [this]() { return printThird; };
			auto action1 = [this]() { cout << arr1[cur1++] << " "; total++; };
			auto action2 = [this]() { cout << arr2[cur2++] << " "; total++; };
			auto action3 = [this]() { cout << arr3[cur3++] << " "; total++; };
			auto next1 = [this]() { printFirst = false;  printSecond = true; };
			auto next2 = [this]() { printSecond = false;  printThird = true; };
			auto next3 = [this]() { printThird = false;  printFirst = true; };

			thread t1(&AccessArrayElementsInOrder::printInorder, this, pred1, action1, next1);
			thread t2(&AccessArrayElementsInOrder::printInorder, this, pred2, action2, next2);
			thread t3(&AccessArrayElementsInOrder::printInorder, this, pred3, action3, next3);

			t1.join();
			t2.join();
			t3.join();
		}
	};

	template <class T>
	class BoundedQueue
	{
		queue<T> q;
		mutex m;
		condition_variable cv;
		int n;

	public:
		BoundedQueue(int n) : n(n) {}

		void add(T item) {
			unique_lock<mutex> lock(m);
			cv.wait(lock, [this]() {return q.size() != n; });

			q.push(item);
			cv.notify_all();
		}

		T front() {
			shared_lock<mutex> lock(m);
			cv.wait(lock, [this]() {return !q.empty(); });

			auto res = q.front();
			cv.notify_all();

			return res;
		}

		T pop() {
			unique_lock<mutex> lock(m);
			cv.wait(lock, [this]() {return !q.empty(); });

			auto res = q.front(); q.pop();
			cv.notify_all();

			return res;
		}

		static void test() {
			BoundedQueue<int> obj(10);
			thread write1, write2, write3;
			thread read1, read2, read3;

			write1 = thread([&obj]() {obj.add(1); });
			write2 = thread([&obj]() {obj.add(2); });

			read1 = thread([&obj]() {cout << obj.pop(); });
			read2 = thread([&obj]() {cout << obj.pop(); });
			read3 = thread([&obj]() {cout << obj.pop(); });

			write3 = thread([&obj]() {obj.add(3); });

			write1.join();
			write2.join();
			write3.join();

			read1.join();
			read2.join();
			read3.join();

		}
	};

public:
	static void test() {
		cout << "Print even odd using lambda: " << endl;
		MultiThreading obj;
		int n = 100;
		obj.printEvenOdd(n);
		cout << endl << endl;

		cout << "Print even odd using seperate class: " << endl;
		PrintEvenOdd printEvenOdd;
		printEvenOdd.printEvenOdd(100);
		cout << endl << endl;

		cout << "Print even odd using seperate class with predicate support: " << endl;
		PrintEvenOddPredicate printEvenOddWithPredicate;
		printEvenOddWithPredicate.printEvenOdd(100);
		cout << endl << endl;

		cout << "Print even odd using seperate class with predicate support: " << endl;
		Print012WithPredicate print012;
		print012.print012(100);
		cout << endl << endl;

		cout << "Access Array elements in order " << endl;
		AccessArrayElementsInOrder printOrderElements;
		printOrderElements.test();
		cout << endl << endl;

		cout << "Bounded queue access " << endl;
		BoundedQueue<int>::test();
		cout << endl << endl;
	}

	void printEvenOdd(int mx) {
		mutex m;
		condition_variable cv;
		volatile int cnt = 0;

		thread printEvenThread([&cnt, mx, &m, &cv]() {
			while (cnt < mx) {
				unique_lock<mutex> lock(m);
				cv.wait(lock, [&cnt]() {
					return (cnt & 1) == 0;
					});

				cout << cnt++ << " ";

				cv.notify_one();
			}
			});

		thread printOddThread([&cnt, mx, &m, &cv]() {
			while (cnt < mx) {
				unique_lock<mutex> lock(m);
				cv.wait(lock, [&cnt]() {
					return (cnt & 1) == 1;
					});

				cout << cnt++ << " ";

				cv.notify_one();
			}
			});

		printEvenThread.join();
		printOddThread.join();
	}
};