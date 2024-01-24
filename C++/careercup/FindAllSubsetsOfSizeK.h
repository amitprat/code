#include "../header.h"

/*
https://careercup.com/question?id=16760663

Given an array, find all unique three-member subsets, with unique being that [0,2,3] and [3,2,0] are the same set. Should run in faster than 2^n time

void solve(char[]in){
  Arrays.sort(in);
  int N = in.length;
  for(int i=0;i<N-2;i++){
     if (i>;0 && in[i]==in[i-1]) continue;
     for(int j=i+1;j<N-1;j++){
        if (j>i+1 && in[j]==in[j-1]) continue;
        for(int k=j+1;k<N;k++){
           if (k>j+1 && in[k]==in[k-1]) continue;
           System.out.println(in[i]+","+in[j]+","+in[k]);
        }
    }
  }
}
*/
class FindAllSubsetsOfSizeK {
   public:
    static void test() {
        FindAllSubsetsOfSizeK obj;
        int k = 3;
        vector<int> arr = {1, 2, 3, 2, 3, 4};

        auto res1 = obj.allSubsetsOfSizeK1(arr, k);
        print(res1);

        // auto res2 = obj.allSubsetsOfSizeK2(arr, k);
        // print(res2);

        auto res3 = obj.findAllUniqueSubsetOfSize3(arr);
        print(res3);
    }

   private:
    // O(2^N) or O(nCr)
    vector<vector<int>> allSubsetsOfSizeK1(vector<int> arr, int k) {
        vector<vector<int>> result;
        sort(arr.begin(), arr.end());
        allSubsetsOfSizeK1(arr, arr.size(), {}, k, result);

        return result;
    }

    void allSubsetsOfSizeK1(vector<int>& arr, int n, vector<int> cur, int k, vector<vector<int>>& result) {
        if (k == 0) {
            result.push_back(cur);
            return;
        }
        if (n <= 0) return;

        allSubsetsOfSizeK1(arr, n - 1, cur, k, result);

        if (n < arr.size() - 1 && arr[n - 2] != arr[n - 1]) {
            cur.push_back(arr[n - 1]);
            allSubsetsOfSizeK1(arr, n - 1, cur, k - 1, result);
        }
    }

    //
    vector<vector<int>> allSubsetsOfSizeK2(vector<int>& arr, int k) {
        vector<vector<int>> result;

        int n = arr.size();
        int allSets = 1 << n;
        for (int i = 0; i < allSets; i++) {
            if (i < k) continue;

            vector<int> cur;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) cur.push_back(arr[j]);
                if (cur.size() > k) break;
            }
            if (cur.size() == k) result.push_back(cur);
        }

        return result;
    }

   private:
    vector<vector<int>> findAllUniqueSubsetOfSize3(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        vector<vector<int>> result;
        int n = arr.size();
        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && arr[i - 1] == arr[i]) continue;
            for (int j = i + 1; j < n - 1; j++) {
                if (j > i + 1 && arr[j - 1] == arr[j]) continue;
                for (int k = j + 1; k < n; k++) {
                    if (k > j + 1 && arr[k - 1] == arr[k]) continue;
                    vector<int> cur = {arr[i], arr[j], arr[k]};
                    result.push_back(cur);
                }
            }
        }

        return result;
    }

    static void print(vector<vector<int>>& result) {
        cout << "Result: {";
        for (auto& arr : result) cout << arr << ",";
        cout << "}";
        cout << endl;
    }
};