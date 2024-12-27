#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=5767864852152320

There are discounts on particular time period
suppost
Day1 - Day5 => 10%
Day2 - Day 8 => 5%
Day4 - Day6 => 20 %

find the period where maximum discounts is available.

For above example the period is Day4 - Day5 => 10+5+20

that means 35%

Provide the generalize solution. Period can be time also.

1st Approach:
convert periods into pairs
{day#, discount change}
start day of period has a positive discount change value, end day negative.
sort by day.
scan pairs, updating max total discount. when max is changed that is the starting day of the max period and the end day of the period is reset.
when we have max starting day and find a drop in total discount we set that pair as the end of the period.
O(nlgn)
*/

class CalculateMaximumDiscountPeriod {
    struct Discount {
        int start, end, discount;
        Discount() {}
        Discount(int start, int end, int discount) : start(start), end(end), discount(discount) {}
    };

   public:
    static void test() {
        vector<Discount> input = {Discount(1, 5, 10), Discount(2, 8, 5), Discount(4, 6, 20)};

        auto res = getMaxDiscountPeriod(input);
    }

    static Discount getMaxDiscountPeriod(vector<Discount>& discounts) {
        int minStartDay = INT_MAX, maxStartDay = INT_MIN;
        for (auto& discount : discounts) {
            minStartDay = min(minStartDay, discount.start);
            maxStartDay = max(maxStartDay, discount.end);
        }

        vector<int> discountByDay(maxStartDay - minStartDay + 1, 0);
        for (auto& discount : discounts) {
            for (int start = discount.start - minStartDay; start <= discount.end - minStartDay; start++) {
                discountByDay[start] += discount.discount;
            }
        }

        Discount maxDiscount, maxDiscountSoFar;
        int previous = INT_MIN;
        for (int start = 0; start < discountByDay.size(); start++) {
            if (previous == -1 || discountByDay[start] > previous) {
                maxDiscount = maxDiscountSoFar;
                maxDiscountSoFar = Discount(start + minStartDay, start, discountByDay[start]);
            } else {
                maxDiscountSoFar.end = start;
            }
        }

        return maxDiscount;
    }

    static Discount getMaxDiscountPeriod2(vector<Discount>& discounts) {
        vector<pair<int, int>> events;

        for (auto& discount : discounts) {
            events.push_back({discount.start, discount.discount});
            events.push_back({discount.end, -discount.discount});
        }

        sort(events.begin(), events.end(), [](const auto& first, const auto& second) { return first.first < second.first; });

        Discount curDiscount(0, -1, 0), maxDiscount(0, -1, 0);
        for (auto& event : events) {
            if (curDiscount.discount == maxDiscount.discount) {
                maxDiscount.end = event.first;
            }

            curDiscount.discount += event.second;
            if (curDiscount.discount > maxDiscount.discount) {
                curDiscount = Discount(event.first, event.first, curDiscount.discount);
                maxDiscount = curDiscount;
            }
        }

        return maxDiscount;
    }
};