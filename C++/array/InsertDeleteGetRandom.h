#pragma once
#include "../header.h"

#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <expected>
#include <iostream>
#include <random>
#include <span>
#include <unordered_map>
#include <vector>

/**
 * @brief Problem: Design a data structure that supports insert, remove, and getRandom in O(1) average time.
 * https://leetcode.com/problems/insert-delete-getrandom-o1/?envType=study-plan-v2&envId=top-interview-150
 */

class RandomizedSet {
   private:
    std::vector<int> data_;
    std::unordered_map<int, std::size_t> index_map_;

    inline thread_local static std::mt19937_64 rng_ = std::mt19937_64{std::random_device{}()};

   public:
    RandomizedSet() {
        // Seed with non-deterministic random device
        std::random_device rd;
        rng_.seed(rd());
    }

    [[nodiscard]] bool insert(int val) noexcept {
        if (index_map_.contains(val)) {
            return false;
        }

        data_.push_back(val);
        index_map_[val] = data_.size() - 1;
        return true;
    }

    [[nodiscard]] bool remove(int val) noexcept {
        auto it = index_map_.find(val);
        if (it == index_map_.end()) {
            return false;
        }

        const std::size_t pos = it->second;
        const int last_val = data_.back();

        // Move last element to removed position
        data_[pos] = last_val;
        index_map_[last_val] = pos;

        data_.pop_back();
        index_map_.erase(it);

        return true;
    }

    [[nodiscard]] int getRandom() {
        if (data_.empty()) {
            throw std::out_of_range("RandomizedSet is empty");
        }

        std::uniform_int_distribution<std::size_t> dist(0, data_.size() - 1);
        return data_[dist(rng_)];
    }

    [[nodiscard]] std::size_t size() const noexcept { return data_.size(); }
    [[nodiscard]] bool empty() const noexcept { return data_.empty(); }

    // Debug helper
    [[nodiscard]] std::span<const int> view() const noexcept {
        return std::span<const int>(data_);
    }

    // Static test suite
    static void test() {
        std::cout << "=== RandomizedSet Test Suite ===\n";

        RandomizedSet set;

        // Test 1: Insert unique values
        assert(set.insert(1) == true);
        assert(set.insert(2) == true);
        assert(set.insert(3) == true);
        assert(set.insert(1) == false);  // duplicate
        assert(set.size() == 3);

        std::cout << "Test 1 (Insert): PASSED\n";

        // Test 2: Remove existing and non-existing
        assert(set.remove(2) == true);
        assert(set.remove(2) == false);
        assert(set.remove(5) == false);
        assert(set.size() == 2);
        assert(std::ranges::find(set.view(), 2) == set.view().end());

        std::cout << "Test 2 (Remove): PASSED\n";

        // Test 3: getRandom uniformity (statistical test)
        constexpr int trials = 10'000;
        std::array<int, 10> counts{};  // Only track 1 and 3 now

        set.insert(2);  // Restore {1, 2, 3}
        assert(set.size() == 3);

        for (int i = 0; i < trials; ++i) {
            int val = set.getRandom();
            assert(val == 1 || val == 2 || val == 3);
            if (val >= 1 && val <= 3) {
                ++counts[val];
            }
        }

        // Check each value appears roughly 1/3 of the time (±5%)
        const double expected = trials / 3.0;
        const double tolerance = expected * 0.05;

        for (int v = 1; v <= 3; ++v) {
            assert(std::abs(counts[v] - expected) <= tolerance);
        }

        std::cout << "Test 3 (Random Uniformity): PASSED\n";

        // Test 4: Empty set handling
        set.remove(1);
        set.remove(2);
        set.remove(3);
        assert(set.empty());

        bool threw = false;
        try {
            set.getRandom();
        } catch (const std::out_of_range&) {
            threw = true;
        }
        assert(threw);

        std::cout << "Test 4 (Empty Set): PASSED\n";

        std::cout << "All tests passed!\n\n";
    }
};
