#pragma once
#include "../Header.h"

class PrintArrayElementsInOrder {
	using T = tuple<int, int, int>;
	vector<vector<int>> input;
	priority_queue<T, vector<T>, greater<T>> pq;

public:
	PrintArrayElementsInOrder(vector<vector<int>> input) :input(input) {
		for (int i = 0; i < input.size(); i++) {
			if (!input[i].empty()) pq.push({ input[i][0] , i, 0 }); // compare by first element in tuple
		}
	}

	bool hasNext() {
		return !pq.empty();
	}

	int next() {
		auto item = pq.top(); pq.pop();
		auto curVal = get<0>(item);
		auto arrIdx = std::get<1>(item);
		auto nextPos = std::get<2>(item) + 1; // next position in this array

		if (nextPos < input[arrIdx].size()) { // not equalTo because that is end of array
			pq.push({ input[arrIdx][nextPos], arrIdx, nextPos });
		}

		return curVal;
	}

public:
	static void test() {
		vector<vector<int>> input = { {1, 5, 7}, {2, 3, 10}, {4, 6, 9 } };

		PrintArrayElementsInOrder obj(input);
		while (obj.hasNext()) {
			cout << obj.next() << " ";
		}
	}
};