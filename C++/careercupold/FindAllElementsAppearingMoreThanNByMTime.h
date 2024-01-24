/*
Design an algorithm that, given a list of n elements in an array, finds all the elements that appear more than n/3 times in the list. The algorithm should run in linear time ( n >=0 )

You are expected to use comparisons and achieve linear time. No hashing/excessive space/ and don't use standard linear time deterministic selection algo
*/

/*
I have a correct solution to it. I am gonna post a small piece of code. You need a compiler that support C++ 11 to run the code.
But don't worry if you don't have such one. I know that most of people would prefer English to code. I will explain the idea in English afterward, but, excuse me for I am not a native English speaker.
The algorithm here is actually not designed dedicatedly to solve this question but to handle a more general case:
Given an array of N numbers, finds all the elements that appear more than N/M times and report the their frequencies.
The time complexity is O(2*N*logM) and space complexity is O(M)
For this question, M = 3, so the time is O(2log3 N) = O(N), space is O(3) = O(1);


#include <iostream>
#include <map>
#include <algorithm>
typedef std::map<int, int> Map;
 Map findOverNth(int arr[], int size, int n)
{
	Map ret_map; 
	typedef Map::value_type Elem; //pair<CONST int, int>
	int total = 0;
	std::for_each(arr, arr + size, [&, n](int val) 
	{
		auto ret_pair = ret_map.insert(Elem(val, 0));
		++(*ret_pair.first).second; ++ total;
		if (ret_map.size() == n)
			for (auto iter = ret_map.begin(); iter != ret_map.end(); )
			{
				--(*iter).second; -- total;
				if ((*iter).second == 0)
					ret_map.erase(iter++);
				else
					iter++;
			}
	});
	std::for_each(ret_map.begin(), ret_map.end(), [](Elem &elem) {elem.second = 0;});
	std::for_each(arr, arr + size, [&ret_map](int val) {if (ret_map.find(val) != ret_map.end()) ret_map[val] ++;});
	for (auto iter = ret_map.begin(); iter != ret_map.end(); )
	{
		if ((*iter).second <= size / n)
			ret_map.erase(iter++);
		else 
			iter++;
	}
	return ret_map;
}
using namespace std;
int main()
{
	//int arr[] = {5,6,7,8, 10, 4,4, 4, 4,1, 1,1};
	int arr[] = {5,6,7,8, 10, 10, 10,10,10,10, 4,4, 4, 4,4,1, 1,1,1};
	auto a_map = findOverNth(arr, sizeof(arr)/sizeof(int), 4);
	cout<<sizeof(arr)/sizeof(int)<<endl;
	//cout<<a_map.size()<<endl;
	for each(auto elem in a_map)
	{
		cout<<elem.first<<" "<<elem.second<<endl;
	}
}
*/

/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<int,int> findOverNth(vector<int> arr, int m) {
    unordered_map<int,int> map;
    for(auto elem:arr) {
        map[elem]++;
        if(map.size() == m) {
            for(auto iter = map.begin();iter != map.end();) {
                --(*iter).second;
				if ((*iter).second == 0)
					map.erase(iter++);
				else
					iter++;
            }
        }
    }
    for(auto& entry : map) {
        entry.second = 0;
    }
    
    for(auto elem : arr) {
        if(map.find(elem) != map.end()) map[elem]++;
    }
    
    for(auto elem:map) {
        if(elem.second < m) map.erase(elem.first);
    }
    
    return map;
}

int main()
{
    vector<int> arr = {5,6,7,8, 10, 10, 10,10,10,10, 4,4, 4, 4,4,1, 1,1,1};
    int m = 4;
    
    cout<<"Total Size = "<<arr.size()<<endl;
    unordered_map<int,int> map;
    for(auto e : arr) map[e]++;
    for(auto e:map) if(e.second >= m) cout<<e.first<<"="<<e.second<<", ";
    cout<<endl;
    
	auto a_map = findOverNth(arr, m);
	for(auto elem : a_map)cout<<elem.first<<"="<<elem.second<<", ";
	cout<<endl;
	
	return 0;
}
