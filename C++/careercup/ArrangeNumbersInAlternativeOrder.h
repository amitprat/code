#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5684901156225024

Arrange an array into wiggle / alternating order in a single pass:
    b[0] <= b[1] >= b[2] <= b[3] >= b[4] ...

i.e. every odd-indexed element is a local peak, every even-indexed element
is a local valley — no sorting required, O(n) time, O(1) space.

Example:
  Input:  [3, 5, 7, 8, 4, 9]
  Output: [3, 7, 5, 8, 4, 9]   ← what this algorithm actually produces
  Verify:  3 < 7 > 5 < 8 > 4 < 9  ✓

Approach 2 (sort-based) gives the canonical/sorted-looking output:
  Output: [3, 5, 4, 8, 7, 9]
  Verify:  3 < 5 > 4 < 8 > 7 < 9  ✓
*/

class AlternatingArray {
   public:
    static void test() {
        const std::vector<std::vector<int>> cases = {
            {3, 5, 7, 8, 4, 9},  // general
            {1, 2, 3, 4, 5},     // sorted ascending
            {5, 4, 3, 2, 1},     // sorted descending
            {1, 1, 1, 1},        // all equal
            {2, 1},              // two elements
            {1},                 // single element
        };

        for (const auto& input : cases) {
            auto v1 = input, v2 = input;
            arrangeSinglePass(v1);
            arrangeSorted(v2);

            std::println("input:       {}", to_string(input));
            std::println("single-pass: {}  valid: {}", to_string(v1), isValid(v1) ? "yes" : "NO");
            std::println("sort-based:  {}  valid: {}\n", to_string(v2), isValid(v2) ? "yes" : "NO");
        }
    }

    // Approach 1 — O(n) single pass, in-place.
    static void arrangeSinglePass(std::vector<int>& v) {
        const int sz = static_cast<int>(v.size());
        for (int i = 1; i < sz; ++i) {
            if ((i & 1) && v[i] < v[i - 1]) std::swap(v[i], v[i - 1]);   // odd  = peak:   swap if less than left
            if (!(i & 1) && v[i] > v[i - 1]) std::swap(v[i], v[i - 1]);  // even = valley: swap if greater than left
        }
    }

    // Cleaner version of single-pass approach: always swap if right is greater than left,
    // then condition is automatically satisfied for both peaks and valleys without needing to check the index parity
    static void arrangeSinglePass(std::vector<int>& v) {
        const int sz = static_cast<int>(v.size());
        for (int i = 1; i < sz; i += 2) {
            if (v[i] < v[i - 1]) std::swap(v[i], v[i - 1]);                // ensure peak >= left
            if (i + 1 < sz && v[i] < v[i + 1]) std::swap(v[i], v[i + 1]);  // ensure peak >= right
        }
    }

    // Approach 2 — O(n log n) sort then interleave.
    // After sorting, swapping every adjacent pair at odd indices
    // guarantees valley <= peak >= valley strictly from the sorted order.
    // Produces a more "canonical" output (smallest values in valleys).
    static void arrangeSorted(std::vector<int>& v) {
        std::ranges::sort(v);
        for (int i = 1; i + 1 < static_cast<int>(v.size()); i += 2) {
            std::swap(v[i], v[i + 1]);
        }
    }

   private:
    [[nodiscard]] static bool isValid(const std::vector<int>& v) {
        for (int i = 1; i < static_cast<int>(v.size()); i += 2) {
            if (v[i] < v[i - 1]) return false;                      // odd index should be peak: check left
            if (i + 1 < v.size() && v[i] < v[i + 1]) return false;  // odd index should be peak: check right
        }
        return true;
    }
};