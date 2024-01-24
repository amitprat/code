#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
using namespace std;

class KClosest
{
public:
    void test()
    {
        vector<tuple<vector<int>, int, int>> v = {
            {{1,2,3,3,5,23,62}, 3, 37},
            {{3,6,6,6,6,23,24,34}, 2, 23},
            {{2,2,3,3,5,5,23,42,42,52}, 6, 28}
        };

        for (auto p : v) {
            cout << "Processing: {{";
            for (auto j : get<0>(p)) cout << j << " ";
            cout << "}, k= " << get<1>(p) << ", x = " << get<2>(p) << " : ";

            auto res = kClosest(get<0>(p), get<1>(p), get<2>(p));
            cout << "Result = {";
            for (auto j : res) cout << j << " ";
            cout << "}" << endl;
        }
    }

    vector<int> kClosest(vector<int>& v, int k, int x)
    {
        auto res = crossoverPoint(v, 0, v.size() - 1, x);
        int l = res.first;
        int r = res.second;
        vector<int> output;
        if (l == -1 || r == -1) return output;

        while (l >= 0 && r < v.size() && output.size() < k) {
            if (abs(v[l] - x) < abs(v[r] - x))output.push_back(v[l--]);
            else output.push_back(v[r++]);
        }

        while (l >= 0 && output.size() < k) {
            output.push_back(v[l--]);
        }

        while (r < v.size() && output.size() < k) {
            output.push_back(v[r++]);
        }

        return output;
    }

    pair<int, int> crossoverPoint(vector<int> v, int l, int r, int x)
    {
        if (v[l] >= x) return { l, l + 1 };
        if (v[r] <= x) return { r - 1,r };
        if (l <= r)
        {
            int m = (l + r) / 2;
            if (v[m] >= x && v[m - 1] < x) return { m - 1, m };
            if (v[m] < x) return crossoverPoint(v, m + 1, r, x);
            return crossoverPoint(v, l, m - 1, x);
        }

        return { -1, -1 };
    }
};