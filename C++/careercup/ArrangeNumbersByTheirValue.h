#pragma once
#include "../header.h"

// Returns the callable's result paired with how long it took.
// Works with any return type including void.
template <std::invocable Fn>
[[nodiscard]] auto timed(Fn&& fn) {
    const auto t0 = std::chrono::high_resolution_clock::now();
    auto result = std::invoke(std::forward<Fn>(fn));
    const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t0);
    return std::pair{std::move(result), elapsed};
}

// Langford pairing: arrange 1..n so each k appears twice
// with exactly k numbers between the two occurrences.
// e.g. n=3 → [2, 3, 1, 2, 1, 3]
// Solutions only exist when n ≡ 0 or 3 (mod 4).
class ArrangeNumbersByTheirValue {
    using TimedResult = std::pair<bool, std::chrono::microseconds>;

   public:
    static void test() {
        ArrangeNumbersByTheirValue obj;

        for (int i = 1; i <= 10; i++) {
            std::vector<int> r1, r2;

            auto [a, t1] = obj.canBePlaced(i, r1);
            auto [b, t2] = obj.canBePlacedAlt(i, r2);

            std::println("{:2} : {}  [{:>8}]  |  alt: {}  [{:>8}]",
                         i,
                         a ? to_string(r1) : "no solution", t1,
                         b ? to_string(r2) : "no solution", t2);
        }
    }

    // --- Approach 1: place one number at a time (no auxiliary set) ---
    [[nodiscard]] TimedResult canBePlaced(int n, std::vector<int>& result) {
        result.assign(n * 2, 0);
        return timed([&] { return solve(1, n, result); });
    }

    // --- Approach 2: walk position by position, try every unplaced number ---
    [[nodiscard]] TimedResult canBePlacedAlt(int n, std::vector<int>& result) {
        result.assign(n * 2, 0);
        std::unordered_set<int> placed;
        return timed([&] { return solveByPosition(1, n, 0, result, placed); });
    }

   private:
    // Approach 1 — places num, then num+1, … until all are placed.
    [[nodiscard]] bool solve(int num, int end, std::vector<int>& result) {
        if (num > end) return true;

        const int sz = static_cast<int>(result.size());
        for (int i = 0; i + num + 1 < sz; ++i) {
            if (result[i] != 0 || result[i + num + 1] != 0) continue;

            result[i] = result[i + num + 1] = num;
            if (solve(num + 1, end, result)) return true;
            result[i] = result[i + num + 1] = 0;
        }
        return false;
    }

    // Approach 2 — scans pos left-to-right; at each empty slot tries every unplaced number.
    [[nodiscard]] bool solveByPosition(
        int startNum, int endNum, int pos,
        std::vector<int>& result,
        std::unordered_set<int>& placed) {
        if (static_cast<int>(placed.size()) == endNum) return true;

        const int sz = static_cast<int>(result.size());
        if (pos >= sz) return false;

        if (result[pos] != 0) return solveByPosition(startNum, endNum, pos + 1, result, placed);

        for (int i = startNum; i <= endNum; ++i) {
            if (placed.contains(i)) continue;
            if (pos + i + 1 >= sz) continue;
            if (result[pos + i + 1] != 0) continue;

            result[pos] = result[pos + i + 1] = i;
            placed.insert(i);

            if (solveByPosition(startNum, endNum, pos + 1, result, placed)) return true;

            result[pos] = result[pos + i + 1] = 0;
            placed.erase(i);
        }

        return false;
    }
};