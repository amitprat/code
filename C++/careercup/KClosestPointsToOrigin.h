#pragma once
#include "../header.h"

class KClosestPointsToOrigin {
    struct Point {
        int x;
        int y;

        auto dist() const {
            return x * x + y * y;
        }
        auto operator<=(const Point& other) const {
            return dist() <= other.dist();
        }
    };

   public:
    static void test() {
        KClosestPointsToOrigin solution;

        vector<Point> points = {{1, 3}, {-2, 2}, {5, 8}, {0, 1}, {-1, -1}, {2, 2}, {3, 4}, {-3, -4}, {1, 1}, {-1, 0}};
        int k = 4;

        auto result = solution.kClosest(points, k);
        for (const auto& p : result) {
            cout << "[" << p.x << ", " << p.y << "] ";
        }
        cout << endl;
    }

   public:
    vector<Point> kClosest(vector<Point>& points, int k) {
        if (points.empty() || k == 0) return {};

        int p = quickSelect(points, 0, points.size() - 1, k);
        if (p == -1) return {};
        return {points.begin(), points.begin() + p + 1};
    }

    int quickSelect(vector<Point>& pointList, int left, int right, int k) {
        if (left > right) return -1;

        int pivot = partition(pointList, left, right);
        if (pivot - left + 1 == k) return pivot;
        else if (k < pivot - left + 1) return quickSelect(pointList, left, pivot - 1, k);
        else return quickSelect(pointList, pivot + 1, right, k - (pivot - left + 1));
    }

    int partition(vector<Point>& pointList, int left, int right) {
        Point pivot = pointList[right];
        int i = left;
        for (int j = left; j < right; j++) {
            if (pointList[j] <= pivot) {
                swap(pointList[i++], pointList[j]);
            }
        }
        swap(pointList[i], pointList[right]);

        return i;
    }
};