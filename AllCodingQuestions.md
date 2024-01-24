## [Print Triplets which sums to Zero](https://careercup.com/question?id=10033132)
- Using hash method to store the sum -> paired hash value. 
- Time = O(n2), Space = O(n)
```cpp
void triplets(vector<int>& arr) {
    int sum = 0;
    unordered_map<int, int> map;
    for(int i=0;i<arr.size();i++) {
        for(int j=i+1;j<arr.size();j++) {
            int tsum = arr[i] + arr[j];
            int rsum = sum - tsum;
            if(map.find(rsum) == map.end()) {
                auto k = map[rsum];
                if(i != j && i != k) {
                    cout<<i<<" "<<j<<" "<<k<<endl;
                }
            } else {
                map[arr[i]] = i;
                map[arr[j]] = j;
            }
        }
    }
}
```

- Using sorting method to sort the array and then for every subarray, look for triplets with given sum.
```cpp
void triplets(vector<int>& arr) {
    int sum = 0;
    sort(arr.begin(), arr.end());

    for(int i=0;i<arr.size();i++) {
        int j = i+1;
        int k = arr.size()-1;

        while(j < k) {
            int curSum = arr[i] + arr[j] + arr[k];
            if(curSum == sum) {
                cout<<arr[i]<<" "<<arr[j]<<" "<<arr[k]<<endl;
                j++;k--;
            } else if(curSum < sum) {
                j++;
            } else {
                k--;
            }
        }
    }
}
```

## Given n, output the numbers from 0 to 2^n-1 (inclusive) in n-bit binary form, in such an order that adjacent numbers in the list differ by exactly 1 bit.
- This is problem of generating gray numbers.
- Just do a loop from 0 to 2^n-1 with the following.

```cpp
unsigned int binaryToGray(unsigned int num) {
    return (num >> 1) ^ num;
}
void generateGrayNumbers(int n) {
    for(int i=0;i<n;i++) {
        auto cur = binaryToGray(i);
        cout<<cur<<" ";
    }
}
```

## Subarray Product Less Than K
- Use sliding window approach with 2 pointers. Fast pointer to track the current product of subarray and slow pointer to reduce the current product to < k.
```cpp
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    int sum = 1;
    int count = 0;

    for(int i=0,j=0;j<nums.size();j++) {
        sum *= nums[j];
        while(i <= j && sum >= k) {
            sum /= nums[i++];
        }

        count += (j-i+1);
    }

    return count;
}
```

## Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
- Using hashmap approach.
- Sorting method doesn't work here as that will change the order of elements. 
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    int index = 0;
    for(auto& num : nums) {
        int rsum = target - num;
        if(map.find(rsum) != map.end()) {
            return {map[rsum], index};
        } else {
            map[num] = index;
        }

        index++;
    }

    return {-1,-1};
}
```

## Find pair of numbers in an integer array with given sum.
- This is finding the pairs so we can use either hash method or sorting based on Time and space complexity requirements.
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());

    int i = 0, j = nums.size()-1;
    while(i < j) {
        if(nums[i] + nums[j] == target) return {i,j};
        else if(nums[i] + nums[j] < target) i++;
        else j--;
    }

    return {-1,-1};
}
```

## Longest Substring Without Repeating Characters
- Given an string, find the longest substring in it without repeating characters.
- Time = O(n)
```cpp
int lengthOfLongestSubstring(string s) {
    vector<int> map(256, -1);
    int i = 0, j =0;
    int mxLen = 0;

    for(;j<s.length();j++) {
        char ch = s[j];
        if(map[ch] != -1) { // if this character is already seen
            mxLen = max(mxLen, j-i); // get current max len (excluding current character)
            while(i<=map[ch]) { // remove the characters <= map[ch]
                char ch1 = s[i];
                map[ch1] = -1;
                i++;
            }
        }

        map[ch] = j; // mark current character
    }
    mxLen = max(mxLen, j-i); // get max length from end

    return mxLen;
}
```

## Square root of a number using binary search
```cpp
int squareRoot(int num) {
    int l = 1, r = num;
    int res = -1;

    while(l <= r) { // do binary search
        int m = l + (r-l)/2; // to avoid overflow
        if(m <= num/m) { // to avoid overflow
            res = m; // always consider the smaller integer before it
            l = m+1; // keep looking for more accurate result
        } else {
            r = m-1; // ignore the values which result in > num and look on left.
        }
    }

    return res;
}
```

## Square root of a floating point number using newton-raphson method
```cpp
float squareRoot(float n) {
    double x = 1, y = n;
    double e = 0.00001;

    // keep doing binary search between 2 numbers until the differnce
    // becomes less than expected diff.
    // first number = (first number + second number) / 2
    // second number = number / first number
    while(abs(x-y) > e) {
        x = (x+y)/2.0;
        y = n/x;
    }

    return x;
}
```

## Find leaves from preorder of BST.

```cpp
vector<int> getLeaves(vector<int> &pre) {
vector<int> leaves;
stack<int> st;

int prev = 0;
for (auto &e : pre) {
    // find the ancestor of current node which is greater than current node.
    int ancestor = 0;
    while (!st.empty() && st.top() < e) {
        ancestor = st.top();
        st.pop();
    }

    // if ancestor is greater than prev node, add it to leaves.
    if (ancestor > prev) {
        leaves.push_back(prev);
    }

    // push the current node to stack and set it to prev.
    st.push(e);
    prev = e;
}

// insert the last node.
if (!st.empty()) {
    leaves.push_back(prev);
}

return leaves;
}
```

## Construct BST from preorder

```cpp
Node *constructBst(vector<int>& pre)
{
int n = pre.size();
return constructBst(pre, 0, pre[0], INT_MIN, INT_MAX, n);
}
Node *constructBst(vector<int>& pre, int preIndex, int key, int mn, int mx, int sz) {
if(preIndex >= sz) return nullptr;

Node *root = nullptr;
if(key > mn && key < mx) {
    root = new Node(key);
    preIndex++;

    if(preIndex < sz) root->left = constructBst(pre, preIndex, pre[preIndex], mn, key, sz);
    if(preIndex < sz) root->right = constructBst(pre, preIndex, pre[preIndex],key, mx, sz);
}

return root;
}
```

## Kth Largest in Array

### Kth largest using sorting

***Complexity: O(nlogn)***

```cpp
int kthLargestUsingSorting(vector<int>& arr, int k) {
sort(arr.begin(), arr.end(), [](const auto& f, const auto& s) { return f > s; });

return arr[k - 1];
}
```

### Kth largest using max heap

***Complexity: O(nlogn)***

```cpp
template <class T>
class Heap {
vector<T> arr;
int sz = 0;
std::function<bool(const T&, const T&)> compare;

public:
Heap(std::function<bool(const T&, const T&)> compare) : compare(compare) {}

void push(T e) {
    arr.push_back(e);
    sz++;

    upHeapify(sz - 1);
}

T top() {
    return arr[0];
}

T pop() {
    auto e = arr[0];
    arr[0] = arr[sz - 1];
    sz--;

    downHeapify(0);

    return e;
}

bool empty() {
    return sz == 0;
}

private:
void upHeapify(int idx) {
    T p = parent(idx);
    while (idx != 0 && compare(arr[p], arr[idx])) {
        swap(arr[idx], arr[p]);
        idx = p;
        p = parent(idx);
    }
}

void downHeapify(int idx) {
    int largestIndex = idx;

    int l = left(idx);
    if (l < sz && compare(arr[largestIndex], arr[l])) largestIndex = l;

    int r = right(idx);
    if (r < sz && compare(arr[largestIndex], arr[r])) largestIndex = r;

    if (idx != largestIndex) {
        swap(arr[idx], arr[largestIndex]);

        downHeapify(largestIndex);
    }
}

int parent(int idx) { return (idx - 1) / 2; }
int left(int idx) { return 2 * idx + 1; }
int right(int idx) { return 2 * idx + 2; }
};

int kthLargestUsingHeap(vector<int>& arr, int k) {
Heap<int> heap([](const auto& f, const auot& s) { return f < s; });
for (auto& e : arr) heap.push(e);

int elem = INT_MIN;
while (!heap.empty() && k--) {
    elem = heap.pop();
}

return k > 0 ? INT_MIN : elem;
}
```

### Kth largest using selection algorithm

***Average=O(n), Max = O(n^2)***

```cpp
int kthLargest(vector<int>& arr, int k) {
return kthLargest(arr, 0, arr.size() - 1, k);
}

int kthLargest(vector<int>& arr, int l, int r, int k) {
if (l > r) return INT_MIN;

int p = partition(arr, l, r);
int q = r - p + 1;  // larger elements on right

if (k == q)
    return arr[p];
else if (q < k)
    return kthLargest(arr, l, p - 1, k - q);
else
    return kthLargest(arr, p + 1, r, k);
}

int partition(vector<int>& arr, int l, int r) {
int pivot = arr[r];
int low = l;
for (int i = l; i < r; i++) {
    if (arr[i] <= pivot) {
        swap(arr[low++], arr[i]);
    }
}
swap(arr[low], arr[r]);

return low;
}
```

### Print k largest elements

```cpp
void printKLargestElements(vector<int>& arr, int k) {
auto pos = kthLargestIndex(arr, 0, arr.size() - 1, k);
for (int i = pos; i < arr.size(); i++) cout << arr[i] << " ";
cout << endl;
}
int kthLargestIndex(vector<int>& arr, int l, int r, int k) {
if (l > r) return INT_MIN;

int p = partition(arr, l, r);
int q = r - p + 1;  // larger elements on right

if (k == q)
    return p;
else if (q < k)
    return kthLargestIndex(arr, l, p - 1, k - q);
else
    return kthLargestIndex(arr, p + 1, r, k);
}
```

## Is Valid parenthesis

```cpp
bool isValid(string s) {
stack<char> st;
for(auto ch : s) {
    if(isOpen(ch)) st.push(ch);
    else {
        if(st.empty()) return false;
        if(!isMatch(st.top(), ch)) return false;
        st.pop();
    }
}

return st.empty();
}

bool isOpen(char ch) {
return ch == '[' || ch == '{' || ch == '(';
}

bool isMatch(char open, char close) {
return (open == '[' && close == ']') 
        || (open == '{' && close == '}') 
        || (open == '(' && close == ')');
}
```

## Minimum number of meeting rooms required.

***Approach 1***

```cpp
int minNumberOfMeetingRooms1(vector<Interval>& meetings) {
priority_queue<int, vector<int>, greater<int>> minHeap;
sort(meetings.begin(), meetings.end(), [](auto& f, auto& s) { return f.start < s.start; });

for (auto& meeting : meetings) {
    if (!minHeap.empty() && meeting.start >= minHeap.top()) {
        minHeap.pop();
    }
    minHeap.push(meeting.end);
}

return minHeap.size();
}
```

***Aproach 2***

```cpp
void minNumberOfMeetingRooms2(vector<Interval>& meetings) {
auto comparator = [](const auto& f, const auto& s) { return f.end < s.end; };
list<priority_queue<Interval, vector<Interval>, decltype(comparator)>> minHeaps;
sort(meetings.begin(), meetings.end(), [](auto& f, auto& s) { return f.start < s.start; });

for (auto& meeting : meetings) {
    bool found = false;
    for (auto& q : minHeaps) {
        if (!q.empty() && meeting.start >= q.top().end) {
            q.push(meeting);
            found = true;
            break;
        }
    }

    if (!found) {
        minHeaps.push_back({});
        minHeaps.back().push(meeting);
    }
}

for (auto& q : minHeaps) {
    while (!q.empty()) {
        auto interval = q.top();
        cout << interval.to_string() << " ";
        q.pop();
    }
    cout << endl;
}

cout << format("Minimum number of meeting rooms required={}", minHeaps.size()) << endl;
}
```

***Approach 3***

```cpp
private:
int minNumberOfMeetingRooms3(vector<Interval>& meetings) {
vector<pair<int, char>> vals;

for (auto& meeting : meetings) {
    vals.push_back({meeting.start, 'f'});
    vals.push_back({meeting.end, 's'});
}

sort(vals.begin(), vals.end(), [](const auto& f, const auto& s) {
    if (f.first < s.first) return true;
    if (f.first > s.first) return false;
    return f.second < s.second;
});

int minRooms = 0;
int cur = 0;
for (auto& val : vals) {
    if (val.second == 'f')
        cur++;
    else {
        minRooms = max(minRooms, cur);
        cur--;
    }
}

return minRooms;
}
```

## Maximum sum subsequence of non-consecutive numbers.

```cpp
int maxSumSubsequence(vector<int>& nums) {
int n = nums.size();
if(n == 0) return 0;
if(n == 1) return nums[0];

vector<int> table(n);
table[0] = nums[0];
table[1] = max(nums[0], nums[1]);

for(int i=2;i<n;i++) {
    table[i] = max(table[i-1], nums[i] + table[i-2]);
}

return table[n-1];
}
```

## Maximum sum subsequence without consecutive numbers

```cpp
int maxSumSubsequenceRecursive(vector<int>& nums) {
return maxSumSubsequenceRecursive(nums, 0, nums.size(), 0);
}

int maxSumSubsequenceRecursive(vector<int>& nums, int idx, int sz, int cur) {
if (idx == sz) return 0;
if (idx == sz - 1) return nums[idx];
if (idx == sz - 2) return max(nums[idx], nums[idx + 1]);

return max(maxSumSubsequenceRecursive(nums, idx + 1, sz, cur),
            nums[idx] + maxSumSubsequenceRecursive(nums, idx + 2, sz, cur));
}
```

```cpp
int maxSumSubsequence(vector<int>& nums) {
int n = nums.size();
if (n == 0) return 0;
if (n == 1) return nums[0];

vector<int> table(n);
table[0] = nums[0];
table[1] = max(nums[0], nums[1]);

for (int i = 2; i < n; i++) {
    table[i] = max(table[i - 1], nums[i] + table[i - 2]);
}

return table[n - 1];
}
```

### Print combinations

```html
https://careercup.com/question?id=5634222671790080

Given a string as input, return the list of all the patterns possible:


'1' : ['A', 'B', 'C'], 
'2' : ['D', 'E'],
'12' : ['X']
'3' : ['P', 'Q']
Example if input is '123', then output should be [ADP, ADQ, AEP, AEQ, BDP, BDQ, BEP, BEQ, CDP, CDQ, CEP, CEQ, XP, XQ]
```

```cpp
void printCombinations(string str) {
unordered_map<string, list<string>> map = {
    {"1", {"A", "B", "C"}},
    {"2", {"D", "E"}},
    {"12", {"X"}},
    {"3", {"P", "Q"}}};

vector<string> curResult;
printCombinations(str, map, curResult);
}

void printCombinations(string str, unordered_map<string, list<string>>& map, vector<string>& curResult) {
if (str.empty()) {
    cout << curResult << endl;
    return;
}

for (int i = 1; i <= str.size(); i++) {
    string cur = str.substr(0, i);
    string rest = str.substr(i);

    for (auto& e : map[cur]) {
        curResult.push_back(e);
        printCombinations(rest, map, curResult);
        curResult.pop_back();
    }
}
}
```

## Longest Common Subsequence

```cpp
int longestCommonSubsequenceDP(string text1, string text2) {
int n = text1.size();
int m = text2.size();

vector<vector<int>> table(n+1, vector<int>(m+1));

for(int i=0;i<=n;i++) {
    for(int j=0;j<=m;j++) {
        if(i == 0 || j == 0) table[i][j] = 0;
        else if(text1[i-1] == text2[j-1]) table[i][j] = table[i-1][j-1] + 1;
        else table[i][j] = max(table[i-1][j], table[i][j-1]);
    }
}

return table[n][m];
}
```

```cpp
int longestCommonSubsequenceRecursive(string text1, int n, string text2, int m) {
if(n == 0 || m == 0) return 0;

if(text1[n-1] == text2[m-1]) return 1 + longestCommonSubsequenceRecursive(text1, n-1, text2, m-1);

return max(longestCommonSubsequenceRecursive(text1, n-1, text2, m),
            longestCommonSubsequenceRecursive(text1, n, text2, m-1));
}
```

## Longest common substring

- Recursive method

```cpp
int longestCommonSubstring(string& s1, string& s2) {
int n = s1.length();
int m = s2.length();

return longestCommonSubstring(s1, s2, n, m, 0);
}

int longestCommonSubstring(string& s1, string& s2, int n, int m, int len) {
if(n == 0 || m == 0) return len;

if(s1[n-1] == s2[m-1]) return longestCommonSubstring(s1, s2, n-1, m-1, len+1);
return max(longestCommonSubstring(s1, s2, n-1, m, 0), longestCommonSubstring(s1, s2, n, m-1, 0));
}
```

- DP method

```cpp
int longestCommonSubstring(string& s1, string& s2) {
int n = s1.length();
int m = s2.length();
int mxLen = 0;

vector<vector<int>> table(n+1, vector<int>(m+1));
for(int i=0;i<=n;i++) {
    for(int j=0;j<=m;j++) {
        if(i == 0 || j == 0) table[i][j] = 0;
        else if(s1[i-1] == s2[j-1]) table[i][j] = 1+table[i-1][j-1];
        else table[i][j] = 0;

        mxLen = max(mxLen, table[i][j]);
    }
}

return mxLen;
}
```

## Shuffle Array

```cpp
void shuffle(vector<int>& arr) {
int n = arr.size();
for (int i = n - 1; i >= 0; i--) {
    int r = rand() % (i + 1);
    swap(arr[i], arr[r]);
}
}
```

## Shortest common subsequence

```
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
```

```cpp
string shortestCommonSupersequence(string str1, string str2) {
string lcs = getLCS(str1, str2);

// combine all mismatches with lcs string
string result;
int i = 0, j = 0;
for(auto& ch : lcs) {
    while(str1[i] != ch) result += str1[i++];
    while(str2[j] != ch) result += str2[j++];
    result += ch;
    i++,j++;
}

return result + str1.substr(i) + str2.substr(j);
}

string getLCS(string& s1, string& s2) {
int n = s1.length();
int m = s2.length();

// get the lcs length
vector<vector<int>> table(n+1, vector<int>(m+1));
for(int i=0;i<=n;i++) {
    for(int j=0;j<=m;j++) {
        if(i == 0 || j == 0) table[i][j] = 0;
        else if(s1[i-1] == s2[j-1]) table[i][j] = 1 + table[i-1][j-1];
        else table[i][j] = max(table[i-1][j], table[i][j-1]);
    }
}

// determine the actual lcs string
string result;
for(int i=n,j=m;i>0&&j>0;) {
    if(s1[i-1] == s2[j-1]) {
        result += s1[i-1];
        i--;
        j--;
    } else if(table[i-1][j] > table[i][j-1]) {
        i--;
    } else {
        j--;
    }
}

reverse(result.begin(), result.end());

return result;
}
```

## Minimum distance between 2 strings

```
Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.

In one step, you can delete exactly one character in either string.

Input: word1 = "sea", word2 = "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
```

```cpp
int minDistance(string word1, string word2) {
return minDistanceUsingLCS(word1, word2);
}

int minDistanceUsingEditDistance(string word1, string word2) {
int n = word1.length(), m = word2.length();
vector<vector<int>> table(n+1,vector<int>(m+1));

for(int i=0;i<=n;i++) {
    for(int j=0;j<=m;j++) {
        if(i == 0) table[i][j] = j;
        else if(j == 0) table[i][j] = i;
        else if(word1[i-1] == word2[j-1]) table[i][j] = table[i-1][j-1];
        else table[i][j] = 1+min(table[i-1][j], table[i][j-1]);
    }
}

return table[n][m];
}

int minDistanceUsingLCS(string word1, string word2) {
int n = word1.length(), m = word2.length();
vector<vector<int>> table(n+1,vector<int>(m+1));

for(int i=0;i<=n;i++) {
    for(int j=0;j<=m;j++) {
        if(i == 0 || j == 0) table[i][j] = 0;
        else if(word1[i-1] == word2[j-1]) table[i][j] = 1 + table[i-1][j-1];
        else table[i][j] = max(table[i-1][j], table[i][j-1]);
    }
}

int l = table[n][m];

return n+m - 2*l;
}
```

## Longest Palindromic Subsequence

### Finding longest palindromic using recursive method

T = O(2^n)

```cpp
int longestPalinRec(string s) {
return longestPalinRec(s, 0, s.length() - 1);
}

int longestPalinRec(string& s, int l, int r) {
if (l > r) return 0;
if (l == r) return 1;

if (s[l] == s[r]) return 2 + longestPalinRec(s, l + 1, r - 1);
return max(longestPalinRec(s, l + 1, r), longestPalinRec(s, l, r - 1));
}
```

### Finding longest palindromic using recursive method with memoization to avoid recursive calls.

T = O(n^2)

```cpp
int longestPalinUsingMemo(string& s) {
int n = s.length();
vector<vector<int>> table(n, vector<int>(n, -1));

return longestPalinUsingMemo(s, 0, n - 1, table);
}

int longestPalinUsingMemo(string& s, int l, int r, vector<vector<int>>& table) {
if (l > r) return 0;
if (l == r) return 1;
if (table[l][r] != -1) return table[l][r];

if (s[l] == s[r])
    table[l][r] = 2 + longestPalinUsingMemo(s, l + 1, r - 1, table);
else
    table[l][r] = max(longestPalinUsingMemo(s, l + 1, r, table), longestPalinUsingMemo(s, l, r - 1, table));

return table[l][r];
}
```

### Finding palindromic subsequence using DP to match the sublength

T = O(n^2)

```cpp
int longestPalinSubseqUsingDP1(string& s) {
int n = s.length();
vector<vector<int>> table(n, vector<int>(n, 0));
for (int i = 0; i < n; i++) table[i][i] = 1;

for (int l = 2; l <= n; l++) {
    for (int i = 0; i < n - l + 1; i++) {
        int j = i + l - 1;
        if (l == 2 && s[i] == s[j])
            table[i][j] = 2;
        else if (s[i] == s[j])
            table[i][j] = table[i + 1][j - 1] + 2;
        else
            table[i][j] = max(table[i + 1][j], table[i][j - 1]);
    }
}

return table[0][n - 1];
}
```

### Using LCS DP to get the common subsequence between string and its reverse.

T = O(n^2)

```cpp
int longestPalinSubseqUsingLCSDP(string& s1) {
int n = s1.length();
string s2 = s1;
reverse(s2.begin(), s2.end());
vector<vector<int>> table(n + 1, vector<int>(n + 1));

for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
        if (i == 0 || j == 0)
            table[i][j] = 0;
        else if (s1[i - 1] == s2[j - 1])
            table[i][j] = 1 + table[i - 1][j - 1];
        else
            table[i][j] = max(table[i - 1][j], table[i][j - 1]);
    }
}

return table[n][n];
}
```

### Above methods only finds the length of longest palindromic subsequence but not actually prints. Following methods prints it using LCS DP and traverse the table from back and follow the track in reverse direction.

```cpp
void printLongestPalindromicSubsequence(string& s1) {
string s2(s1.rbegin(), s1.rend());

int n = s1.length();

vector<vector<int>> table(n + 1, vector<int>(n + 1));

for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
        if (i == 0 || j == 0)
            table[i][j] = 0;
        else if (s1[i - 1] == s2[j - 1])
            table[i][j] = 1 + table[i - 1][j - 1];
        else
            table[i][j] = max(table[i - 1][j], table[i][j - 1]);
    }
}

string result;
for (int i = n, j = n; i > 0 && j > 0;) {
    if (s1[i - 1] == s2[j - 1]) {
        result += s1[i - 1];
        i--, j--;
    } else if (table[i - 1][j] > table[i][j - 1]) {
        i--;
    } else {
        j--;
    }
}

reverse(result.begin(), result.end());

cout << "Result: " << result << endl;
}
```

## Count subarrays with elements less that K.

```cpp
int countSubarrays(vector<int>& arr, int k) {
int l = 0;
int n = arr.length();
int cnt = 0;
for (int r = 0; r < n; r++) {
    if (arr[r] < k)
        cnt += (r - l + 1);
    else
        l = r + 1;
}

return cnt;
}
```

## Merge overlapping intervals

```cpp
void mergeIntervalsInPlace2(vector<Interval>& intervals) {
sort(intervals.begin(), intervals.end(), [](auto& f, auto& s) { return f.start < s.start; });

vector<Interval> result;
for (auto& interval : intervals) {
    if (result.empty() || result.back().end < interval.start) {
        result.push_back(interval);
    }
    else {
        result.back()[1] = max(result.back().end, interval.end);
    }
}

return result;
}
```

```cpp
void mergeIntervalsInPlace(vector<Interval>& intervals) {
int i = 0;
for (int j = 1; j < intervals.size(); j++) {
    if (overlap(intervals[i], intervals[j])) {
        merge(intervals[i], intervals[j]);
    } else {
        i++;
        intervals[i] = intervals[j];
    }
}

while (intervals.size() > i + 1) intervals.pop_back();
}

bool overlap(Interval it1, Interval it2) {
return it2.start <= it1.end && it2.start >= it1.start;
}

void merge(Interval& it1, Interval& it2) {
it1 = {min(it1.start, it2.start), max(it1.end, it2.end)};
}
```

## Merge 2 sorted arrays

```cpp
vector<Interval> mergeArrays(vector<Interval>& arr1, vector<Interval>& arr2) {
vector<Interval> output;
int i = 0, j = 0;

while (i < arr1.size() && j < arr2.size()) {
    if (arr1[i].start <= arr2[j].start) {
        insertOrMerge(output, arr1[i]);
        i++;
    } else {
        insertOrMerge(output, arr2[j]);
        j++;
    }
}

while (i < arr1.size()) insertOrMerge(output, arr1[i++]);
while (j < arr2.size()) insertOrMerge(output, arr2[j++]);

return output;
}

void insertOrMerge(vector<Interval>& out, Interval it) {
if (out.empty() || it.start > out.back().end) {
    out.push_back(it);
} else {
    auto cur = out.back();
    out.pop_back();
  
    cur = {min(cur.start, it.start), max(cur.end, it.end)};
    out.push_back(cur);
}
}
```

## Count Islands in a matrix with 1s and 0s where 1 represent land and 0 represent water.

- An island a continous land of 1s (moving up, down, left, right)

```
https://careercup.com/question?id=5669768827764736

FB On-site March

Q: Find number of Islands.
XXXOO
OOOXX
XXOOX
Return 3 islands.
1 1 1OO
OOO2 2
3 3OO 2


Followup: If the board is too big to fit in memory, how to get the number?
```

***Using DFS**

- We can mark the matrix itself to mark the visited cells. If that's not allowed, we can use seperate visited matrix for that.

```cpp
int countIslands(vector<vector<int>>& matrix, int n, int m) {
for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
        if(matrix[i][j] == 1) {
            dfs(matrix, i, j);
            cnt++;
        }
    }
}

return cnt;
}
```

- we can use bfs as well instead of dfs in above approach.

***Count without dfs by looking up or left and increase islands count.

```cpp
int countIslands(vector<vector<int>>& matrix, int n, int m) {
int cnt = 0;
for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
        if(matrix[i][j] ==1) {
            if((i == 0 || matrix[i-1][j] == 0) &&
                (j == 0 || matrix[i][j-1] == 0))
            {
                cnt++;
            }
        }
    }
}

return cnt;
}
```

## Longest increasing subsequence

***Using recursion***

```cpp
int longestUsingRecursion(vector<int>& arr) {
return longestUsingRecursion(arr, INT_MIN, 0, arr.size());
}

int longestUsingRecursion(vector<int>& arr, int mn, int l, int n) {
if (l == n) return 0;

int l1 = 0;
if (arr[l] > mn) l1 = 1 + longestUsingRecursion(arr, arr[l], l + 1, n);
int l2 = longestUsingRecursion(arr, mn, l + 1, n);

return max(l1, l2);
}
```

***Using dynamic programming***

```cpp
int longestUsingDP(vector<int>& arr) {
int n = arr.size();
vector<int> table(n, 0);
table[0] = 1;

for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= 0; j--) {
        if (arr[i] > arr[j])
            table[i] = max(table[i], table[j] + 1);
        else
            table[i] = 1;
    }
}

return table[n - 1];
}
```

## Least interval with cooldown period.

```
Input:
N = 6
K = 2
task[ ] = {'A', 'A', 'A', 'B', 'B', 'B'}
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is atleast 2 units of time between any two same tasks.
```

```cpp
int leastInterval(int N, int K, vector<char>& tasks) {
using P = pair<int, int>;
auto comparator = [](const auto& f, const auto& s) { return f.second < s.second; };
priority_queue<P, vector<P>, decltype(comparator)> pq;

unordered_map<char, int> freqMap;
for (auto& task : tasks) freqMap[task]++;

for (auto& e : freqMap) pq.push({e.first, e.second});

int period = 0;
while (!pq.empty()) {
    vector<char> curTasks;

    // add current task to list
    auto cur = pq.top();
    pq.pop();
    curTasks.push_back(cur.first);
    period++;

    // calculate cooldown period
    int cooldown = 0;
    if (pq.size() < K) cooldown = K - pq.size();  // cooldown period

    // reduce frequency of rest of element
    int mn = min((int)pq.size(), K);
    period += mn;
    while (mn--) {
        auto rest = pq.top();
        pq.pop();
        rest.second--;
        if (rest.second) pq.push(rest);
        curTasks.push_back(rest.first);
    }

    // reduce frequency of cur element and add it back to queue
    cur.second--;
    if (cur.second) pq.push(cur);

    // add the remaining cooldown period
    if (pq.size()) {
        period += cooldown;
        vector<char> coolDownTasks(cooldown, '_');
        curTasks.insert(curTasks.end(), coolDownTasks.begin(), coolDownTasks.end());
    }

    cout << curTasks << endl;
}

return period;
}
```

```cpp
int leastInterval2(int N, int K, vector<char>& tasks) {
// code here
int freq[26] = {0};
int maxF = 0;

for (auto i : tasks) {
    freq[i - 'A']++;
    maxF = max(maxF, freq[i - 'A']);
}

int maxFcount = 0;

for (int i = 0; i < 26; i++) {
    if (freq[i] == maxF) maxFcount++;
}

int time = (maxF - 1) * (K + 1) + maxFcount;

return max(time, N);
}
```

## Insert new interval in sorted non-overlapping intervals list

```
https://careercup.com/question?id=5676064539934720

Given a class Range


class Range {
public int begin;
public int end;
public Range(int begin, int end) {
    this.begin = begin;
    this.end = end;
}
}
The problem:
Intput:
1) list of Ranges that don't overlap (not sorted)
2) newRange that might overlap.
Output:
list of merged Ranges

For example:
Input: [1..5] [9..13] [17..22]
newRange: [4..10]
Output: [1..13] [17..22]
```

```java
public Range[] merge(Range[] ranges, Range newRange)
{
List<Range> output = new LinkedList<>();
int b = newRange.begin;
int e = newRange.end;

for (Range r : ranges)
{
    if (r.end < b || r.begin > e)
    {
        output.add(r);
    }
    else
    {
        b = Math.min(b, r.begin);
        e = Math.max(e, r.end);
    }
}
output.add(new Range(b, e));

return output.toArray(new Range[output.size()]);
}
```

## Sort an array of 0 and 1s

- Using swapping

```cpp
void sort(vector<int>& arr) {
int l = 0, r = arr.size()-1;
while(l < r) {
    if(arr[l] == 0) l++;
    else if(arr[m] == 1) m--;
    else swap(arr[l++], arr[m--]);
}
}
```

- Using counting

```cpp
void sort(vector<int>& arr) {
int zeros = 0;
for(int i=0;i<arr.size();i++) if(arr[i] == 0) zeros++;

for(int i=0;i<zeros;i++) arr[i] = 0;
for(int i=zeros;i<arr.size();i++) arr[i] = 1;
}
```

## DNF sort OR sort an array of 0,1,2

```cpp
void sort(vector<int>& arr) {
int l = 0, m = 0, r = arr.size()-1;
while(m <= r) {
    if(arr[m] == 0) swap(arr[l++], arr[m++]);
    else if(arr[m] == 1) m++;
    else swap(arr[m], arr[r--]);
}
}
```

## Find out the two numbers which appear odd number of times.

```
You are given an integer array, where all numbers except for TWO numbers appear even number of times.

1. XOR all the n numbers.
2. Result will be knocked out for all the even pairs as a^a=0 The result now contains only XOR of the two odd out numbers.
3. Find the first bit position in the result that is 1. Definitely this bit position both the odd numbers have different bit values. i.e. one has a 0 and another has a 1 at this position. Let this position be x
4. XOR the elements that have 1 at x bit position and XOR the elements that have 0 at x bit position. The two XOR results would give the two odd count numbers.
```

```cpp
void findNumbers(vector<int>& arr) {
int x = 0, y = 0;

int Xor = 0;
for(auto& e : arr) Xor ^= e;

int lastSetBit = Xor & ~(Xor-1);

for(auot& e : arr) {
    if(e&lastSetBit) x ^= e;
    else y ^= e;
}

cout<<x<<" "<<y<<endl;
}
```

## Flatten a Multilevel Doubly Linked List

- Flatten list using stack.

```cpp
Node *flatten(Node *root) {
stack<Node *> st;
st.push(root);

Node *prev = nullptr;

while(!st.empty()) {
    auto cur = st.top(); st.pop();

    if(cur->next) st.push(cur->next);
    if(cur->child) st.push(cur->child);

    if(!prev) prev = cur;
    else {
        prev->next = cur;
        prev->child = nullptr;
    }
    cur->prev = prev;

    prev = cur;
}
}
```

- Using recursion.

```cpp
Node *flatten(Node *root) {
if(!root) return root;

auto next = root->next;
if(root->child) root->next = flatten(root->child);
if(root->next) root->next->prev = root;

while(root->next) root = root->next;
root->next = flatten(next);
if(root->next) root->next->prev = root;
}
```

## Binary tree to doubly linked list

```cpp
Node * binaryTreeToDLL(Node *root)
{
Node *next = nullptr;
return bToDLL(root, next);
}

Node * binaryTreeToDLL(Node *root, Node *& next)
{
if(!root) return root;

binaryTreeToDLL(root->right, next);

root->right = next;
if(next) next->left = root;
next = root;

binaryTreeToDLL(root->left, next);

return next;
}
```

## Print string in sorted order

```
https://careercup.com/question?id=5680043955060736

Output top N positive integer in string comparison order. For example, let's say N=1000, then you need to output in string comparison order as below:
1, 10, 100, 1000, 101, 102, ... 109, 11, 110, ...
```

```cpp
public static void main(String[] args) {
    for(int i=1;i<;10;i++)
        printRec(""+i, 1000);
}
static void printRec(String str, int n){
    if(Integer.parseInt(str) > n)
        return;

    System.out.println(str);
    for(int i=0;i<;10;i++)
        printRec(str+i,n);
}
```

## Area under histogram OR Largest Rectangle in Histogram
- Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

- Approach 1
```cpp
int largestRectangleArea(vector<int>& heights) {
    int area = 0;
    stack<int> st;

    for(int i=0;i<=heights.size();i++) {
        // if we see a bar with lesser height than top of stack, pop those bars and calculate their areas (without considering current bar).
        while(!st.empty() && (i == heights.size() || heights[st.top()] > heights[i])) {
            int height = heights[st.top()]; st.pop();
            int width = st.empty() ? i : (i-1)-st.top();

            int curArea = height * width;
            area = max(area, curArea);
        }
        if(i < heights.size()) st.push(i);
    }

    return area;
}
```

- Approach 2
```cpp
int area(vector<int>& hist) {
    int area = 0;
    stack<int> st;

    int i = 0;
    while(i < hist.size()) {
        // if current bar is higher or equal to previous bar, then push current bar to stack.
        if(st.empty() || hist[i] >= hist[st.top()]) {
            st.push(i);
        } else { // don't consider the bar at current position yet. Calculate area of rectables formed by existing bars in stack.
            int height = hist[st.top()]; st.pop();
            int width = st.empty() ? i : (i-1) - st.top(); // width without considering the current bar

            int curArea = height * width;
            area = max(area, curArea);
        }
    }

    // while there are still more bars in stack, they must be all arranged in increasing height order so we can calculate the area from right;
    while(!st.empty()) {
        int height = hist[st.top()]; st.pop();
        int width = st.empty() ? i : (i-1)-st.top();
        area = max(area, curArea);
    }

    return area;
}
```

## Trapped Rain Water
- Given bars of various heights, we consider the trapped water between those bars.
```cpp
int trapWater(vector<int>& heights) {
    int edgeLevel = 0;
    int l = 0, r = heights.size()-1;
    int water = 0;

    while(l < r) {
        int curLevel = min(heights[l], heights[r]); // take the minimum of level on both ends

        // move the pointer from the shorter bar side.
        if(curLevel == heights[l]) l++;
        else r--;

        edgeLevel = max(edgeLevel, curLevel); // keep track of maximum edge level seen so far.

        water += edgeLevel - curLevel; // the height difference between the current Level and max edge level will give the water hold on top of current bar
    }

    return water;
}
```

## Largest Rectangle Sum
- Given a matrix of negative and positive numbers. Find the rectangle in matrix with highest sum.

- Approach:
    - Keep summing the matrix elements row by row (from top to bottom as cumulative sum) for each set of rows. For example(row0, row0+row1, row0+row1+row2,...,row1,row1+row2,..)
    - In the current cumulative sum, find the max sum subarray using kadane's algorithm.

## Largest Binary Rectangle
- Given a matrix of binary numbers. Find the largest reactangle made by all 1s.

Approach:
    - Keep summing the cells row by row. (same as above). Only additional thing is to only sum the cells if current cell value is 1 else keep it as 0. This will bar heights at each column position.
    - We can't use kadane's algorithm here as it will given the largest reactangle sum which will includes all cells as there values are positive. Even if we represent the '0' as '-1', then also it will some even though they don't have all 1s.
    - We need to use histogram apporach here to find largest rectangle under histogram.

```cpp
int largestBinaryRectangle(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int largestArea = 0;

    for(int i=0;i<n;i++) {
        vector<int> cumSum(m, 0);
        for(int j=i;j<n;j++) {
            for(int k=0;k<m;k++) {
                if(matrix[j][k] == 0) curSum[k] = 0;
                else cumSum[k] += matrix[j][k];
            }

            int area = areaUnderHistogram(cumSum);
            largestArea = max(largestArea, area);
        }
    }

    return largestArea;
}
```

- If the matrix is arranged such that all zeros are on top and 1s on bottom in a column. Then, we don't need to do pair sum of each row.
- If we allowed to modify matrix, then we can do incremental cumSum on matrix itself (adding row by row as we move down).
- Then, on each matrix row, find the largest histogram area.
```java
int largestBinaryRectangle(int[][] matrix) {
    int mxRectangle = 0;
    for (int r = 0; r < matrix.length; r++) {
        if (r != 0) {
            for (int c = 0; c < matrix[r].length; c++) {
                if (matrix[r][c] == 1) matrix[r][c] += matrix[r - 1][c];
            }
        }
        mxRectangle = Math.max(mxRectangle, areaUnderHist(matrix[r]));
    }

    return mxRectangle;
}
```

## Largest rectangle sorrounded by 1s. OR largest land area sorrounded by water where water is represented as 0 and land as 1.
- T=O(n2), S=O(n2)
```java
private int largestArea(int[][] mat) {
    int n = mat.length;
    int m = mat[0].length;
    Point[][] memo = new Point[n][m]; // 0 initialized
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            memo[i][j] = new Point(0, 0);
        }
    }

    // prepare the count of 1s on top and left to current cell.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 1) {
                if (i == 0 && j == 0) memo[i][j] = new Point(1, 1);
                else if (i == 0) memo[i][j] = new Point(memo[i][j - 1].x + 1, 1);
                else if (j == 0) memo[i][j] = new Point(1, memo[i - 1][j].y + 1);
                else memo[i][j] = new Point(memo[i][j - 1].x + 1, memo[i - 1][j].y + 1);
            }
        }
    }

    // printing
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            System.out.print(memo[i][j] + "\t");
        }
        System.out.println();
    }

    // iterate from right bottom and calculate the max subsquare
    int mxArea = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (mat[i][j] == 1) {
                int curLen = Math.min(memo[i][j].x, memo[i][j].y);
                while (curLen != 0) {
                    boolean isSquare = memo[i - curLen + 1][j].x >= curLen &&
                            memo[i][j - curLen + 1].y >= curLen;

                    if (isSquare) {
                        mxArea = Math.max(mxArea, curLen);
                        break;
                    }
                    curLen--;
                }
            }
        }
    }

    return mxArea;
}
```

- Another approach using checking each col, left->right on each row and check if subsquare formed by (row, col) and size = N-max(row, col) is a valid subsquare with black boundary.
```cpp
tuple<int, int, int> findLargestSubsqaure(vector<vector<int>>& matrix) {
    int maxSz = 0;
    int col = 0;
    int N = matrix.size();
    tuple<int, int, int> result;

    while (N - col > maxSz) {
        for (int row = 0; row < N; row++) {
            int size = N - max(row, col);
            while (size > maxSz) {
                if (isSquareWithBlackBoundary(matrix, row, col, size)) {
                    maxSz = size;
                    result = {row, col, size};
                    break;
                }
                size--;
            }
        }
        col++;
    }
    return result;
}

bool isSquareWithBlackBoundary(vector<vector<int>>& matrix, int r, int c, int sz) {
    // check first and last column for each row
    for (int i = r; i < r + sz; i++) {
        if (!matrix[i][c] || !matrix[i][c + sz - 1]) // first and last column cell in this row.
            return false;
    }

    // check first and last row for each column
    for (int i = c; i < c + sz; i++) {
        if (!matrix[r][i] || !matrix[r + sz - 1][i]) // first and last row cell in this column.
            return false;
    }
    return true;
}
```

## [Find Disjoint continuous subarray with max diff.](https://www.careercup.com/question?id=19286747)
- Given an integer array like {2, -1, -2, 1, -4, 2, 8}. Find two subarrays in it which have maximum difference.
- For example: one solution is: {-1, -2, 1, -4}, {2, 8}

- Approach:
    - Find the minimum sum subarrays from left and store their sum in an array.
    - Find the maximum sum subarrays from right and store their sum in another array.
    - Now, iterator array again and for each index, find the leftSum <= i and rightSum >=i+1 and update maxDiff.

```java
private int findMaxDiff(int[] arr) {
    List<Integer> minArr = new ArrayList<>();
    int i = 0, j = 0;
    int sum = 0;
    while (j < arr.length) {
        sum += arr[j++];
        while (i < j && arr[i] >= 0) sum -= arr[i++];
        if (sum >= 0) {
            i = j;
            sum = 0;
        }
        minArr.add(sum);
    }

    i = arr.length-1;
    j = arr.length-1;
    sum = 0;
    List<Integer> maxArr = new ArrayList<>();
    while (j >= 0) {
        sum += arr[j--];
        while (i > j && arr[i] < 0) sum -= arr[i--];
        if (sum <= 0) {
            i = j;
            sum = 0;
        }
        maxArr.add(sum);
    }

    int mxDiff = Integer.MIN_VALUE;
    for (i = 0; i < arr.length; i++) {
        mxDiff = Math.max(mxDiff, maxArr.get(i) - minArr.get(i));
    }

    return mxDiff;
}
```
- This might not be correct as we need to calculate 4 arrays for min and max subarray from left and right.
- Then, need to calculate absolute max difference.

- Psuedo code
```python
int maxDiffSubArrays(arr):
    (minSumArrFromLeft, maxSumArrFromLeft) = calculateMaxAndMinSumSubarraysSumUsingKadane(arr, 0, n-1, 1)
    (minSumArrFromRight, maxSumArrFromRight) = calculateMaxAndMinSumSubarraysSumUsingKadane(arr, n-1, 0, -1)

    int mxDiff = 0;
    for i to n-1:
        mxDiff = max(mxDiff, 
                            max(abs(maxSumArrFromRight[i+1]-minSumArrFromLeft[i]),
                                abs(maxSumArrFromLeft(i)-minSumArrFromRight[i+1])
                    )

    return mxDiff

(minArr, mxArr) calculateMaxAndMinSumSubarraysSumUsingKadane(arr, s, e, i):
    minArr = []
    mxArr =  []

    mnSum = INT_MAX;
    mxSum = INT_MIN;
    curMinSum = 0
    curMaxSum = 0;
    for(j=s;i > 0 ? j<=e : j>=e;j-=i):
        curMinSum += arr[j]
        curMaxSum += arr[j]

        mnSum = min(mnSum, curMinSum)
        mxSum = max(mxSum, curMaxSum)

        if curMinSum > 0:
            curMinSum = 0
        
        if curMaxSum < 0:
            curMaxSum = 0

        minArr[j] = mnSum
        mxArr[j] = mxSum
```

## Find largest contiguous sequence in an array
- Example: {1, 6, 10, 4, 7, 9, 5, 9, 11,13,12}, Output: [6,4,7,5]

```cpp
vector<int> largestSequence(vector<int>& arr) {
    unordered_map<int, int> rangeMap;
    int mn = 0, mx = -1;

    for(int i=0;i<arr.size();i++) {
        int beg = arr[i], end = arr[i];
        if(rangeMap.find(beg-1) != rangeMap.end())
            beg = rangeMap[beg-1];
        if(rangeMap.find(end+1) != rangemap.end())
            end = rangeMap[end+1];

        rangeMap[beg] = end;
        rangeMap[end] = beg;

        if(end-beg+1 > mx-mn+1) {
            mn = beg;
            mx = end;
        }
    }

    vector<int> result;
    for(int i=mn;i<=mx;i++) result.push_back(i);

    return result;
}
```

## K Sorted Array Iterator OR K-Sorting
- Given n sorted arrays. Print elements in sorted order from all arrays. Provide it in form of iterator;

```cpp
class KSortIterator {
    vector<vector<int>> arrs;

    vector<pair<int, int>> indices;
public:
    KSortIterator(vector<vector<int>>& arrs) : arrs(arrs) {
        for(int i=0;i<arrs.size();i++) {
            indices.push_back({i, 0});
        }
    }

    bool hasNext() {
        return indices.size() > 0;
    }

    int next() {
        int mnArrPos = -1;
        int mnElemSoFar = INT_MAX;
        for(int i=0;i<indices.size();i++) {
            auto e = indices[i];
            if(arrs[e.first][e.second] < mnElemSoFar) {
                mnElemSoFar = arrs[e.first][e.second];
                mnArrPos = i;
            }
        }

        if(indices[mnArrPos].second+1 < arrs[indices[mnArrPos].first].size()) {
            indices[mnArrPos].second += 1;
        } else {
            indices.erase(indices.begin() + mnArrPos);
        }
    }
};
```

## Max subarray with K unique values
- Can be solved by keeping an map of <array element to count>
- Keep two pointers in array : start and end.
- Keep inserting or increment count in map using end pointer.
- If map size > k, then increment start pointer until end pointer and map size becomes <= k
- Keep track of {mnS, mxE} pointers to keep track of max subarray encountered.

## [Find minimum distance between given 2 words in an array or a sentence.](https://www.careercup.com/question?id=6273553081040896)
 - https://www.geeksforgeeks.org/find-the-minimum-distance-between-the-given-two-words/
```cpp
int minimumDistance(string sentence, string word1, string word2) {
    vector<string> words = split(sentence, ' ');

    int word1Index = -1, word2Index = -1;
    for(int i=0;i<words.size();i++) {
        if(words[i] == word1) {
            word1Index = i;
        } else if(words[i] == word2) {
            word2Index = i;
        }

        if(word1Index != -1 && word2Index != -1) {
            mnDistance = min(minDistance, abs(word2Index-word1Index));
        }

        return mnDistance;
    }
}
```

## Rearrange positive/negative numbers
- Rearrange numbers in array such that all negative numbers comes first and then positive numbers. Keep the same order.
- Example: {1,-2,3,-4,-5,-6,-7,8,9,4,10,11,12}, Output: {-2,-4,-5,-6,-7,1,3,8,9,4,10,11,12}

- Using extra memory
- T=O(n)
```cpp
vector<int> rearrange(vector<int>& arr) {
    vector<int> output;
    int i=0;
    for(auto e : arr) {
        if(e < 0) output[i++] = e;
    }

    for(auto e : arr) {
        if(e >= 0) output[i++] = e;
    }
}
```

- Using normal array shit approach.
- T=O(n2)
```cpp
void rearrange(vector<int>& arr) {
    for(int i=0;i<arr.size();i++) {
        if(arr[i] < 0) continue;
        int negPos = findNegPos(arr, i+1);
        if(negPos == -1) break;
        rightRotate(arr, i, negPos);
    }
}

void rightRotate(vector<int>& arr, int pos, int neg) {
    int negElem = arr[neg];
    for(int j=neg;j>pos;j--) {
        arr[j] = arr[j-1];
    }
    arr[pos] = negElem;
}
```

- Using optimized merge sort
- T=O(nlogn)
```cpp
void rearrange(vector<int>& arr) {
    rearrange(arr, 0, arr.size()-1);
}
void rearrange(vector<int>& arr, int l, int r) {
    if(l> r) return;
    int m = (l+r)/2;
    rearrange(arr, l, m, r);
    rearrange(arr, m+1, r);
    merge(arr, l, m, r);
}
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(m-l+1);
    vector<int> right(r-m);

    for(int i=l;i<=m;i++) left[i-l] = arr[i];
    for(int i=m+1;i<=r;i++) right[i-m-1] = arr[i];

    for(int i=l,j=m+1,k=l;k<=r;k++) {
        if(i <= m && left[i] < 0) arr[k] = left[i++];
        else if(j<=r && right[j] < 0) arr[k] = right[j++];
        else if(i <= m) arr[k] = left[i++];
        else arr[k] = right[j++];
    }
}
```

## Rearrange positive/negative numbers alternatively.
```cpp
```

## Sort elements by given order
```
Sort an array according to the order defined by another array
Given two arrays A1[] and A2[], sort A1 in such a way that the relative order among the elements will be same as those are in A2.
For the elements not present in A2, append them at last in sorted order.

Input: A1[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8}
       A2[] = {2, 1, 8, 3}
Output: A1[] = {2, 2, 1, 1, 8, 8, 3, 5, 6, 7, 9}
```

- T=O(nlogn), S=O(n)
```cpp
void sort(vector<int>& arr, vector<int>& order) {
    unordered_map<int, int> posMap;
    for(int i=0;i<order.size();i++) posMap[order[i]] = i;

    sort(arr.begin(), arr.end(), [](const auto& f, const auto& s) {
        if(posMap.find(f) != posMap.end() && posMap.find(s) != posMap.end()) {
            return posMap[f] < posMap[s];
        } else if(posMap.find(f) != posMap.end()) {
            return true;
        } else if(posMap.find(s) != posMap.end()) {
            return false;
        } else {
            return f < s;
        }
    });
}
```

- Using swapping
```cpp
void sort(vector<int>& arr, vector<int>& order) {
    for(int i=0;i<arr.size();i++) {
        int tmp = i;
        while(tmp != order[tmp]) {
            swap(arr[tmp], arr[order[tmp]]);
            swap(order[tmp], order[order[tmp]]);
            tmp = order[tmp];
        }
    }
}
```

## Search range in sorted array.
```
Given a sorted integer array and a number, find the start and end indexes of the number in the array.

Ex1: Array = {0,0,2,3,3,3,3,4,7,7,9} and Number = 3 --> Output = {3,6}
Ex2: Array = {0,0,2,3,3,3,3,4,7,7,9} and Number = 5 --> Output = {-1,-1}

Complexity should be less than O(n)
```
```cpp
pair<int, int> getRange(vector<int>& arr, int e) {
    int start = searchLeft(arr, 0, arr.size()-1, e);
    int end = searchRight(arr, 0, arr.size()-1, e);

    return {start, end};
}

int searchLeft(vector<int>& arr, int l, int r, int e) {
    while(l < r) {
        int m = (l+r)/2;
        if(e <= arr[m]) r = m;
        else l = m+1;
    }

    return l;
}

int searchRight(vector<int>& arr, int l, int r, int e) {
    while(l < r) {
        int m = (l+r+1)/2;
        if(e >= arr[m]) l = m;
        else r = m-1;
    }

    return l;
}
```

## Space numbers by its value
```cpp
void spaceNumbers(int n) {
    vector<int> arr(2*n);
    spaceNumbers(1, arr, n);
}

void spaceNumbers(int num, vector<int>& arr, int n) {
    if(num > n) return;

    for(int i=0;i+num+1<2*n;i++) {
        if(arr[i] != 0 || arr[i+num+1] != 0) continue;

        arr[i] = arr[i+num+1] = num;
        spaceNumbers(num+1, arr, n);
        arr[i] = arr[i+num+1] = 0;
    }
}
```

## Rearrange tasks by cooldown period
- Given a set of tasks and a cooldown period of K. Rearrange taks such that same task is spaced atleast by 'K' spaces. Find the minimum period to execute all tasks.

- Idea is to keep all tasks by frequency in priority queue and then try to fill as many different tasks we can put in each set and rest by cooldown window.
```cpp
int leastInterval(vector<char>& tasks, int K) {
    using P = pair<int, int>;
    auto comparator = [](const auto& f, const auto& s) { return f.second < s.second; };
    priority_queue<P, vector<P>, decltype(comparator)> pq;

    // find frequency of each task
    unordered_map<char, int> freqMap;
    for (auto& task : tasks) freqMap[task]++;

    // arrange pq by frequency.
    for (auto& e : freqMap) pq.push({e.first, e.second});

    int period = 0;
    while (!pq.empty()) {
        vector<char> curTasks; // tasks in current set
        vector<pair<int, int>> rest; // rest of the tasks which can be inserted for next iteration

        // add current task to list
        auto cur = pq.top();
        pq.pop();
        curTasks.push_back(cur.first);
        period++;  // increment period for current element

        // reduce occurance of this element and insert into rest
        cur.second--;
        if (cur.second) rest.push_back(cur);

        // calculate cooldown period
        int cooldown = 0;
        if (pq.size() < K) cooldown = K - pq.size();  // cooldown period

        // reduce frequency of rest of element
        int mn = min((int)pq.size(), K);
        period += mn;

        while (mn--) {
            auto top = pq.top();
            pq.pop();
            top.second--;
            curTasks.push_back(top.first);

            if (top.second) rest.push_back(top);
        }

        // insert rest to pq back
        for (auto& e : rest) pq.push(e);

        // add the remaining cooldown period
        if (pq.size()) {
            period += cooldown;
            vector<char> coolDownTasks(cooldown, '_');
            curTasks.insert(curTasks.end(), coolDownTasks.begin(), coolDownTasks.end());
        }

        cout << curTasks << endl;
    }

    return period;
}
```

## Space tasks with cooldwn period.
- This problem seems very similar to above but its actually very different.
- In above problem, we are allowed to rearrange elements and find least interval.
- In this problem, we don't need to rearrange elements. But, need to put spaces between tasks so that they are seperated by K cooldown period.
- We can keep the position of last occurance of current task and insert spaces accordingly.

```cpp
int spaceTasks(vector<char>& tasks, int k) {
    vector<int> lastIndex(256, -1);

    int totalTime = 0;
    int curIndex = 0;
    for(auto& task : tasks) {
        if(lastIndex[task] != -1 && curIndex - lastIndex[task] < k+1) {
            totalTime += (k+1)-(curIndex - lastIndex[task]); // insert these many spaces
            curIndex += totalTime; // indexes for all the spaces
        }
        lastIndex[task] = curIndex;
        totalTime += 1; // time for current task
        curIndex  += 1; // index for current element        
    }

    return totalTime;
}
```

## Rearrange characters of strings such that no two same characters are places together
- If such result not possible, return empty.

```cpp
 string reorganizeString(string s) {
    using P = pair<char, int>;
    auto compare = [](const auto& f, const auto& s) {return f.second < s.second;};
    priority_queue<P, vector<P>, decltype(compare)> pq;
    unordered_map<char, int> freq;
    for(auto& e : s) freq[e]++;
    for(auto& e : freq) pq.push({e.first, e.second});

    string result;
    while(!pq.empty()) {
        if(pq.size()==1 && pq.top().second > 1) return "";
        if(pq.size()==1 && pq.top().second == 1) {
            result += pq.top().first;
            break;
        }
        auto first = pq.top(); pq.pop();
        auto second = pq.top(); pq.pop();
        if(first.second > 1) pq.push({first.first, first.second-1});
        if(second.second > 1) pq.push({second.first, second.second-1});
        result += first.first;
        result += second.first;
    }

    return result;
}
```