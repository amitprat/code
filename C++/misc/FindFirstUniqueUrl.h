#pragma once
#include "../Header.h"

class FirstUniqueUrl {
public:
    static void test() {
        FirstUniqueUrl obj;
        vector<string> urls = {
           "abc.google.com",
           "abc.facebook.com",
           "abc.amazon.com",
           "abc.yahoo.com",
           "abc.facebook.com",
           "abc.yahoo.com",
           "abc.facebook.com",
           "abc.google.com"
        };

        cout << "First unique url = " << obj.firstUnique(urls) << endl;
        cout << "First unique url = " << obj.firstUnique2(urls) << endl;
    }

    string firstUnique(vector<string> urls) {
        unordered_map<string, list<string>::iterator> seen;
        list<string> l;

        for (auto url : urls) {
            if (seen.find(url) == seen.end()) {
                l.push_front(url);
                seen[url] = l.begin();
            }
            else if (seen[url] != l.end()) {
                l.erase(seen[url]);
                seen[url] = l.end();
            }
        }

        return l.front();
    }

    string firstUnique2(vector<string>& urls) {
        unordered_map<string, int> countMap;
        for (auto& url : urls) {
            countMap[url]++;
        }

        for (auto& url : urls) {
            if (countMap[url] == 1) return url;
        }
        return string("");
    }
};