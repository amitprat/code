#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=11856466

Given a very long list of URLs, find the first URL which is unique ( occurred exactly once ).

I gave a O(n) extra space and O(2n) time solution, but he was expecting O(n) time, one traversal.

- AK December 06, 2011 in India | Rep
*/
class FirstUniqueUrl
{
public:
    static void test() {
        FirstUniqueUrl obj;
        vector<string> urls = { "url1","url2","url3","url3","url1","url2"};
        auto res = obj.findFirstUniqueUrl(urls);
        cout << res << endl;
    }

    string findFirstUniqueUrl(vector<string> urls)
    {
        list<string> urlList;
        unordered_map<string, list<string>::iterator> urlMap;

        for (auto& url : urls) {
            if (urlMap.find(url) != urlMap.end()) {
                auto val = urlMap[url];
                if (val != urlList.end()) {
                    urlList.erase(val);
                    urlMap[url] = urlList.end();
                }
            }
            else {
                urlList.push_back(url);
                urlMap[url] = std::prev(urlList.end());
            }
        }

        if (!urlList.empty()) {
            return urlList.front();
        }

        return "Not Found";
    }
};