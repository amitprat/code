#pragma once
#include "../Header.h"

class SumOfFourNumbers {
public:
    static void test() {
        SumOfFourNumbers obj;
        int N = 5, K = 3;
        int A[] = { 0,0,2,1,1 };

        auto res = obj.getFourSum1(A, N, K);
        cout << to_string(res) << endl;
    }

    vector<vector<int>> getFourSum(int A[], int N, int K) {
        sort(A, A + N);
        unordered_map<int, pair<int, int>> map;
        for (int i = 0; i < N; i++) {
            while (i != 0 && A[i] == A[i - 1]) i++;
            for (int j = i + 1; j < N; j++) {
                while (j != 0 && A[j] == A[j - 1]) j++;
                int cur = A[i] + A[j];
                map[cur] = { i,j };
            }
        }

        vector<vector<int>> result;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                int cur = A[i] + A[j];
                if (map.find(K - cur) != map.end()) {
                    auto& res = map[K - cur];
                    if (res.first != i && res.second != j) {
                        vector<int> curRes = { A[res.first],A[res.second],A[i],A[j] };
                        sort(curRes.begin(), curRes.end());
                        result.push_back(curRes);

                        while (i != 0 && A[i] == A[i - 1]) i++;
                        while (j != 0 && A[j] == A[j - 1]) j++;
                    }
                }
            }
        }

        return result;
    }

    vector<vector<int>> getFourSum1(int A[], int N, int K)
    {
        vector<vector<int>> result;
        sort(A, A + N);
        for (int i = 0; i < N - 3; i++) {
            while (i != 0 && A[i] == A[i - 1]) i++;
            for (int j = i + 1; j < N - 2; j++) {
                while (j > i + 1 && A[j] == A[j - 1]) j++;
                int k = j + 1;
                int l = N - 1;
                int old_k = k;
                int old_l = l;
                while (k < l) {
                    int sum = A[i] + A[j] + A[k] + A[l];
                    if (sum == K) {
                        result.push_back({ A[i],A[j],A[k],A[l] });
                        while (k < l && A[old_k] == A[k]) k++;
                        while (k < l && A[old_l] == A[l]) l--;
                    }
                    else if (sum < K) k++;
                    else l--;
                }
            }
        }

        return result;
    }
};