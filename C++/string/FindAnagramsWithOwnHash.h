#pragma once
#include "../header.h"

class FindAnagrams {
   public:
    static void test(vector<string> strs) {
        FindAnagrams obj;
        auto res = obj.calculate(strs);
        for (auto r : res) {
            cout << r.first << " : ";
            for (auto s : r.second) {
                cout << s << " ";
            }
            cout << endl;
        }
    }

    vector<pair<unsigned long long, vector<string>>> calculate(vector<string> str) {
        vector<pair<unsigned long long, vector<string>>> res;
        for (auto s : str) {
            unsigned long long h = hash(s);
            bool exist = false;
            for (auto& v : res) {
                if (v.first == h) {
                    v.second.push_back(s);
                    exist = true;
                }
            }
            if (!exist) res.push_back({h, {s}});
        }

        return res;
    }

    unsigned long long hash(string str) {
        int radix = 256;
        int pw = 10;
        unsigned long long res = 0;
        for (auto ch : str) {
            res += pow(radix, pw) + ch;
            pw++;
        }

        return res;
    }

    size_t calculateHash(const string& input) {
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(input);

        println("Hash of string:{0} is {1}", input, hash_value);
    }
};