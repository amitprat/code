#include "../header.h"

class Permutations {
   public:
    static void test() {
        Permutations obj;

        vector<string> inputs = {
            "abc", "aba", "aac"};

        for (auto& input : inputs) {
            cout << "Permutations for input: " << input << endl;
            auto res1 = obj.permutations_recursive(input);
            auto res2 = obj.permutations_recursive_alternative(input);

            auto sortedres1 = res1;
            auto sortedres2 = res2;
            sort(sortedres1.begin(), sortedres1.end());
            sort(sortedres2.begin(), sortedres2.end());
            assert(areEqual<string>(sortedres1, sortedres2));
            cout << "Normal permutations are: res1: " << res1 << endl;
            cout << "Normal permutations are: res2: " << res2 << endl;

            auto res3 = obj.permutationsUsingSTL(input);
            cout << "STL unique permutations are: " << res3 << endl;

            auto res4 = obj.generatePermutationsWithDuplicates(input);
            cout << "Unsorted unique permutations are: " << res4 << endl;
            auto sortedres4 = res4;
            sort(sortedres4.begin(), sortedres4.end());

            auto res5 = obj.getSortedPermutationsWithDuplcates(input);
            // assert(areEqual<string>(res3, sortedres4));
            assert(areEqual<string>(sortedres4, res5));
            cout << "Sorted unique permutations are: " << res5 << endl;

            cout << endl;
        }
    }

   private:
    vector<string> permutations_recursive(string str) {
        vector<string> result;
        permutations_recursive(str, 0, str.length(), result);

        return result;
    }

    void permutations_recursive(string str, int idx, int n, vector<string>& result) {
        if (idx == n) {
            result.push_back(str);
            return;
        }

        for (int i = idx; i < n; i++) {
            swap(str[idx], str[i]);
            permutations_recursive(str, idx + 1, n, result);
            swap(str[idx], str[i]);
        }
    }

   private:
    vector<string> permutations_recursive_alternative(string str) {
        vector<string> result;
        permutations_recursive_alternative(str, "", result);

        return result;
    }

    void permutations_recursive_alternative(string str, string cur, vector<string>& result) {
        if (str.length() == 0) {
            result.push_back(cur);
            return;
        }

        for (int i = 0; i < str.length(); i++) {
            string left = str.substr(0, i);
            string right = str.substr(i + 1);

            string rest = left + right;  // except the current character
            permutations_recursive_alternative(rest, cur + str[i], result);
        }
    }

   private:
    vector<string> permutationsUsingSTL(string str) {
        vector<string> result;
        do {
            result.push_back(str);
        } while (next_permutation(str.begin(), str.end()));

        return result;
    }

   private:
    vector<string> generatePermutationsWithDuplicates(string& str) {
        vector<string> output;
        generatePermutationsWithDuplicates(str, 0, str.length(), output);

        return output;
    }

    void generatePermutationsWithDuplicates(string& str, int idx, int n, vector<string>& output) {
        if (idx == n) {
            output.push_back(str);
            return;
        }

        for (int i = idx; i < n; i++) {
            // Skip if same character has already been fixed at idx
            // This works only for sorted string where duplicates are already together.
            // If not, then we need to use used vector to skip existing used characters
            // which aren't placed together.
            if (i != idx && str[idx] == str[i]) continue;

            swap(str[idx], str[i]);
            generatePermutationsWithDuplicates(str, idx + 1, n, output);
            swap(str[idx], str[i]);
        }
    }

   private:
    vector<string> getSortedPermutationsWithDuplcates(string& str) {
        vector<string> output;
        getSortedPermutationsWithDuplicates(str, output);

        return output;
    }

    void getSortedPermutationsWithDuplicates(string& str, vector<string>& output) {
        sort(str.begin(), str.end());

        while (true) {
            output.push_back(str);  // push the current str (original)

            // find the next element in sorted array from back
            int idx = -1;
            for (int i = str.length() - 2; i >= 0; i--) {
                if (str[i] < str[i + 1]) {
                    idx = i;
                    break;
                }
            }

            // if string is already reverse sorted, no further permutations are possible
            if (idx == -1) break;

            // find the next smallest element on right side which is larger than arr[idx]
            int idx1 = ceil(str, idx);

            // swap the order
            swap(str[idx], str[idx1]);

            // reverse/sort the array after the idx to get minimize the str on right side.
            // reverse also works here as the string on right side is already reverse sorted.
            // sort(str.begin() + idx + 1, str.end());
            std::reverse(str.begin() + idx + 1, str.end());
        }
    }

    int ceil(string& str, int i) {
        int idx = i + 1;
        for (int j = i + 1; j < str.length(); j++) {
            if (str[j] > str[i] && str[j] < str[idx]) {
                idx = j;
            }
        }

        return idx;
    }

   public:
    static void permuteWithDups(string& str) {
        unordered_map<char, int> count;
        for (auto& ch : str) count[ch]++;

        vector<string> result;
        permuteWithDups(str, count, str.length(), "", result);
    }

    static void permuteWithDups(string& str, unordered_map<char, int>& count, int remaining, string prefix,
                                vector<string>& result) {
        if (remaining == 0) {
            result.push_back(prefix);
            return;
        }

        for (auto& ch : str) {
            if (count[ch]) {
                count[ch]--;
                permuteWithDups(str, count, remaining - 1, prefix + ch, result);
                count[ch]++;
            }
        }
    }

   public:
    static void permute(string& str, int i, int n) {
        if (i == n) {
            cout << str << " ";
            return;
        }

        for (int j = i; j < n; j++) {
            swap(str[i], str[j]);
            permute(str, i + 1, n);
            swap(str[i], str[j]);
        }
    }

    static void permute_stl(string str, int i, int n) {
        // sort(str.begin(), str.end());
        do {
            cout << str << " ";
        } while (next_permutation(str.begin(), str.end()));
    }

    static void permute_withoutdup(string str, int i, int n) {
        sort(str.begin(), str.end());
        do {
            cout << str << " ";
        } while (nextPermutation(str));
    }

    static bool nextPermutation(string& str) {
        int s = str.length() - 2;
        while (s >= 0 && str[s] >= str[s + 1]) s--;

        if (s < 0) return false;

        int e = s + 1;
        for (int i = e + 1; i < str.length(); i++) {
            if (str[i] < str[e] && str[i] > str[s]) e = i;
        }

        swap(str[s], str[e]);

        sort(str.begin() + s + 1, str.end());

        return true;
    }

   public:
    bool permute(vector<int>& arr, int index, int n, unordered_set<int>& visited) {
        if (visited.size() == n) return true;
        if (index == arr.size() || arr[index] != 0) return false;

        for (int i = 1; i <= n; i++) {
            if (visited.find(i) != visited.end()) continue;
            if (arr[index + i + 1] != 0) continue;

            arr[index] = arr[index + i + 1] = i;
            visited.insert(i);

            if (permute(arr, index + 1, n, visited)) return true;

            arr[index] = arr[index + i + 1] = 0;
            visited.erase(i);
        }
        return false;
    }
};