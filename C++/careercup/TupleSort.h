#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5078393905217536


There is an array of 3-tuple, in the form of (a, 1, 5). The first element in the tuple is the id, the second and third elements
are both integers, and the third is always larger than or equal to the second. Assume that the array is sorted based on the second
element of the tuple. Write a function that breaks each of the 3-tuple into two 2-tuples like (a, 1) and (a, 5), and sort them
according to the integer.

E.g. given (a, 1, 5), (b, 2, 4), (c, 7, 8), output (a, 1), (b, 2), (b, 4), (a, 5), (c, 7), (c, 8).


The O(nlogn) Solution is pretty straight forward. The interesting part is: whether can we find O(n) solution. The answer is NO.
I can prove this by contradiction.
Assume such algorithm exists. Then for any N integers x1,x2,....xn. I construct the N three tuples (a, -infinity, x1),
(b, -infinity, x2)...... clearly -infinity < xk, so it satisfies the condition. Now, with the algorithm, we can get
(a,-infinity), (b, -infinity) .......(a, x1), (b, x3)..... This means we can sort any N integers in O(N) time, which
is impossible based on normal comparison. Of course, if you do it by using bucket sort, you can do it but it needs
more assumptions about the numbers.
*/
class TupleSort {
   public:
    static void test() {
        std::vector<std::tuple<char, int, int>> tuples = {
            {'a', 1, 5},
            {'b', 2, 4},
            {'c', 7, 8},
            {'d', 3, 9},
            {'e', 10, 11}};

        auto sorted = generateSortedPairs2(tuples);
        std::cout << "Test Case 1 (basic): " << to_string(sorted) << std::endl;

        std::vector<std::tuple<char, int, int>> edgeCase1 = {
            {'x', 5, 5},  // start == end
            {'y', 2, 2},
            {'z', 1, 1}};
        std::cout << "Test Case 2 (start == end): " << to_string(generateSortedPairs2(edgeCase1)) << std::endl;

        std::vector<std::tuple<char, int, int>> edgeCase2 = {
            {'m', 10, 100},
            {'n', 20, 30},
            {'o', 1, 1000}};
        std::cout << "Test Case 3 (wide ranges): " << to_string(generateSortedPairs2(edgeCase2)) << std::endl;

        std::vector<std::tuple<char, int, int>> edgeCase3 = {
            {'a', 3, 6},
            {'b', 3, 5},
            {'c', 3, 4},
            {'d', 3, 3}};
        std::cout << "Test Case 4 (same start): " << to_string(generateSortedPairs2(edgeCase3)) << std::endl;
    }

   public:
    /*
                •	starts are sorted by assumption.
                •	ends, being ≥ corresponding start, are not guaranteed to be globally sorted, but due to start_i ≤ start_{i+1}
                                and end_i ≥ start_i, it is guaranteed that end_i ≥ start_i but not that end_i ≤ end_{i+1}.

                                {('a', 1, 100), ('b', 2, 3)}

                                Split:
                                                •	starts = [(a,1), (b,2)] → sorted
                                                •	ends   = [(a,100), (b,3)] → NOT sorted

                                Merged output (if naively assumed both are sorted):
                                                •	(a,1), (b,2), (a,100), (b,3) → ❌ Wrong order
                                Correct output:
                                                •	(a,1), (b,2), (b,3), (a,100)

                Following algorithm doesn't handle this case, and hence incorrect.

                •	starts is sorted ✔
                •	ends is not necessarily sorted ❌
                •	Therefore, we cannot assume both subarrays are sorted
                •	So, merge-based O(n) only works if ends is sorted, which is not guaranteed
                •	Hence, the original merge-style O(n) logic is incorrect in general
    */
    static vector<pair<char, int>> generateSortedPairs1(vector<tuple<char, int, int>> values) {
        vector<pair<char, int>> result;
        vector<pair<char, int>> tmp1;
        vector<pair<char, int>> tmp2;

        for (auto e : values) {
            tmp1.push_back({get<0>(e), get<1>(e)});
            tmp2.push_back({get<0>(e), get<2>(e)});
        }

        int i = 0, j = 0;
        while (i < tmp1.size() || j < tmp2.size()) {
            if (i == tmp1.size())
                result.push_back(tmp2[j++]);
            else if (j == tmp2.size())
                result.push_back(tmp1[i++]);
            else if (tmp1[i].second <= tmp2[j].second)
                result.push_back(tmp1[i++]);
            else
                result.push_back(tmp2[j++]);
        }

        return result;
    }

   public:
    static std::vector<std::pair<char, int>> generateSortedPairs2(const std::vector<std::tuple<char, int, int>>& input) {
        std::vector<std::pair<char, int>> result;
        result.reserve(input.size() * 2);

        for (const auto& [id, start, end] : input) {
            result.emplace_back(id, start);
            result.emplace_back(id, end);
        }

        std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        return result;
    }
};