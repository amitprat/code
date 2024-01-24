#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class PowerSet
{
public:
    static void test()
    {
        PowerSet obj;
        vector<string> res = obj.getPowerSet(4);
        for (auto s : res) cout << s << " ";
        cout << endl;
    }

    vector<string> getPowerSet(int len)
    {
        vector<string> res;
        //recurse(len, string(), res);
        binaryPowerSet(len, res);

        return res;
    }

    void binaryPowerSet(int len, vector<string>& res)
    {
        int p = pow(2, len);
        for (int i = 0; i < p; i++) {
            string cur;
            for (int j = 0; j < len; j++) {
                if (i & (1 << j)) cur += "1";
                else cur += "0";
            }
            res.push_back(cur);
        }
    }

    void recurse(int n, string cur, vector<string>& res)
    {
        if (n == 0) {
            res.push_back(cur); return;
        }
        recurse(n - 1, cur + "0", res);
        recurse(n - 1, cur + "1", res);
    }
};