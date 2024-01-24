#pragma once
#include "../Header.h"

class DocumentSimilarity {
public:
    static void test() {
        DocumentSimilarity obj;
        vector<pair<int, vector<int>>> documents = {
            {13, {14, 15, 100, 9, 3}},
            {16, {32, 1, 9, 3, 5}},
            {19, {15, 29, 2, 6, 8, 7}},
            {24, {7, 10} }
        };

        {
            vector<pair<pair<int, int>, double>> similarities = obj.calculate(documents);
            for (auto s : similarities) {
                cout << "Similarity between pair " + to_string(s.first) << " = " << s.second << endl;
            }
        }

        {
            vector<pair<pair<int, int>, double>> similarities = obj.calculate2(documents);
            for (auto s : similarities) {
                cout << "Similarity between pair " + to_string(s.first) << " = " << s.second << endl;
            }
        }
    }

    vector<pair<pair<int, int>, double>> calculate(vector<pair<int, vector<int>>> documents) {
        vector<pair<pair<int, int>, double>> result;

        for (int i = 0; i < documents.size(); i++) {
            for (int j = i + 1; j < documents.size(); j++) {
                auto s = calcSim(documents[i].second, documents[j].second);
                if (s > 0) result.push_back({ {documents[i].first, documents[j].first},s });
            }
        }

        return result;
    }

    double calcSim(vector<int> doc1, vector<int> doc2) {
        unordered_set<int> s;
        int inter = 0;
        for (auto e : doc1) s.insert(e);
        for (auto e : doc2) {
            if (s.find(e) != s.end()) inter++;
        }

        return (double)inter / (double)(doc1.size() + doc2.size() - inter);
    }

    vector<pair<pair<int, int>, double>> calculate2(vector<pair<int, vector<int>>> documents) {
        // calcualte reverse map and sz map
        unordered_map<int, vector<int>> revMap;
        unordered_map<int, int> count;
        unordered_map<int, int> sz;
        for (auto doc : documents) { // T = O(W*D) where D=num documents, W-max word size
            sz.insert({ doc.first,doc.second.size() });
            for (auto e : doc.second) {
                revMap[e].push_back(doc.first);
                count[e]++;
            }
        }

        // do pair count
        vector<pair<pair<int, int>, double>> result;
        unordered_map<string, int> pairCount;
        for (auto entry : revMap) { // T = O(W*D) where D=num documents, W-max word size
            if (entry.second.size() > 1) {
                for (int i = 0; i < entry.second.size(); i++) {
                    for (int j = i + 1; j < entry.second.size(); j++) {
                        pairCount[to_key(entry.second[i], entry.second[j])]++;
                    }
                }
            }
        }

        // calculate final result
        for (auto s : pairCount) { // T=O(D)
            auto p = to_pair(s.first);
            auto i = s.second;
            auto u = sz[p.first] + sz[p.second] - i;

            result.push_back({ p,(double)i / (double)u });
        }

        return result;
    }

private:
    string to_key(int i, int j) {
        return std::to_string(i) + "," + std::to_string(j);
    }

    pair<int, int> to_pair(string s) {
        auto pos = s.find(",");
        return { stoi(s.substr(0,pos)), stoi(s.substr(pos + 1)) };
    }
};