#pragma once
#include "../Header.h"

class PathInMatrix {
public:
	static void test() {
		vector<vector<int>> matrix =
		{
			{1, 0, 0, 0, 1, 0, 0, 0},
			{1, 1, 0, 0, 1, 1, 0, 0},
			{0, 1, 1, 0, 0, 1, 1, 0},
			{1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 1, 0, 0, 0},
			{1, 1, 0, 0, 1, 1, 0, 0},
			{0, 1, 1, 0, 0, 1, 1, 0},
			{1, 1, 1, 1, 1, 1, 1, 1}
		};

		srand(time(nullptr));
		cout << "Input matrix: " << to_string(matrix) << endl;

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				Point s = { i,j };
				Point e = { rand() % 4, rand() % 4 };

				vector<Point> res = findPath(matrix, s, e);
				vector<Point> res1 = findPathUsingDP(matrix, s, e);

				assert(res.size() == res1.size());
				cout << format("Minimum distance path from src={} to dst={} is {}", s.to_string(), e.to_string(), to_string(res)) << endl;
			}
		}
	}

	static vector<Point> findPath(vector<vector<int>> matrix, Point s, Point e) {
		if (matrix[s.x][s.y] == 0) return {};
		queue < pair<Point, vector<Point>>> q;
		q.push({ s, {s} });
		unordered_set<int> seen;
		int n = matrix.size();
		int m = matrix[0].size();
		seen.insert(s.x * m + s.y);

		while (!q.empty()) {
			auto u = q.front(); q.pop();
			if (u.first == e) return u.second;

			auto res = u.second;
			Point right = { u.first.x, u.first.y + 1 };
			Point down = { u.first.x + 1,u.first.y };

			if (right.y < m && matrix[right.x][right.y] && seen.find(right.x * m + right.y) == seen.end()) {
				res.push_back(right);
				q.push({ right, res });
				res.pop_back();
			}

			if (down.x < n && matrix[down.x][down.y] && seen.find(down.x * m + down.y) == seen.end()) {
				res.push_back(down);
				q.push({ down, res });
				res.pop_back();
			}
		}

		return {};
	}

	static vector<Point> findPathUsingDP(vector<vector<int>> matrix, Point s, Point e) {
		int n = matrix.size();
		if (n == 0) return {};

		int m = matrix[0].size();
		vector<vector<int>> dist(n, vector<int>(m));

		for (int i = s.x; i <= e.x; i++) {
			for (int j = s.y; j <= e.y; j++) {
				if (matrix[i][j] == 0) { dist[i][j] = INT_MAX; continue; }

				if (i == s.x && j == s.y) dist[i][j] = 0;
				else if (i == s.x) dist[i][j] = dist[i][j - 1] == INT_MAX ? INT_MAX : 1 + dist[i][j - 1];
				else if (j == s.y) dist[i][j] = dist[i - 1][j] == INT_MAX ? INT_MAX : 1 + dist[i - 1][j];
				else {
					int curMin = min(dist[i - 1][j], dist[i][j - 1]);
					dist[i][j] = curMin == INT_MAX ? INT_MAX : 1 + curMin;
				}
			}
		}

		vector<Point> result;
		int i = e.x, j = e.y;
		while (i >= s.x && j >= s.y && dist[i][j] != INT_MAX) {
			result.push_back({ i,j });
			if (i == s.x && j == s.y) break;
			if (i == s.x) j--;
			else if (j == s.y) i--;
			else if (dist[i - 1][j] < dist[i][j] && matrix[i - 1][j]) i--;
			else j--;
		}
		if (i != s.x || j != s.y) return {};

		reverse(result.begin(), result.end());

		return result;
	}
};