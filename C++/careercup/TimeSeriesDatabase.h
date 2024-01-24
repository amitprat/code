#include "../header.h"

class TimeSeriesDatabase
{
public:
    static void test()
    {
        map<int, unordered_map<string, int>> productsTimeData;

        productsTimeData[0] = {
            {"x", 10},
            {"y", 5},
            {"z", 1}};

        productsTimeData[1] = {
            {"x", 1},
            {"a", 5},
            {"b", 1}};

        productsTimeData[2] = {
            {"y", 5},
            {"z", 1},
            {"a", 10}};

        /*
        x:4
        y:15
        z:12
        a:26
        b:6
        c:1
        */
        productsTimeData[3] = {
            {"x", 3},
            {"y", 5},
            {"z", 10}};

        productsTimeData[4] = {
            {"a", 10},
            {"y", 5},
            {"c", 1}};

        productsTimeData[5] = {
            {"a", 1},
            {"b", 5},
            {"z", 1}};

        TimeSeriesDatabase obj;
        {
            auto res = obj.getTopRankingProducts(productsTimeData, 3, 5);

            cout << format("Result: [{},{}]: ", 3, 5) << res << endl;
        }

        {
            auto res = obj.getTopRankingProducts(productsTimeData, 1, 5);

            cout << format("Result: [{},{}]: ", 1, 5) << res << endl;
        }
    }

    unordered_map<string, int> getTopRankingProducts(map<int, unordered_map<string, int>> products, int s, int e)
    {
        unordered_map<string, int> result;

        auto start = products.lower_bound(s);
        auto end = products.upper_bound(e);
        while (start != end)
        {
            for (auto &e : start->second)
            {
                result[e.first] += e.second;
            }

            start++;
        }

        return result;
    }
};