#pragma once
#include "../Header.h"

class ProbabilityOfBeingAlive {
	template <class T>
	class Island {
	public:
		Point top, bottom;
		Island(Point top, Point bottom) :top(top), bottom(bottom) {}
		string to_string() {
			return "{" + top.to_string() + ", " + bottom.to_string() + "}";
		}
		bool isValid(Point p) {
			return p.x >= top.x && p.y >= top.y && p.y <= bottom.x && p.y <= bottom.y;
		}
	};
public:
	static void test() {
		ProbabilityOfBeingAlive obj;
		int n = 8;
		int steps = 12;
		Point p(3, 5);
		Island<int> island({ 0, 0 }, { n - 1, n - 1 });
		unordered_map<string, float> memo;

		auto res = obj.probability(island, p, steps, memo);
		cout << "Probility = " << res << endl;
	}

	float probability(Island<int> island, Point pos, int step, unordered_map<string, float>& memo) {
		if (!island.isValid(pos)) return 0;
		if (step == 0) return 1.0;
		string k = key(pos, step);
		if (memo.find(k) != memo.end()) return memo[k];
		memo[k] = 0.25 * probability(island, pos + Point{ -1, 0 }, step - 1, memo)
			+ 0.25 * probability(island, pos + Point{ 1, 0 }, step - 1, memo)
			+ 0.25 * probability(island, pos + Point{ 0, 1 }, step - 1, memo)
			+ 0.25 * probability(island, pos + Point{ 0, -1 }, step - 1, memo);

		return memo[k];
	}

	string key(Point pos, int step) {
		string  k = "key=(";
		k += pos.to_string();
		k += ", " + std::to_string(step);
		k += ")";
		return k;
	}
};