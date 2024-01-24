#include "../header.h"

/*
https://careercup.com/question?id=5745183166562304

Given an array of n elements which contains elements from 0 to n-1, with any of these numbers appearing any number of times. Find these repeating numbers in O(n) and using only constant memory space.
Try to do it in one pass
example
[4, 2, 0, 5, 2, 0, 1] return: 0, 2
[1, 2, 3, 0, 0, 1, 3, 6, 6,6] return 0, 1, 3, 6
public List<Integer> findRepeat(int nums[]){
}
*/
class FindDuplicatesInArrayWithoutExtraSpace {
   public:
    static void test() {
        FindDuplicatesInArrayWithoutExtraSpace obj;
        vector<vector<int>> inputs =
            {
                {1, 2, 3, 6, 3, 6, 1},
                {1, 0, 3, 6, 0, 6, 1},
                {0, 1, 2, 3, 4, 5, 6},
                {6, 5, 4, 3, 2, 1, 0},
                {0, 0, 0, 0, 0, 0, 0},
                {6, 6, 6, 0, 0, 0, 1}};

        for (auto &arr : inputs) {
            obj.findDuplicatesUsingCountSort(arr);
        }
    }

   private:  // first duplicates using array index
    void findDuplicatesUsingArrayIndex(vector<int> arr) {
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0)
                arr[i] = n;
        }

        for (int i = 0; i < n;) {
            int e = arr[i];

            if (e < 0)
                i++;  // if this element is already visited, then skip
            else {
                if (arr[e % n] < 0)  // if the next element to swap is already seen, then increase its count
                {
                    arr[e % n] += -1 * arr[i];
                    arr[i++] = 0;  // set the current element not found so far
                } else {
                    swap(arr[i], arr[e % n]);
                    arr[e % n] *= -1;
                }
            }
        }

        unordered_map<int, int> freqMap;
        for (int i = 0; i < arr.size(); i++) {
            if (i == 0)
                freqMap.insert({i, abs(arr[i] / n)});
            else
                freqMap.insert({i, abs(arr[i] / i)});
        }

        cout << freqMap << endl;
    }

   private:  // count frequency using array index but simpler method
    void findDuplicatesUsingArrayOptimized(vector<int> arr) {
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            int idx = arr[i] % n;
            arr[idx] += n;
        }

        unordered_map<int, int> freqMap;
        for (int i = 0; i < n; i++) {
            if (arr[i] >= n) {
                freqMap[i] += arr[i] / n;
            }
        }

        cout << "FreqMap: " << freqMap << endl;
    }

   private:  // count frequency using array index but simpler method
    void findDuplicatesUsingArrayOptimized2(vector<int> arr) {
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            int e = abs(arr[i] % n);
            arr[e] = -1 * (abs(arr[e]) + n);
        }

        unordered_map<int, int> freqMap;
        for (int i = 0; i < n; i++) {
            if (arr[i] < 0) {
                freqMap[i] += abs(arr[i] / n);
            }
        }

        cout << "FreqMap: " << freqMap << endl;
    }

   private:
    void findDuplicatesUsingCountSort(vector<int> arr) {
        countSort(arr);

        unordered_map<int, int> freq;
        int prev = arr[0];
        int count = 1;
        for (int i = 1; i <= arr.size(); i++) {
            if (i == arr.size() || prev != arr[i]) {
                freq[prev] = count;

                prev = arr[i];
                count = 1;
            } else {
                count++;
            }
        }

        cout << "FreqMap: " << freq << endl;
    }

    void countSort(vector<int> &arr) {
        int n = arr.size();
        vector<int> count(n, 0);

        for (auto &e : arr)
            count[e]++;
        for (int i = 1; i < n; i++) {
            count[i] += count[i - 1];
        }

        vector<int> output(n);
        for (int i = n - 1; i >= 0; i--) {
            output[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
};