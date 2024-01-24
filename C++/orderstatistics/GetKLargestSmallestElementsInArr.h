#pragma once
#include "../Header.h"
using namespace std;

class GetKLargestSmallestElementsInArr
{
public:
    static void test()
    {
        GetKLargestSmallestElementsInArr obj;
        vector<pair<vector<int>, int>> inputs = {
            {{1,3,2,5,23,62,42,3}, 1},
            {{3,6,23,6,34,24,6,6,23}, 4},
            {{3,42,5,2,42,3,2,52,5,23}, 7}
        };

        for (auto& input : inputs) {
            cout << "Processing: {{";
            for (auto j : input.first) cout << j << " ";
            cout << "}, " << input.second << "} : ";
            auto res = obj.klargest(input.first, input.second);
            cout << "KLargest = {";
            for (auto j : res) cout << j << " ";
            cout << "}, ";

            res = obj.ksmallest(input.first, input.second);
            cout << "KSmallest = {";
            for (auto j : res) cout << j << " ";
            cout << "}" << endl;
        }
    }

    vector<int> klargest(vector<int>& v, int n)
    {
        int p = klargestutil(v, 0, v.size() - 1, n);
        return { v.begin() + p, v.end() };
    }

    vector<int> ksmallest(vector<int>& v, int n)
    {
        int p = ksmallestutil(v, 0, v.size() - 1, n);
        return { v.begin(), v.begin() + p + 1 };
    }

private:
    int klargestutil(vector<int>& v, int l, int r, int k)
    {
        if (l > r) { return -1; }
        int p = partition(v, l, r);

        int e = r - p + 1;
        if (e == k) return p;
        if (e < k) return klargestutil(v, l, p - 1, k - e);
        else return klargestutil(v, p + 1, r, k);
    }

    int ksmallestutil(vector<int>& v, int l, int r, int k)
    {
        if (l > r) { return -1; }
        int p = partition(v, l, r);

        int e = p - l + 1;
        if (e == k) return p;
        if (e < k) return ksmallestutil(v, p + 1, r, k - e);
        else return ksmallestutil(v, l, p - 1, k);
    }

    int partition(vector<int>& v, int l, int r)
    {
        int pivot = v[r];
        int i = l;
        for (int j = l; j < r; j++) {
            if (v[j] <= pivot) {
                swap(v[i], v[j]);
                i++;
            }
        }
        swap(v[i], v[r]);

        return i;
    }
};