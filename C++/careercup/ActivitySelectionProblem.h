#include "../header.h"
/*
https://www.careercup.com/question?id=6306164115505152

We have a day to work and we have different kinds works do to which has start-time and end-time. We have to choose the different works so that we can achieve the maximum number of minutes in a day to work. Chosen works should not overlaps to each other.
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
class ActivitySelectionProblem {
    struct Job {
        int start, end, weight;
        Job(int start, int end, int weight) : start(start), end(end), weight(weight) {}
        string to_string() {
            return "{" + std::to_string(start) + "," + std::to_string(end) + "," + std::to_string(weight) + "}";
        }
    };

   public:
    static void test() {
        vector<Interval> tasks = {{5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};

        selectMaximumNumberOfNonConflictingActivities(tasks);

        {
            vector<Job> weightedJobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
            int res = selectJobsWithMaximumWeight(weightedJobs);
            cout << "Result = " << res << endl;
        }

        {
            vector<Job> weightedJobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
            int res = selectJobsWithMaximumWeightOptimizedLinearSearch(weightedJobs);
            cout << "Result = " << res << endl;
        }

        {
            vector<Job> weightedJobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
            int res = selectJobsWithMaximumWeightOptimizedBinarySearch(weightedJobs);
            cout << "Result = " << res << endl;
        }

        {
            vector<Job> weightedJobs = {{600, 830, 230}, {900, 1100, 200}, {1230, 1400, 150}, {800, 900, 100}, {1030, 1400, 350}, {900, 1130, 250}};
            int res = selectJobsWithMaximumWeightOptimizedBinarySearch(weightedJobs);
            cout << "Result = " << res << endl;
        }
    }

    static void selectMaximumNumberOfNonConflictingActivities(vector<Interval> tasks) {
        sort(tasks.begin(), tasks.end(), [](const auto& f, const auto& s) { return f.end < s.end; });

        int i = -1;
        for (int j = 0; j < tasks.size(); j++) {
            if (i == -1 || tasks[j].start >= tasks[i].end) {
                cout << tasks[j].to_string() << ", ";
                i = j;
            }
        }
        cout << endl;
    }

    static int selectJobsWithMaximumWeight(vector<Job>& weightedJobs) {
        sort(weightedJobs.begin(), weightedJobs.end(), [](const auto& f, const auto& s) { return f.end < s.end; });
        int n = weightedJobs.size();

        int* memo = new int[n + 1];
        memo[0] = 0;

        for (int i = 1; i <= n; i++) {
            memo[i] = memo[i - 1];
            for (int j = i - 1; j >= 0; j--) {
                if (j == 0 || weightedJobs[j - 1].end <= weightedJobs[i - 1].start)
                    memo[i] = max(memo[i], memo[j] + weightedJobs[i - 1].weight);
            }
        }

        return memo[n];
    }

    static int selectJobsWithMaximumWeightOptimizedLinearSearch(vector<Job>& weightedJobs) {
        if (weightedJobs.empty()) return 0;

        sort(weightedJobs.begin(), weightedJobs.end(), [](const auto& f, const auto& s) { return f.end < s.end; });
        int n = weightedJobs.size();

        int* memo = new int[n];
        memo[0] = weightedJobs[0].weight;

        for (int i = 1; i < n; i++) {
            memo[i] = memo[i - 1];
            int j = latestNonConflictingJob(weightedJobs, i);
            memo[i] = max(memo[i], memo[j] + weightedJobs[i].weight);
        }

        return memo[n - 1];
    }

    static int latestNonConflictingJob(vector<Job> jobs, int curIndex) {
        for (int j = curIndex - 1; j >= 0; j--) {
            if (jobs[j].end <= jobs[curIndex].start)
                return j;
        }
        return -1;
    }

    static int selectJobsWithMaximumWeightOptimizedBinarySearch(vector<Job>& weightedJobs) {
        if (weightedJobs.empty()) return 0;

        sort(weightedJobs.begin(), weightedJobs.end(), [](const auto& f, const auto& s) { return f.end < s.end; });
        int n = weightedJobs.size();

        int* memo = new int[n];
        memo[0] = weightedJobs[0].weight;

        for (int i = 1; i < n; i++) {
            memo[i] = memo[i - 1];
            int j = latestNonConflictingJobBinarySearch(weightedJobs, 0, i - 1, i);
            memo[i] = max(memo[i], memo[j] + weightedJobs[i].weight);
        }

        return memo[n - 1];
    }

    static int latestNonConflictingJobBinarySearch(vector<Job> jobs, int s, int e, int cur) {
        if (s > e) return -1;
        if (s == e) return jobs[s].end <= jobs[cur].start ? s : -1;

        int m = (s + e + 1) / 2;
        if (jobs[m].end <= jobs[cur].start) return latestNonConflictingJobBinarySearch(jobs, m, e, cur);
        return latestNonConflictingJobBinarySearch(jobs, s, m - 1, cur);
    }
};