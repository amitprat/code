#pragma once
#include "../Header.h"

/*
Given an array having 16000 unique integers, each lying within the range 1<x<20000, how do u sort it. U can load only 1000 numbers at a time in memory.

use bit vector to store each integer in single bit. 625 integers are required to store 20000 numbers

int arr[625] = {0};

ex: to store data 2000
arr index = 2000/32 = 62
bit position = 2000%32 = 16

now make bit position 16 of array index 62 arr[62] to 1

using this bit vectors we can store data range from 1 - 20000 in 625 integers..

after storing all data in bit vectors, check all bit positions of arr[0], arr[1]..... arr[625]... if any bit position is set to 1 then store back that data into array

lets arr[10] bit position 15 is set to 1 then this is equivalent to data 10*32+15 = 335
*/

class SortNumbersInRange1To20000 {
	class Bitset {
		int sz = 0;
		int* arr = nullptr;
		int numSz = 0;
	public:
		Bitset(int range) {
			this->numSz = (8 * sizeof(int));
			this->sz = (range / numSz) + (range % numSz ? 1 : 0);
			arr = new int[this->sz];
			memset(arr, 0, sizeof(int) * this->sz);
		}
		void add(int number) {
			int pos = number / numSz;
			int off = number % numSz;

			set(pos, off);
		}

		void set(int pos, int off) {
			arr[pos] |= (1 << off);
		}
		bool isset(int number) {
			int pos = number / numSz;
			int off = number % numSz;

			return isset(pos, off);
		}

		bool isset(int pos, int off) {
			return arr[pos] & (1 << off);
		}
	};

public:
	static void test() {
		SortNumbersInRange1To20000 obj;
		int range = 20000;

		for (int i = 0; i < 100; i++) {
			unordered_set<int> seen;
			vector<int> input;
			srand(time(nullptr));
			for (int i = 0; i < 16000;) {
				int newNum = (rand() % range) + 1;
				if (seen.count(newNum) > 0) continue;

				seen.insert(newNum);
				input.push_back(newNum);
				i++;
			}

			vector<int> output = input;
			obj.sort(output, range);

			assert(input.size() == output.size());
			assert(obj.hasElements(input, output));
			assert(obj.isSorted(output));
		}

		vector<int> input = { 6,4,200,600,2,32,234,20 };
		print("Original Array", input);

		vector<int> output = input;
		obj.sort(output, range);
		print("Sorted Array", output);
	}

	void sort(vector<int>& arr, int range) {
		Bitset bitset(range + 1); // numbers are in range [1,20000] so array should be of size +1
		for (auto e : arr) {
			bitset.add(e);
		}
		arr.clear();

		for (int i = 1; i <= range; i++) {
			if (bitset.isset(i)) arr.push_back(i);
		}
	}

private:
	bool hasElements(vector<int>& input, vector<int>& output) {
		unordered_set<int> elements;
		for (auto e : output) elements.insert(e);
		for (auto e : input) if (elements.find(e) == elements.end()) return false;
		return true;
	}

	bool isSorted(vector<int>& output) {
		for (int i = 1; i < output.size(); i++) {
			if (output[i] < output[i - 1]) return false;
		}
		return true;
	}
};