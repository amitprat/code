#pragma once
#include "../header.h"

class FindNumOfTimesStrRepeated {
   private:
   public:
    static void test(vector<pair<string, string>> inputs) {
        FindNumOfTimesStrRepeated obj;
        for (auto input : inputs) {
            auto res = obj.findRepeatition(input.first, input.second);
            cout << "String Repeated: {" << input.first << ", " << input.second << "} :: " << res.first << ", " << res.second << endl;
        }
    }

    pair<int, string> findRepeatition(string a, string b) {
        int repeatCount = 0;
        unordered_map<char, vector<int>> positions;
        for (int i = 0; i < b.size(); i++) {
            positions[b[i]].push_back(i);
        }

        unordered_map<char, int> amap;
        for (int i = 0; i < a.size(); i++) {
            amap[a[i]] = i;
        }

        for (auto p : positions) {
            for (auto i : p.second) {
                if (amap[p.first] != (i + amap[p.first]) % a.size()) return {-1, ""};
            }
        }

        repeatCount = ceil(double((b.size() + amap[b[0]])) / double(a.size()));
        return {repeatCount, b};
    }
};