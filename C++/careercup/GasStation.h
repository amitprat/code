#pragma once
#include "../header.h"

// https://leetcode.com/problems/gas-station/?envType=study-plan-v2&envId=top-interview-150

/*
134. Gas Station
Solved
Medium
Topics
premium lock icon
Companies
There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique.



Example 1:

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
*/

class Solution {
   public:
    /**
     * @brief Finds the starting gas station index to complete a circuit.
     * @param gas Vector of gas available at each station.
     * @param cost Vector of cost to travel to the next station.
     * @return Starting index if possible, otherwise -1.
     */
    [[nodiscard]] static int canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost) {
        const int n = static_cast<int>(gas.size());
        if (n == 0) return -1;

        int total_surplus = 0;
        int current_surplus = 0;
        int start = 0;

        for (int i = 0; i < n; ++i) {
            int surplus = gas[i] - cost[i];
            total_surplus += surplus;
            current_surplus += surplus;

            if (current_surplus < 0) {
                current_surplus = 0;
                start = i + 1;
            }
        }

        return total_surplus >= 0 ? start : -1;
    }

   public:
    /**
     * @brief Two-pointer (sliding-window) O(n) solution – the original
     *        `canCompleteCircuit2` logic, cleaned up and made safe.
     *
     * It expands a window `[s, e)` while keeping `curFuel >= 0`.  When the fuel
     * becomes negative we shrink the window from the left until the fuel is
     * non-negative again.  The loop stops as soon as a full lap is completed.
     *
     * @param gas  Gas available at each station.
     * @param cost Cost to travel from each station to the next.
     * @return Starting index if a circuit is possible, otherwise -1.
     */
    [[nodiscard]] static int canCompleteCircuit2(const std::vector<int>& gas,
                                                 const std::vector<int>& cost) {
        const int n = static_cast<int>(gas.size());
        if (n == 0) return -1;

        int s = 0, e = 0;  // window boundaries
        int curFuel = 0;
        const int maxSteps = 2 * n;  // safety bound

        for (int step = 0; step < maxSteps; ++step) {
            curFuel += gas[e] - cost[e];
            e = (e + 1) % n;

            // one full lap completed → we have a candidate
            if (e % n == s) break;

            // shrink from left while fuel is negative
            while (s != e && curFuel < 0) {
                curFuel -= gas[s] - cost[s];
                s = (s + 1) % n;
            }
        }

        return (curFuel >= 0) ? s : -1;
    }

   public:
    /**
     * @brief Test function with example cases.
     */
    static void test() {
        struct TestCase {
            std::vector<int> gas;
            std::vector<int> cost;
            int expected;
        };

        const std::vector<TestCase> tests = {
            {{1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}, 3},
            {{2, 3, 4}, {3, 4, 3}, -1},
            {{5, 1, 2, 3, 4}, {4, 4, 1, 5, 1}, 4},
            {{1}, {1}, 0},
            {{}, {}, -1}};

        std::cout << "Running canCompleteCircuit tests...\n";
        int passed = 0;

        for (size_t i = 0; i < tests.size(); ++i) {
            const auto& t = tests[i];
            int result = canCompleteCircuit(t.gas, t.cost);
            bool ok = (result == t.expected);
            passed += ok;

            std::cout << "Test " << i + 1 << ": ";
            if (ok) {
                std::cout << "PASSED\n";
            } else {
                std::cout << "FAILED (got " << result << ", expected " << t.expected << ")\n";
            }
        }

        std::cout << passed << "/" << tests.size() << " tests passed.\n\n";
    }
};