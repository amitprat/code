#pragma once
#include "../Header.h"

class MixedProblems {
	class Permutations {
		string str;
	public:
		Permutations(string str) : str(str) {}

		bool hasNext() {
			if (str.length() == 1) return false;
			for (int i = str.length() - 1; i >= 1; i--) {
				if (str[i - 1] < str[i]) return true;
			}
			return false;
		}

		string next() {
			if (str.length() == 1) return str;

			// find first adjancent smaller element
			int l = str.length() - 2;
			while (l >= 0 && str[l] >= str[l + 1]) {
				l--;
			}
			if (l < 0) return "Not possible";

			// find next greater element
			int r = l + 1;
			int j = l + 1;
			while (j < str.length()) {
				if (str[j] > str[l] && str[j] < str[r]) r = j;
				j++;
			}

			// swap these two values
			swap(str[l], str[r]);
			//cout << l << " " << r << endl;

			// sort the str after l
			sort(str.begin() + l + 1, str.end());

			return str;
		}
	};

public:
	static void test()
	{
		// validate permutations
		{
			Permutations p("347226");
			while (p.hasNext()) { cout << p.next() << " "; }
			cout << endl;
		}
		cout << endl;

		MixedProblems obj;

		// Number of subarrays with product < k
		{
			vector<int> arr = { 1, 2, 3, 4 };
			int k = 20;
			int res = obj.numSubarrayProductLessThanK(arr, k);
			cout << format("Number of subarrays in {} with product less than {} are {}", to_string(arr), k, res) << endl;
		}
		cout << endl;

		// K closed point to given point
		{
			vector<Point> points = { {1,2},{3,1},{0,2},{1,1},{3,4},{1,0},{0,1},{0,0} };
			int k = 5;
			Point p = { 0,0 };
			auto res = obj.kClosest(points, { 0,0 }, 5);
			cout << format("{} closed points to {} in point set {} are {}", k, p.to_string(), to_string(points), to_string(res)) << endl;
		}
		cout << endl;

		// Total time covered by overlapping intervals
		{
			vector<Interval> intervals = { {1,4}, {6,8}, {2,4}, {7,9}, {10, 15} };
			auto res = obj.totalIntervalCovered(intervals);
			cout << format("Total time covered by intervals {} is {}", to_string(intervals), res) << endl;
		}
		cout << endl;

		{
			cout << "Generate arragement of numbers:" << endl;
			obj.permutationDistance(3);
		}
		cout << endl;

		{
			vector<int> input = { 2,3,1,4 };
			auto res = obj.multiplyExceptSelf(input);
			cout << format("Multiply array elements except self, before {}, after {}", to_string(input), to_string(res)) << endl;
		}
		cout << endl;
	}

private:
	int numSubarrayProductLessThanK(vector<int>& arr, int k) {
		int prod = 1;
		int s = 0, e = 0;
		int res = 0;
		while (s <= e && e <= arr.size()) {
			if (prod <= k) {
				if (prod <= k) res += (e - s); // this is correct because we need to consider all subarrays
				if (e < arr.size()) prod *= arr[e];
				e++;
			}
			else {
				prod /= arr[s++];
			}
		}

		return res;
	}

	int distance(Point p1, Point p2) {
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}

	int partition(vector<Point>& points, int l, int r, Point origin) {
		int i = 0;
		int pivotDistance = distance(origin, points[r]);
		for (int j = i; j < r; j++) {
			if (distance(points[j], origin) <= pivotDistance) {
				swap(points[j], points[i++]);
			}
		}
		swap(points[i], points[r]);

		return i;
	}

	int selectionAlgorithm(vector<Point>& points, int l, int r, Point source, int k) {
		int p = partition(points, l, r, source);
		int q = p - l + 1;
		if (q == k) return p;

		if (q < k) return selectionAlgorithm(points, p + 1, r, source, k - q);
		return selectionAlgorithm(points, l, p - 1, source, k);
	}

	vector<Point> kClosest(vector<Point> points, Point source, int k) {
		int l = 0, r = points.size() - 1;
		auto p = selectionAlgorithm(points, l, r, source, k);

		return { points.begin(), points.begin() + p + 1 };
	}

	int totalIntervalCovered(vector<Interval>& intervals) {
		sort(intervals.begin(), intervals.end(), [](const auto& f, const auto& s) {
			return f.start < s.start;
			});
		int timeCovered = 0;
		int last = 0;
		for (auto it : intervals) {
			timeCovered += max(it.end - max(last, it.start), 0);
			last = max(last, it.end);
		}

		return timeCovered;
	}

	bool generatePermutation(vector<int>& arr, unordered_set<int> visited, int n)
	{
		if (visited.size() == n) return true;

		for (int i = 1; i <= n; i++) {
			if (visited.find(i) != visited.end()) continue;
			for (int j = 0; j < arr.size() - i - 1; j++) {
				if (arr[j] == 0 && arr[j + i + 1] == 0) {
					arr[j] = arr[j + i + 1] = i;
					visited.insert(i);
					if (generatePermutation(arr, visited, n)) return true;
					arr[j] = arr[j + i + 1] = 0;
					visited.erase(i);
				}
			}
		}

		return false;
	}

	void permutationDistance(int n) {
		vector<int> arr(2 * n, 0);
		unordered_set<int> visited;

		bool res = generatePermutation(arr, visited, n);
		if (res) {
			cout << "Permutations: ";
			for (int i = 0; i < 2 * n; i++) cout << arr[i] << " ";
			cout << endl;
		}
		else {
			cout << "Not possible" << endl;
		}
	}

	vector<int> multiplyExceptSelf(vector<int> arr) {
		int n = arr.size();
		int l = 1;
		int r = 1;

		vector<int> output(arr.size(), 1);

		for (int i = 0; i < n; i++) {
			output[i] *= l;
			output[n - i - 1] *= r;

			l *= arr[i];
			r *= arr[n - i - 1];
		}
		return output;
	}
};