#pragma once
#include "../Header.h"

class PrintKWordsFromList {
	template <class T>
	class CircularQueue {
	public:
		T* arr = nullptr;
		int size, capacity;
		int start, end;
		CircularQueue(int k) :capacity(k) {
			arr = new T[k];
			size = start = end = 0;
		}
		void push(T val) {
			if (isFull()) pop();
			auto s = index(end++);
			arr[s] = val;
			size++;
		}
		T front() {
			if (empty()) throw exception("Queue is empty");
			return arr[index(start)];
		}
		T pop() {
			if (empty()) throw exception("Queue is empty");
			T res = arr[index(start++)];
			if (start == end) start = end = 0;
			size--;
			return res;
		}
		bool empty() {
			return size == 0;
		}
		bool isFull() {
			return size == capacity;
		}
		int index(int cur) {
			return (cur % capacity);
		}
	};
public:
	static void test() {
		PrintKWordsFromList obj;
		vector<string> input = {
			"aaa",
			"bbb",
			"ccc",
			"booking",
			"alpha",
			"beta",
			"gamma"
		};

		{
			auto res = obj.getKWords(input, "booking", 3);
			cout << to_string(res) << endl;
		}

		{
			auto res = obj.getKWords(input, "alpha", 6);
			cout << to_string(res) << endl;
		}

		{
			auto res = obj.getKWords(input, "beta", 4);
			cout << to_string(res) << endl;
		}

		{
			auto res = obj.getKWords(input, "gamma", 2);
			cout << to_string(res) << endl;
		}
	}

	vector<string> getKWords(vector<string> input, string target, int k) {
		CircularQueue<string> queue(k);
		for (auto word : input) {
			queue.push(word);
			if (word == target) break;
		}

		vector<string> result;
		while (!queue.empty()) {
			result.push_back(queue.front()); queue.pop();
		}
		return result;
	}
};