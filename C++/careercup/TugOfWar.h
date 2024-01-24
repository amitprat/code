#include "../header.h"

class TugOfWar {
   public:
    static void test() {
        TugOfWar obj;
        vector<int> arr = {23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4};
        obj.tugOfWar(arr);
    }

   private:
    void tugOfWar(vector<int>& arr) {
        int n = arr.size();
        int sum = accumulate(arr.begin(), arr.end(), 0);

        vector<int> first, second;
        int mnDiff = INT_MAX;
        tugOfWar(arr, sum, 0, n, n / 2, mnDiff, {}, {}, first, second);

        cout << "Sum: " << sum << endl;
        cout << "First array:" << first << endl;
        cout << "Second array:" << second << endl;
        cout << "Min difference:" << accumulate(first.begin(), first.end(), 0) - accumulate(second.begin(), second.end(), 0) << endl;
    }

    void tugOfWar(vector<int>& arr, int sum, int cur, int n, int cnt, int& mnDiff, vector<int> first, vector<int> second, vector<int>& outFirst, vector<int>& outSecond) {
        if (n < 0) return;
        if (cnt == 0 && (mnDiff > abs(sum / 2 - cur))) {
            mnDiff = abs(sum / 2 - cur);
            outFirst = first;
            outSecond = second;
            return;
        }

        second.push_back(arr[n - 1]);
        tugOfWar(arr, sum, cur, n - 1, cnt, mnDiff, first, second, outFirst, outSecond);
        second.pop_back();

        first.push_back(arr[n - 1]);
        tugOfWar(arr, sum, cur + arr[n - 1], n - 1, cnt - 1, mnDiff, first, second, outFirst, outSecond);
        first.pop_back();
    }
};