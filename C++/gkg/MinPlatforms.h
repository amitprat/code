#pragma once
#include "../Header.h"

class MinPlatforms {
public:
    static void test() {
        {
            vector<pair<int, int>> arr = { {900,910}, {940,1200}, {950,1120}, {1100,1130}, {1500,1900}, {1800,2000} };
            int count = minPlatforms(arr);
            cout << "Min platforms = " << count << endl;
        }
        {
            vector<pair<int, int>> arr = { {1,9},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9} };
            int count = minPlatforms(arr);
            cout << "Min platforms = " << count << endl;
        }
        {
            vector<pair<int, int>> arr = { {1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9} };
            int count = minPlatforms(arr);
            cout << "Min platforms = " << count << endl;
        }
    }

    static int minPlatforms(vector<pair<int, int>> arr) {
        sort(arr.begin(), arr.end(), [](auto& f, auto& s) {return f.first < s.first; });
        int platforms = 1;
        int i = 0, j = 1;
        int cur = 1;
        unordered_map<int, vector<pair<int, int>>> pairs;
        pairs.insert({ 0,{arr[0]} });
        while (j < arr.size()) {
            if (arr[j].first < arr[i].second) {
                pairs[cur].push_back(arr[j]);
                cur++;
                j++;
            }
            else {
                platforms = max(platforms, cur);
                cur--;
                i++;
            }
        }
        platforms = max(platforms, cur);
        cout << to_string(pairs) << endl;

        return platforms;
    }
};