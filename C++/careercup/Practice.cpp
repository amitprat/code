#include "../header.h"

vector<int> findSubstring(string s, vector<string>& words) {
    if (words.empty() || s.empty()) return {};

    unordered_map<string, int> wordmap;
    for (auto& word : words) wordmap[word]++;

    int l = words[0].length();

    int seensofar = 0;
    vector<int> result;
    unordered_map<string, int> seenCount;
    for (int start = 0, end = 0; end < s.length();) {
        string cur = s.substr(end, l);
        end += l;

        if (!wordmap.contains(cur)) {
            seenCount.clear();
            seensofar = 0;
            continue;
        }

        seenCount[cur]++;
        seensofar += l;

        while (seenCount[cur] > wordmap[cur]) {
            string startword = s.substr(start, l);
            seenCount[startword]--;
            start += l;
            seensofar -= l;
        }

        if (seensofar == words.size() * l) result.push_back(end - words.size() * l);
    }

    return result;
}

int main() {
    string s = "wordgoodgoodgoodbestword";
    vector<string> words = {"word", "good", "best", "good"};

    auto result = findSubstring(s, words);
    if (result.empty()) {
        cout << "No valid substring found." << endl;
    } else {
        cout << "Starting indices of valid substrings: ";

        for (int i : result) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}