#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=4681660918398976

Given a large network of computers, each keeping log files of visited urls, find the top ten of the most visited urls.
(i.e. have many large <string (url) -> int (visits)> maps, calculate implicitly <string (url) -> int (sum of visits among all distributed maps), and get the top ten in the combined map)

The result list must be exact, and the maps are too large to transmit over the network (especially sending all of them to a central server or using MapReduce directly, is not allowed)
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
*/

class Top10MostVisitedUrls {
    using P = pair<int, string>;

   private:
    class Server {
       private:
        map<string, int> urlFreq;
        map<int, string, greater<int>> urls;

       public:
        void init(const map<int, string, greater<int>> &urls) {
            this->urls = urls;
            for (auto &url : urls) {
                urlFreq[url.second] += url.first;
            }
        }

        map<int, string, greater<int>> getTopKUrls(int k) {
            map<int, string, greater<int>> result;
            for (auto &url : urls) {
                result.insert(url);
                k--;

                if (k == 0)
                    break;
            }

            return result;
        }

        map<int, string, greater<int>> getUrlsWithHigherFreq(int kthFreq) {
            map<int, string, greater<int>> result;
            for (auto &url : urls) {
                if (url.first >= kthFreq) {
                    result.insert(url);
                }
            }

            return result;
        }

        int getValue(string key) {
            return urlFreq[key];
        }
    };

   public:
    static void test() {
        vector<Server> servers;

        Server server1;
        server1.init({{1, "url1"}, {3, "url2"}, {10, "url3"}, {2, "url5"}, {6, "url4"}});

        Server server2;
        server2.init({{10, "url1"}, {3, "url2"}, {1, "url3"}, {2, "url5"}, {2, "url4"}});

        Server server3;
        server3.init({{3, "url1"}, {1, "url2"}, {4, "url3"}, {2, "url5"}, {6, "url4"}});

        servers.push_back(server1);
        servers.push_back(server2);
        servers.push_back(server3);

        Top10MostVisitedUrls obj;
        map<string, int> result = obj.findTopKUrls(servers);
        cout << "Result: " << result << endl;
    }

   private:
    map<string, int> findTopKUrls(vector<Server> servers) {
        // round 1
        map<string, int> result;
        for (auto &server : servers) {
            auto part = server.getTopKUrls(2);
            for (auto &kv : part) {
                result[kv.second] += kv.first;
            }
        }

        // round 2
        for (auto &kv : result) {
            int val = 0;
            for (auto &server : servers) {
                val += server.getValue(kv.first);
            }

            result[kv.first] = val;
        }

        // round 3
        map<int, string, greater<int>> revMap;
        for (auto &kv : result) {
            revMap[kv.second] = kv.first;
        }

        int kthFreq = 0;
        int k = 2;
        for (auto &e : revMap) {
            kthFreq = e.first;
            k--;
            if (k == 0)
                break;
        }

        result.clear();
        for (auto &server : servers) {
            auto part = server.getUrlsWithHigherFreq(kthFreq / servers.size());
            for (auto &kv : part) {
                result[kv.second] += kv.first;
            }
        }

        revMap.clear();
        for (auto &kv : result) {
            revMap[kv.second] = kv.first;
        }

        k = 2;
        result.clear();
        for (auto &e : revMap) {
            result[e.second] = e.first;
            k--;
            if (k == 0)
                break;
        }

        return result;
    }
};