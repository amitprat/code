#pragma once
#include "../header.h"
#include "ds/PriorityQueue.h"

/*
https://careercup.com/question?id=5309537623998464

Given a set of 2D points, some integer k, find the k points closest to the origin, (0,0).

There are n points on a 2D plan, find the k points that are closest to origin ( x=0, y=0)

You can do it in O(n), but you have to avoid heaps.
First build an array with the distances to the origin and the corresponding point. O(n)
Then find the Kth largest distance using the Selection algorithm. O(n)
The K-1 smallest distances are to the left of the Kth distance, in no particular order.
*/

class KClosestPointsIn2DArray {
   public:
    static void test() {
        KClosestPointsIn2DArray obj;
        vector<Point> points;
        points.push_back(Point(3, 2));
        points.push_back(Point(2, 1));
        points.push_back(Point(2, 4));
        points.push_back(Point(1, 1));
        points.push_back(Point(2, 2));

        Point origin(0, 0);
        int k = 3;
        {
            cout << "K Closest points using heap: ";
            vector<Point> result = obj.kClosestPointsUsingHeap(points, origin, k);
            cout << result << endl;
        }

        {
            cout << "K Closest points using partitioning: ";
            vector<Point> result = obj.kClosestPointsUsingPartition(points, origin, k);
            cout << result << endl;
        }

        {
            cout << "K Closest points using priority queue: ";
            vector<Point> result = obj.kClosestPointsUsingPriorityQueue(points, origin, k);
            cout << result << endl;
        }
    }

   private:
    vector<Point> kClosestPointsUsingPriorityQueue(vector<Point> &points, Point &origin, int k) {
        // prepare minheap of {distance, Point}
        using P = pair<double, Point>;
        auto comp = [&](auto &l, auto &r) { return l.first < r.first; };
        priority_queue<P, vector<P>, decltype(comp)> pq(comp);

        // insert first k points
        for (int i = 0; i < k; i++) {
            double dist = this->distance(origin, points[i]);
            pq.push({dist, points[i]});
        }

        // consider each point one by one and keep updating the new top on heap.
        for (int i = k; i < points.size(); i++) {
            double dist = this->distance(origin, points[i]);
            if (dist < pq.top().first) {  // if new point is closer than point with min distance (on top of heap)
                pq.pop();
                pq.push({dist, points[i]});
            }
        }

        // create result
        vector<Point> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    double distance(Point p1, Point p2) {
        return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
    }

   private:
    vector<Point> kClosestPointsUsingPartition(vector<Point> &points, Point &origin, int k) {
        vector<pair<double, Point>> distances = getDistances(points, origin);

        // partition distances array such that smallest k points are on left.
        int p = kClosestPointsUsingPartition(distances, 0, distances.size() - 1, k);

        // sort the part of vector only
        sort(distances.begin(), distances.begin() + p + 1, [](const auto &f, const auto &s) { return f.first < s.first; });

        // get result.
        vector<Point> result;
        for (int i = 0; i <= p; i++) {
            result.push_back(distances[i].second);
        }

        return result;
    }

    int kClosestPointsUsingPartition(vector<pair<double, Point>> &distances, int l, int r, int k) {
        if (l > r) return -1;

        int p = partition(distances, l, r);
        int q = p - l + 1;

        if (q == k)
            return p;
        else if (q < k)
            return kClosestPointsUsingPartition(distances, p + 1, r, k - q);
        else
            return kClosestPointsUsingPartition(distances, l, p - 1, k);
    }

    int partition(vector<pair<double, Point>> &distances, int l, int r) {
        int pivot = distances[r].first;
        int low = l;
        for (int i = l; i < r; i++) {
            if (distances[i].first <= pivot) {
                swap(distances[low], distances[i]);
                low++;
            }
        }
        swap(distances[low], distances[r]);

        return low;
    }

    vector<pair<double, Point>> getDistances(vector<Point> &points, Point &origin) {
        vector<pair<double, Point>> result;
        for (auto &p : points) {
            result.push_back({this->distance(origin, p), p});
        }

        return result;
    }

   private:
    vector<Point> kClosestPointsUsingHeap(vector<Point> &points, Point &origin, int k) {
        using P = pair<double, Point>;
        auto compare = [](const auto &first, const auto &second) -> bool { return first.first > second.first; };
        PriorityQueue<P> heap(compare);

        vector<P> pointDistancePairs = getDistances(points, origin);

        for (auto &pointDistancePair : pointDistancePairs) {
            if (heap.size() >= k && heap.top().first > pointDistancePair.first) {
                heap.pop();
            }
            if (heap.size() < k) heap.insert(pointDistancePair);
        }

        // get result.
        vector<Point> result;
        while (!heap.empty()) {
            result.push_back(heap.pop().second);
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};