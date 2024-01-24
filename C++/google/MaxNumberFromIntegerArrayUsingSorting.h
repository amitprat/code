#include "../Header.h"

/*
https://www.careercup.com/question?id=7781671

Given an integer array, sort the integer array such that the concatenated integer of the result array is max. 
e.g. [4, 94, 9, 14, 1] will be sorted to [9,94,4,14,1] where the result integer is 9944141
*/

/*
quick sort the input BUT
  while comparing two inputs A and B
  instead of doing the regular A > B, DO THIS
      if(ToInt('AB') > ToInt('BA')) return 1 
             else -1;
*/

void makeBigNum(vector<int> &arr)
{
    sort(arr.begin(), arr.end(), [](const auto &first, const auto &second) {
        string fs = std::to_string(first) + std::to_string(second);
        string ss = std::to_string(second) + std::to_string(first);
        return stoi(fs) <= stoi(ss);
    });
}