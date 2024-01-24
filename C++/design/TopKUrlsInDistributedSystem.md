# Find Top K Urls in Distributed System

*Given a large network of computers, each keeping log files of visited urls, find the top ten of the most visited urls. (i.e. have many large <string (url) -> int (visits)> maps, calculate implicitly <string (url) -> int (sum of visits among all distributed maps), and get the top ten in the combined map). The result list must be exact, and the maps are too large to transmit over the network (especially sending all of them to a central server or using MapReduce directly, is not allowed)*

https://careercup.com/question?id=4681660918398976
```java
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
```

**Sample Code**
```cpp
<string, int> getTopKUrls(int k) {
    vector<Machine> machines;
    unordered_map<string, int> freq;
    priority_queue<pair<int, string>,..,greater<..>>> pq;

    // First iteration
    for(auto m : machines) {
        auto cur = m.getTopKUrls(k);
        freq.merge(cur);
    }

    // Second iteration
    for(auto e : freq) {
        int curFreq = 0;
        for(auto m : machines) {
            curFreq += m.getFreq(e.first);
        }
        if(pq.size() > k) {
            if(curFreq > pq.top().first) {
                pq.pop();
                pq.push({curFreq, e.second});
            }
        } else {
            pq.push({curFreq, e.second});
        }
    }

    // By now, pq has top k elements
    int minFreq = pq.top().first;
    int cutOff = minFreq/machines.size();

    for(auto m : machines) {
        auto cur = m.getAllElementsWithFreqGreater(cutOff);
        newResult.merge(cur);
    }

    // merge as pervious step
    // Now  we have final result
}
```