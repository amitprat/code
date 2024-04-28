#pragma once
#include "../header.h"

class SortArrByFrequency {
   public:
    static void test() {
        SortArrByFrequency obj;
        vector<int> arr = {4, 1, 2, 3, 5, 2, 5, 2, 1};
        auto res1 = obj.sortArrUsingMap(arr);
        auto res2 = obj.sortArrUsingPQ(arr);
        auto res3 = obj.sortArrUsingQuickSort(arr);
        assert(areEqual(res1, res2));
        assert(areEqual(res1, res3));
        cout << res1 << endl;
    }

   public:
    vector<int> sortArrUsingMap(vector<int>& arr) {
        unordered_map<int, int> freqMap;
        for (auto& e : arr) freqMap[e]++;

        vector<pair<int, int>> elements;
        for (auto& e : freqMap) {
            elements.push_back({e.first, e.second});
        }

        sort(elements.begin(), elements.end(), [](const auto& first, const auto& second) {
            if (first.second != second.second) return first.second > second.second;
            return first.first < second.first;
        });

        vector<int> output;
        for (auto& e : elements) {
            output.push_back(e.first);
        }

        return output;
    }

   public:
    vector<int> sortArrUsingPQ(vector<int>& arr) {
        unordered_map<int, int> freqMap;
        for (auto& e : arr) freqMap[e]++;

        auto compare = [](const auto& first, const auto& second) {
            if (first.second != second.second) return first.second < second.second;
            return first.first > second.first;
        };
        using P = pair<int, int>;
        priority_queue<P, vector<P>, decltype(compare)> pq;

        for (auto& e : freqMap) {
            pq.push({e.first, e.second});
        }

        vector<int> output;
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            output.push_back(cur.first);
        }

        return output;
    }

   public:
    vector<int> sortArrUsingQuickSort(vector<int>& arr) {
        unordered_map<int, int> freqMap;
        for (auto& e : arr) freqMap[e]++;

        vector<pair<int, int>> elementsByFreq;
        for (auto& e : freqMap) {
            elementsByFreq.push_back(e);
        }

        quickSort(elementsByFreq, 0, elementsByFreq.size());

        vector<int> output;
        for (auto& e : elementsByFreq) {
            output.push_back(e.first);
        }

        return output;
    }

    void quickSort(vector<pair<int, int>>& elementsByFreq, int s, int e) {
        if (s >= e) return;

        int p = partition(elementsByFreq, s, e);
        quickSort(elementsByFreq, s, p - 1);
        quickSort(elementsByFreq, p + 1, e);
    }

    int partition(vector<pair<int, int>>& elementsByFreq, int s, int e) {
        auto pivot = elementsByFreq[e];

        auto compare = [&](const auto& first, const auto& second) {
            if (first.second != second.second) return first.second > second.second;
            return first.first < second.first;
        };

        int i = s;
        for (int j = s; j < e; j++) {
            if (compare(elementsByFreq[j], pivot)) {
                swap(elementsByFreq[i], elementsByFreq[j]);
                i++;
            }
        }
        swap(elementsByFreq[i], elementsByFreq[e]);

        return i;
    }
};