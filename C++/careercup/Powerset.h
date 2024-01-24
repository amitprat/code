#include "../header.h"

class Powerset {
   public:
    static void test() {
        std::vector<int> nums = {1, 2, 3};

        Powerset obj;

        auto res1 = obj.powersetUsingBitwise(nums);
        obj.print(std::cout, res1);
        cout << endl;

        auto res2 = obj.powersetUsingRecursion(nums);
        obj.print(std::cout, res2);
        cout << endl;
    }

   private:
    vector<vector<int>> powersetUsingRecursion(const vector<int>& arr) {
        vector<vector<int>> result;
        powersetUsingRecursion(arr, 0, arr.size(), {}, result);

        return result;
    }

    void powersetUsingRecursion(const vector<int>& arr, int idx, int n, vector<int> cur, vector<vector<int>>& result) {
        if (idx > n) return;
        if (idx == n) {
            result.push_back(cur);
            return;
        }

        powersetUsingRecursion(arr, idx + 1, n, cur, result);  // skip current element
        cur.push_back(arr[idx]);
        powersetUsingRecursion(arr, idx + 1, n, cur, result);  // include current element
    }

   private:
    vector<vector<int>> powersetUsingBitwise(const vector<int>& arr) {
        int n = arr.size();
        int mx = 1 << n;

        vector<vector<int>> result;
        for (int mask = 0; mask < mx; mask++) {
            vector<int> cur;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) cur.push_back(arr[i]);
            }
            result.push_back(cur);
        }

        return result;
    }

   private:
    friend std::ostream& operator<<(std::ostream& out, const vector<vector<int>>& result) {
        out << "{";
        for (auto& cur : result) {
            out << "{";
            for (auto& num : cur) out << num << ",";
            out << "}";
        }
        out << "}";

        return out;
    }

    void print(std::ostream& out, const vector<vector<int>>& result) {
        out << "{";
        for (auto& cur : result) {
            out << "{";
            for (auto& num : cur) out << num << ",";
            out << "}, ";
        }
        out << "}";
    }
};