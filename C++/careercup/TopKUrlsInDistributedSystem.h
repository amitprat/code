#pragma once
#include "../Header.h"


class TopKUrlsInDistributedSystem {
	struct Machine {
		string id;
		unordered_map<string, int> urls;
		vector<pair<string, int>> getLocalTopKUrlsInDistributedSystem(int k) {
			vector<pair<string, int>> result;
			for (auto url : urls) {
				result.push_back({ url.first,url.second });
			}
			sort(result.begin(), result.end(), [](auto& f, auto& s) {return f.second > s.second; });
			return { result.begin(),result.begin() + k };
		}

		vector<pair<string, int>> getHigherRankUrls(int cutoff) {
			vector<pair<string, int>> result;
			for (auto url : urls) {
				if (url.second > cutoff) result.push_back({ url.first,url.second });
			}
			sort(result.begin(), result.end(), [](auto& f, auto& s) {return f.second > s.second; });
			return result;
		}

		int get(string id) {
			return urls[id];
		}
	};
public:
	static void test() {
		TopKUrlsInDistributedSystem obj;
		vector<Machine> machines;
		machines.push_back({ "M1",{{"1",100},{"2",96},{"7",94},{"3",99},{"5",97}} });
		machines.push_back({ "M2",{{"3",99},{"5",97},{"7",4},{"1",100},{"2",96}} });
		machines.push_back({ "M3",{{"4",98},{"6",95},{"1",100},{"2",96},{"7",4}} });

		vector<pair<string, int>> res = obj.getTopKUrlsInDistributedSystem(machines, 3);
		to_string(res);
	}

	static void to_string(vector<pair<string, int>> res) {
		cout << "Top Urls: " << endl;
		for (auto url : res) {
			cout << url.first << ": " << url.second << endl;
		}
		cout << endl;
	}

	vector<pair<string, int>> getTopKUrlsInDistributedSystem(vector<Machine>& machines, int k) {
		// first pass
		vector<pair<string, int>> firstPassResult;
		for (auto machine : machines) {
			auto res = machine.getLocalTopKUrlsInDistributedSystem(k);
			firstPassResult.insert(firstPassResult.end(), res.begin(), res.end());
		}

		// merge results
		vector<pair<string, int>> intermediateResult;
		mergeResults(firstPassResult, intermediateResult, machines, k);

		// get threshold
		auto t = getThreshold(intermediateResult, k);

		// get cutoff threshold
		auto s = t / machines.size();

		// second pass
		vector<pair<string, int>> secondPassResult;
		for (auto machine : machines) {
			auto res = machine.getHigherRankUrls(s);
			secondPassResult.insert(secondPassResult.end(), res.begin(), res.end());
		}

		// merge results
		mergeResults(secondPassResult, intermediateResult, machines, k);

		return intermediateResult;
	}

private:
	void mergeResults(vector<pair<string, int>>& firstPassResult,
		vector<pair<string, int>>& intermediateResult,
		vector<Machine>& machines, int k) {
		unordered_map<string, int> res;
		for (auto partial : firstPassResult) {
			for (auto machine : machines) {
				res[partial.first] += machine.get(partial.first);
			}
		}

		for (auto r : res) intermediateResult.push_back({ r.first, r.second });
		sort(intermediateResult.begin(), intermediateResult.end(), [](auto& f, auto& s) {return f.second > s.second; });
		intermediateResult = { intermediateResult.begin(),intermediateResult.begin() + k };
	}

	int getThreshold(vector<pair<string, int>>& intermediateResult, int k) {
		return intermediateResult[k - 1].second;
	}

	vector<pair<string, int>> getTopK(vector<pair<string, int>>& intermediateResult, int k) {
		sort(intermediateResult.begin(), intermediateResult.end(), [](auto& f, auto& s) {return f.second > s.second; });
		return { intermediateResult.begin(),intermediateResult.begin() + k };
	}
};

/*
* https://www.careercup.com/question?id=4681660918398976
Given a large network of computers, each keeping log files of visited urls, find the top ten of the most visited urls.
(i.e. have many large <string (url) -> int (visits)> maps, calculate implicitly <string (url) -> int (sum of visits among all distributed maps), and get the top ten in the combined map)

The result list must be exact, and the maps are too large to transmit over the network (especially sending all of them to a central server or using MapReduce directly, is not allowed)
*/

/*
Presuming a protocol exists that can ask three questions to each server:

* the score of a single url
* the top 10
* the top n that satisfy score >= N

We program a two pass solution like so:

We denote the number of servers as S.

[First pass]
(1) Ask every server for its own top ten

(2) merge the results. For all URLs in the merged set calculate correct values by asking
all servers for their scores for each URL. Calculate a set of top ten from our sample.

(3) pick score of the now tenth URL as the threshold that we try to beat
in the second round. We denote the threshold as T.

[Second pass]
(4) Ask every server for all its top N that satisfy score >= T/S

(5) Merge these bigger samples again as in step (2)

(6) We now have the correct top ten with correct scores.
*/

/*
Am not sure if this is going to work all the time. Please correct me if i am wong

X:Y Means Urls X has a count of Y
We want top 2 uRLs

M/C A=> 1:100 2:96 7:98
M/C B=> 3:99 5:97 7:2
M/C C=> 4:98 6:95 7:2

1st Step
A=>1,2
B=>3,5
C=>4,6

2nd Step
Top two after merging
1,3 Urls are selected

3rd Step
Threshold=99(Selected from url 3)

4th Step
Score = 99/3=33
A=>1,2,7
B=>3,5
C=>4,6

5th Step
Merging will again give us 1,3 when infact Url 7 has the highest count

Mithun, you made a mistake in your example and I think you misunderstood the suggested approach.
M/C A=> 1:100 2:96 7:98 , so 1 and 7 would be the top 2.

Anyway, even if we change it to
M/C A=> 1:100 2:96 7:94
M/C B=> 3:99 5:97 7:4
M/C C=> 4:98 6:95 7:4

Where 7 is the most visited site as you intended, the merging in 5th step implies that "For all URLs in the merged set calculate correct values by asking
all servers for their scores for each URL", so we would get 102 as the count for url 7.

Oh okok.. got it.. So in the worst case if all URLs satisfy the score of > T/S, all the URLs will be sent to the server for merging right ?

The approach is correct ... the only issue being that the solution will not scale and for a large number of machines the network traffic may be gargantuan. Consider an example with top ten counts in range of 1million and the number of servers in 10k range (which is not a big number considering the scale of amazon or google scale) so eventually you will ask for all URL which have count >= T/S which is 100 in this case. So you will end up sending a lot more data than is actually needed (as you will be sending URL for counts between 100 and 1 million). Also the bottleneck in such a solution would be central node processing this algorithm which wont scale but as I said earlier the solution is correct but not scalable.

Thanks, vik, for your thoughts on scalability. I think this shows how open ended the question actually is. Without more knowledge about the topology of the machines, datacenters, loadbalancers, etc involved it is not possible to proof the quality and scalability of the algorithm in real life. A few things I would suggest to discuss about this:

- is it a typical weblog file? Typical weblogs have a steep declining start and a long flat tail, so the number of accesses on the tenth rank are usually high: if it is such a distribution, this algorithm is not bad.

- how biased are the loadbalancers? If the loadbalancers have a high degree of randomness built in, then the differences between the machines are statistically already similar enough that the first pass is quite good and the second pass is not much work.

- can clusters of machines be pre-merged? If racks or lines of racks can have a logserver that collects the full logs for the rack or line, then the number of servers to contact can be drastically reduced.

- how often are these calculations repeated? Which similar questions need to be answered? How often? How exact must the numbers be? How up-to-date? Each answer would influence the program and tuning we want to set up to produce fast and good numbers.
*/