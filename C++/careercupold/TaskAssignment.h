#pragma once
#include "../Header.h"

/*
There are at most eight servers in a data center. Each server has got a capacity/memory limit. There can be at most 8 tasks that need to be scheduled on those servers. Each task requires certain capacity/memory to run, and each server can handle multiple tasks as long as the capacity limit is not hit. Write a program to see if all of the given tasks can be scheduled or not on the servers?

Ex:
Servers capacity limits: 8, 16, 8, 32
Tasks capacity needs: 18, 4, 8, 4, 6, 6, 8, 8
For this example, the program should say 'true'.

Ex2:
Server capacity limits: 1, 3
Task capacity needs: 4
For this example, program should return false.

Got some idea that this needs to be solved using dynamic programming concept, but could not figure out exact solution.
*/

class TaskAssignment {
public:
	static void test() {
		TaskAssignment obj;
		vector<int> servers = { 8,16,8,32 };
		vector<int> needs = { 18,4,8,4,6,6,8,8 };
		auto res = obj.assign(servers, needs);
		for (auto e : res) {
			cout << servers[e.first] << ":";
			for (auto f : e.second) {
				cout << f << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	unordered_map<int, vector<int>> assign(vector<int> servers, vector<int> needs) {
		unordered_map<int, vector<int>> result;
		auto res = assign(servers, needs, 0, result);
		if (!res) cout << "No assignment exists!!";
		return result;
	}

	bool assign(vector<int> servers, vector<int> needs, int pos, unordered_map<int, vector<int>>& result) {
		if (pos == needs.size()) return true;
		auto need = needs[pos];
		int index = 0;
		for (auto& server : servers) {
			if (need <= server)
			{
				result[index].push_back(need);
				server -= need;
				if (assign(servers, needs, pos + 1, result)) return true;
				server += need;
				result[index].pop_back();
			}
			index++;
		}
		return false;
	}
};

/*
public boolean canArrange(int[] servers, int[] tasks) {
		boolean[] used = new boolean[tasks.length];
		return canArrangeRecursive(servers, tasks, used);
	}

	public boolean canArrangeRecursive(int[] servers, int[] tasks, boolean[] used) {
		boolean allUsed = true;
		for (boolean b : used) {
			allUsed &=b;
		}
		if (allUsed){
			return true;
		}
		for (int i = 0; i < tasks.length; i++) {
			if (!used[i]) {
				used[i] = true;
				for (int j = 0; j < servers.length; j++) {
					if (servers[j] >= tasks[i]) {
						servers[j] = servers[j] - tasks[i];
						if(canArrangeRecursive(servers, tasks, used)){
							return true;
						}
						servers[j] = servers[j] + tasks[i];
					}
				}
				used[i] = false;
			}
		}
		return false;
}
*/