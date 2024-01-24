#include "../header.h"

// majority element
// https://www.careercup.com/question?id=14099679

/*
Design an algorithm that, given a list of n elements in an array, finds all the elements that appear more than n/3 times
in the list. The algorithm should run in linear time ( n >=0 )

You are expected to use comparisons and achieve linear time. No hashing/excessive space/ and don't use standard linear
 time deterministic selection algo

I have a correct solution to it. I am gonna post a small piece of code. You need a compiler that support C++ 11 to run the code.
But don't worry if you don't have such one. I know that most of people would prefer English to code. I will explain the idea in English afterward, but, excuse me for I am not a native English speaker.
The algorithm here is actually not designed dedicatedly to solve this question but to handle a more general case:
Given an array of N numbers, finds all the elements that appear more than N/M times and report the their frequencies.
The time complexity is O(2*N*logM) and space complexity is O(M)
For this question, M = 3, so the time is O(2log3 N) = O(N), space is O(3) = O(1);
*/
class MajorityElement {
   public:
    static void test() {
        MajorityElement obj;
        vector<vector<int>> inputs = {
            {1, 2, 4, 2, 1, 3, 2, 2, 1, 2, 1, 2, 1},
            {5, 6, 7, 8, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 1, 1, 1, 1}};

        for (auto &input : inputs) {
            cout << "Input: " << input << endl;
            auto res1 = obj.majorityElementHalf(input);
            cout << format("Majority element on half: {}:{}", res1.first, res1.second) << endl;

            auto res2 = obj.majorityElementOneThird(input);
            cout << format("Majority element on one third: {}:{}", res2.first, res2.second) << endl;

            int n = 4;
            auto res3 = obj.findOverNth(input, input.size(), n);
            cout << "Majority element over " << n << " is " << res3 << endl;
        }
    }

   private:
    // majority voting algorithm
    pair<int, int> majorityElementHalf(vector<int> &input) {
        int candidate = -1;
        int count = 0;
        for (int i = 0; i < input.size(); i++) {
            if (count == 0) candidate = input[i];

            if (input[i] == candidate)
                count++;
            else
                count--;
        }

        // validate candidate
        count = 0;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == candidate)
                count++;
        }

        if (count > input.size() / 2)
            return {candidate, count};
        return {-1, -1};
    }

   private:
    pair<int, int> majorityElementOneThird(vector<int> &input) {
        pair<int, int> candidate1 = {-1, 0};
        pair<int, int> candidate2 = {-1, 0};
        for (int i = 0; i < input.size(); i++) {
            if (candidate1.second == 0)
                candidate1 = {input[i], 0};
            else if (candidate2.second == 0)
                candidate2 = {input[i], 0};

            if (input[i] == candidate1.first)  // if first element matches
                candidate1.second++;
            else if (input[i] == candidate2.first)  // if second element matches
                candidate2.second++;
            else {  // both of them match > half so if candidate exists, its count > 0
                candidate1.second--;
                candidate2.second--;
            }
        }

        if (candidate1.second <= 0 && candidate2.second <= 0)
            return {-1, -1};

        // validate candidate
        int count1 = 0, count2 = 0;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == candidate1.first)
                count1++;
            if (input[i] == candidate2.first)
                count2++;
        }

        pair<int, int> result = {-1, -1};
        if (count1 > input.size() / 3)
            result.first = candidate1.first;
        if (count2 > input.size() / 3)
            result.second = candidate2.first;

        return result;
    }

   private:
    vector<int> majorityElementOneThird2(vector<int> &nums) {
        int cnt1 = 0, cnt2 = 0;
        int a, b;
        for (int n : nums) {
            if (cnt1 == 0 || n == a) {
                cnt1++;
                a = n;
            } else if (cnt2 == 0 || n == b) {
                cnt2++;
                b = n;
            } else {
                cnt1--;
                cnt2--;
            }
        }

        // validate
        cnt1 = cnt2 = 0;
        for (int n : nums) {
            if (n == a)
                cnt1++;
            else if (n == b)
                cnt2++;
        }

        vector<int> result;
        if (cnt1 > nums.size() / 3) result.push_back(a);
        if (cnt2 > nums.size() / 3) result.push_back(b);
        return result;
    }

   private:
    using Map = std::map<int, int>;
    Map findOverNth(vector<int> arr, int size, int n) {
        Map ret_map;

        std::for_each(arr.begin(), arr.end(), [&, n](int val) {
            ret_map[val]++;

            if (ret_map.size() == n) {
                for (auto iter = ret_map.begin(); iter != ret_map.end();) {
                    --(*iter).second;
                    --total;
                    if ((*iter).second == 0)
                        ret_map.erase(iter++);
                    else
                        iter++;
                }
            }
        });

        // validate and prepare result
        std::for_each(ret_map.begin(), ret_map.end(), [](auto &elem) { elem.second = 0; });
        std::for_each(arr.begin(), arr.end(), [&ret_map](int val) {if (ret_map.find(val) != ret_map.end()) ret_map[val] ++; });
        for (auto iter = ret_map.begin(); iter != ret_map.end();) {
            if ((*iter).second <= size / n)
                ret_map.erase(iter++);
            else
                iter++;
        }
        return ret_map;
    }
};
