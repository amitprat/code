#include "../header.h"

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