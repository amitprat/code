#pragma once
#include "../Header.h"

class WeightedJobScheduling {
	struct Job {
		int start, end, wt;

		bool operator()(const Job& other) {
			return end < other.end;
		}

		bool operator<(const Job& other) {
			return end < other.end;
		}

		string to_string() {
			stringstream ss;
			ss << "{";
			ss << start << ",";
			ss << end << ",";
			ss << wt;
			ss << "}";
			return ss.str();
		}
	};
public:
	static void test() {
		vector<Job> jobs = { {3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200} };

		int res1 = scheduleJobsRec(jobs);
		int res2 = scheduleJobsDP(jobs);

		assert(res1 == res2);

		cout << res1 << endl;
	}

	static int scheduleJobsDP(vector<Job> jobs) {
		sort(jobs.begin(), jobs.end());

		int n = jobs.size();
		vector<int> table(n, 0);
		table[0] = jobs[0].wt;

		for (int i = 1; i < n; i++) {
			int j = lastNonConflictingIndex(jobs, i, jobs[i].start);
			table[i] = table[i - 1];
			if (j != -1) {
				if (table[j] + jobs[i].wt > table[i]) {
					table[i] = table[j] + jobs[i].wt;
				}
			}
		}

		return table[n - 1];
	}

	static int lastNonConflictingIndex(vector<Job>& jobs, int i, int start) {
		for (int j = i - 1; j >= 0; j--) {
			if (jobs[j].end <= start) return j;
		}
		return -1;
	}

	static int scheduleJobsRec(vector<Job> jobs) {
		sort(jobs.begin(), jobs.end());

		int res1 = scheduleJobsRec1(jobs, 0, 0, jobs.size());
		int res2 = scheduleJobsRec2(jobs, 0, jobs.size());

		assert(res1 == res2);

		return res1;
	}

	static int scheduleJobsRec1(vector<Job>& jobs, int idx, int last, int n) {
		if (idx == n) return 0;

		int excl = scheduleJobsRec1(jobs, idx + 1, last, n);
		int incl = 0;
		if (idx == 0 || jobs[idx].start >= last) {
			incl = jobs[idx].wt + scheduleJobsRec1(jobs, idx + 1, jobs[idx].end, n);;
		}

		return max(incl, excl);
	}

	static int nextConflictingIndex(vector<Job>& jobs, int l, int n, int end) {
		for (int i = l; i < n; i++) {
			if (jobs[i].start >= end) return i;
		}
		return -1;
	}

	static int scheduleJobsRec2(vector<Job>& jobs, int idx, int n) {
		if (idx == n) return 0;

		int excl = scheduleJobsRec2(jobs, idx + 1, n);
		int incl = jobs[idx].wt;
		int next = nextConflictingIndex(jobs, idx + 1, n, jobs[idx].end);
		if (next != -1) {
			incl += scheduleJobsRec2(jobs, next, n);;
		}

		return max(incl, excl);
	}
};