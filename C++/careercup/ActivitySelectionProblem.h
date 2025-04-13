#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=6306164115505152

We have a day to work and we have different kinds works do to which has start-time and end-time. We have to choose the different works so that
we can achieve the maximum number of minutes in a day to work. Chosen works should not overlaps to each other.
Ex-1:
Start-Time End-Time
W1: 6:00 9:30
W2: 9:00 12:30
W3: 12:00 14:30
W4: 10:00 10:30
W5: 11:00 13:30
Solution: W1 + W4 + W3(or W5)
Ex-2:
Start-Time End-Time
W1: 6:00 8:30
W2: 9:00 11:00
W3: 12:30 14:00
W4: 8:00 9:00
W5: 10:30 14:00
W6: 9:00 11:30
Solution : W1 + W6 + W3 = 390min
*/

/*
Other question:
You are given n activities with their start and finish times. Select the maximum number of activities that can be
performed by a single person, assuming that a person can only work on a single activity at a time.
Example:

Consider the following 6 activities.
     start[]  =  {1, 3, 0, 5, 8, 5};
     finish[] =  {2, 4, 6, 7, 9, 9};
The maximum set of activities that can be executed
by a single person is {0, 1, 3, 4}
The greedy choice is to always pick the next activity whose finish time is least among the remaining activities and
the start time is more than or equal to the finish time of previously selected activity. We can sort the activities
according to their finishing time so that we always consider the next activity as minimum finishing time activity.

1) Sort the activities according to their finishing time
2) Select the first activity from the sorted array and print it.
3) Do following for remaining activities in the sorted array.
…….a) If the start time of this activity is greater than the finish time of previously selected activity then select
this activity and print it.
*/

class ActivitySelectionProblem {
    struct Job {
        int start{}, end{}, weight{};

        Job(int s, int e, int w) : start(s), end(e), weight(w) {}

        [[nodiscard]] std::string to_string() const {
            return std::format("{{{},{},{}}}", start, end, weight);
        }

        friend std::ostream& operator<<(std::ostream& os, const Job& job) {
            return os << job.to_string();
        }
    };

   public:
    static void test() {
        using namespace std;

        cout << "\nSelect non-conflicting activities:\n";
        vector<Interval> tasks = {{5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};
        cout << "Input: " << tasks << endl;
        selectMaximumNumberOfNonConflictingActivities(tasks);

        cout << "\nSelect non-conflicting activities with maximum weight:\n";
        vector<Job> weightedJobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
        cout << "Input: " << weightedJobs << endl;

        cout << "Result with memoization = " << selectJobsWithMaximumWeight(weightedJobs) << '\n';
        cout << "Result with optimized linear search = " << selectJobsWithMaximumWeightOptimizedLinearSearch(weightedJobs) << '\n';
        cout << "Result with optimized binary search = " << selectJobsWithMaximumWeightOptimizedBinarySearch(weightedJobs) << '\n';

        cout << "\nSelect non-conflicting activities with maximum weight:\n";
        vector<Job> weightedJobs2 = {{600, 830, 230}, {900, 1100, 200}, {1230, 1400, 150}, {800, 900, 100}, {1030, 1400, 350}, {900, 1130, 250}};
        cout << "Input: " << weightedJobs2 << endl;
        cout << "Result with memoization = " << selectJobsWithMaximumWeight(weightedJobs2) << '\n';
        cout << "Result with optimized linear search = " << selectJobsWithMaximumWeightOptimizedLinearSearch(weightedJobs2) << '\n';
        cout << "Result with optimized binary search = " << selectJobsWithMaximumWeightOptimizedBinarySearch(weightedJobs2) << '\n';
    }

    static void selectMaximumNumberOfNonConflictingActivities(const std::vector<Interval>& tasks) {
        auto sortedTasks = tasks;
        std::ranges::sort(sortedTasks, {}, &Interval::end);

        int lastSelected = -1;
        for (size_t i = 0; i < sortedTasks.size(); ++i) {
            if (lastSelected == -1 || sortedTasks[i].start >= sortedTasks[lastSelected].end) {
                std::cout << sortedTasks[i] << ", ";
                lastSelected = static_cast<int>(i);
            }
        }
        std::cout << '\n';
    }

    static int selectMaximumTasks(const std::vector<Interval>& tasks) {
        if (tasks.empty()) return 0;

        auto sortedTasks = tasks;
        std::ranges::sort(sortedTasks, {}, &Interval::end);

        std::vector<Interval> selectedTasks{sortedTasks.front()};
        int lastEnd = sortedTasks.front().end;

        for (const auto& task : sortedTasks | std::views::drop(1)) {
            if (task.start >= lastEnd) {
                selectedTasks.push_back(task);
                lastEnd = task.end;
            }
        }

        for (const auto& task : selectedTasks) {
            std::cout << task << ", ";
        }
        std::cout << '\n';

        return static_cast<int>(selectedTasks.size());
    }

   private:
    [[nodiscard]] static int selectJobsWithMaximumWeight(std::vector<Job>& weightedJobs) {
        if (weightedJobs.empty()) return 0;

        std::ranges::sort(weightedJobs, {}, &Job::end);
        const int n = static_cast<int>(weightedJobs.size());

        std::vector<int> memo(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            memo[i] = memo[i - 1];
            for (int j = i - 1; j >= 0; --j) {
                if (j == 0 || weightedJobs[j - 1].end <= weightedJobs[i - 1].start) {
                    memo[i] = std::max(memo[i], memo[j] + weightedJobs[i - 1].weight);
                    break;
                }
            }
        }
        return memo[n];
    }

    [[nodiscard]] static int selectJobsWithMaximumWeightOptimizedLinearSearch(std::vector<Job>& weightedJobs) {
        if (weightedJobs.empty()) return 0;

        std::ranges::sort(weightedJobs, {}, &Job::end);
        const int n = static_cast<int>(weightedJobs.size());

        std::vector<int> memo(n, 0);
        memo[0] = weightedJobs[0].weight;

        for (int i = 1; i < n; ++i) {
            int incl = weightedJobs[i].weight;
            int latest = latestNonConflictingJob(weightedJobs, i);
            if (latest != -1) incl += memo[latest];
            memo[i] = std::max(memo[i - 1], incl);
        }

        return memo.back();
    }

    [[nodiscard]] static int selectJobsWithMaximumWeightOptimizedBinarySearch(std::vector<Job>& weightedJobs) {
        if (weightedJobs.empty()) return 0;

        std::ranges::sort(weightedJobs, {}, &Job::end);
        const int n = static_cast<int>(weightedJobs.size());

        std::vector<int> memo(n, 0);
        memo[0] = weightedJobs[0].weight;

        for (int i = 1; i < n; ++i) {
            int incl = weightedJobs[i].weight;
            int latest = latestNonConflictingJobBinarySearch(weightedJobs, i);
            if (latest != -1) incl += memo[latest];
            memo[i] = std::max(memo[i - 1], incl);
        }

        return memo.back();
    }

    [[nodiscard]] static int latestNonConflictingJob(const std::vector<Job>& jobs, int index) {
        for (int j = index - 1; j >= 0; --j) {
            if (jobs[j].end <= jobs[index].start)
                return j;
        }
        return -1;
    }

    [[nodiscard]] static int latestNonConflictingJobBinarySearch(const std::vector<Job>& jobs, int index) {
        int low = 0, high = index - 1, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (jobs[mid].end <= jobs[index].start) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};
